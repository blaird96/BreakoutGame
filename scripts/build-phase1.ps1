# Build Phase I (root main.exe).
# Toolchain discovery is centralized so teammates can use local installs without editing this script.
# Plain `g++ *.cpp` will fail: SFML headers need -I and the linker needs -L plus -lsfml-*.
$ErrorActionPreference = "Stop"
$Root = Split-Path -Parent $PSScriptRoot
$RuntimeDir = Join-Path $Root "runtime"
$Resolver = Join-Path $PSScriptRoot "Resolve-Toolchain.ps1"
. $Resolver

$Toolchain = Resolve-BreakoutToolchain
$Gpp = $Toolchain.Gpp
$Sfml = $Toolchain.SfmlRoot
$Out = Join-Path $Root "main.exe"

if ($Toolchain.Msys2UsrBin) {
    $pathParts = @($Toolchain.CompilerBin, $Toolchain.Msys2UsrBin, $env:PATH) |
        Where-Object { -not [string]::IsNullOrWhiteSpace($_) }
    $env:PATH = ($pathParts | Select-Object -Unique) -join ';'
}

if (-not $Gpp) {
    throw "Could not find g++.exe. Set BREAKOUT_GPP or put g++.exe on PATH."
}

if (-not $Sfml) {
    throw "Could not find an SFML install. Set BREAKOUT_SFML_ROOT to a folder with include/, lib/, and bin/."
}

Write-Host "Using compiler: $Gpp"
Write-Host "Using SFML root: $Sfml"

# Avoid -fdiagnostics-color=always here: some GCC builds return non-zero when stdout is not a TTY.
& $Gpp -std=c++20 -g `
    "-I$Sfml\include" `
    (Join-Path $Root "phase1_main.cpp") `
    (Join-Path $Root "Game.cpp") `
    (Join-Path $Root "src\GameManager.cpp") `
    "-L$Sfml\lib" `
    -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio `
    "-L$Root\lib" `
    -lsqlite3 `
    -o $Out

if (-not (Test-Path -LiteralPath $Out)) {
    $code = $LASTEXITCODE
    throw "Build failed: main.exe was not produced (g++ exit code $code)."
}
if ($LASTEXITCODE -ne 0) {
    Write-Warning "g++ reported exit code $LASTEXITCODE but main.exe exists; continuing."
}

# Copy MinGW/SFML dependency DLLs into runtime\ (recursive via objdump). Static name lists miss installs
# where SFML lives elsewhere or transitive deps differ. Loaders resolve them via PATH (run-game.ps1 / IDE).
function Test-SkipPeBundleDll {
    param([string]$Name)
    $n = $Name.ToLowerInvariant()
    if ($n.StartsWith("api-ms-win-")) { return $true }
    if ($n.StartsWith("ext-ms-")) { return $true }
    return $false
}

function Test-IsMingwRuntimeDllName {
    param([string]$Name)
    $n = $Name.ToLowerInvariant()
    if ($n.StartsWith("lib")) { return $true }
    if ($n -match "sfml") { return $true }
    return $false
}

function Get-PeDllImportNames {
    param(
        [Parameter(Mandatory)][string]$FilePath,
        [Parameter(Mandatory)][string]$ObjdumpExe
    )
    if (-not (Test-Path -LiteralPath $FilePath)) {
        return @()
    }
    $out = & $ObjdumpExe -p $FilePath 2>$null
    if (-not $out) {
        return @()
    }
    $names = [System.Collections.Generic.List[string]]::new()
    foreach ($line in $out) {
        if ($line -match "DLL Name:\s*(\S+)") {
            $names.Add($Matches[1]) | Out-Null
        }
    }
    return $names
}

function Find-DllInSearchRoots {
    param(
        [Parameter(Mandatory)][string]$DllLeafName,
        [string[]]$SearchDirs
    )
    foreach ($dir in $SearchDirs) {
        if ([string]::IsNullOrWhiteSpace($dir)) { continue }
        $p = Join-Path $dir $DllLeafName
        if (Test-Path -LiteralPath $p) {
            return $p
        }
    }
    return $null
}

$CompilerBin = $Toolchain.CompilerBin
$SfmlBin = $Toolchain.SfmlBin
$BinSearch = @(
    $CompilerBin
    $SfmlBin
    $Toolchain.Msys2UsrBin
    $(if ($env:MSYS2_ROOT) { Join-Path $env:MSYS2_ROOT "ucrt64\bin" })
    $(if ($env:BREAKOUT_RUNTIME_BIN) { $env:BREAKOUT_RUNTIME_BIN -split ";" })
) | Where-Object { -not [string]::IsNullOrWhiteSpace($_) } | Select-Object -Unique

$Objdump = Join-Path (Split-Path -Parent $Gpp) "objdump.exe"
if (-not (Test-Path -LiteralPath $Objdump)) {
    Write-Warning "objdump.exe not found next to g++.exe; cannot bundle runtime DLLs automatically."
} else {
    New-Item -ItemType Directory -Path $RuntimeDir -Force | Out-Null
    $queue = New-Object System.Collections.Generic.Queue[string]
    $seenLeaf = @{}

    foreach ($dll in (Get-PeDllImportNames -FilePath $Out -ObjdumpExe $Objdump)) {
        if (Test-SkipPeBundleDll $dll) { continue }
        if (-not (Test-IsMingwRuntimeDllName $dll)) { continue }
        $src = Find-DllInSearchRoots -DllLeafName $dll -SearchDirs $BinSearch
        if ($src) {
            $queue.Enqueue($src) | Out-Null
        }
    }

    $copied = 0
    while ($queue.Count -gt 0) {
        $src = $queue.Dequeue()
        $leaf = Split-Path -Leaf $src
        if ($seenLeaf.ContainsKey($leaf)) { continue }
        $seenLeaf[$leaf] = $true
        Copy-Item -LiteralPath $src -Destination (Join-Path $RuntimeDir $leaf) -Force
        ++$copied

        foreach ($dep in (Get-PeDllImportNames -FilePath $src -ObjdumpExe $Objdump)) {
            if (Test-SkipPeBundleDll $dep) { continue }
            if (-not (Test-IsMingwRuntimeDllName $dep)) { continue }
            $depSrc = Find-DllInSearchRoots -DllLeafName $dep -SearchDirs $BinSearch
            if ($depSrc) {
                $queue.Enqueue($depSrc) | Out-Null
            }
        }
    }

    $stillMissing = [System.Collections.Generic.List[string]]::new()
    foreach ($dll in (Get-PeDllImportNames -FilePath $Out -ObjdumpExe $Objdump)) {
        if (Test-SkipPeBundleDll $dll) { continue }
        if (-not (Test-IsMingwRuntimeDllName $dll)) { continue }
        if (-not (Test-Path -LiteralPath (Join-Path $RuntimeDir $dll))) {
            $stillMissing.Add($dll) | Out-Null
        }
    }

    if ($stillMissing.Count -gt 0) {
        $uniq = $stillMissing | Select-Object -Unique
        $msg = @"
The build linked main.exe, but these MinGW/SFML runtime DLLs were not found under your compiler or SFML bin folders:
  $($uniq -join "`n  ")

Typical fix on MSYS2 (open 'UCRT64' terminal, not MSYS):
  pacman -Syu
  pacman -S mingw-w64-ucrt-x86_64-sfml

Or point BREAKOUT_SFML_ROOT (and if needed BREAKOUT_RUNTIME_BIN) at an install whose bin\ folder contains the DLLs above.
"@
        throw $msg
    }

    if ($copied -gt 0) {
        Write-Host "Copied $copied runtime DLL(s) to runtime\ (objdump dependency closure)."
    }
}

Write-Host "Built: $Out"
