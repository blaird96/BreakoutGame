# Run main.exe with the detected compiler/SFML runtime folders on PATH.
# This keeps the repo portable while still supporting local overrides through environment variables.
$ErrorActionPreference = "Stop"
$Root = Split-Path -Parent $PSScriptRoot
$Resolver = Join-Path $PSScriptRoot "Resolve-Toolchain.ps1"
. $Resolver

$Toolchain = Resolve-BreakoutToolchain
$Exe = Join-Path $Root "main.exe"

if (-not (Test-Path $Exe)) {
    Write-Error "main.exe not found. Build first (VS Code: Terminal > Run Build Task)."
}

$runtimeEntries = @()

# BREAKOUT_RUNTIME_BIN is the team escape hatch for custom DLL locations without editing tracked files.
if ($env:BREAKOUT_RUNTIME_BIN) {
    $runtimeEntries += ($env:BREAKOUT_RUNTIME_BIN -split ';')
} else {
    $runtimeEntries += $Toolchain.CompilerBin
    $runtimeEntries += $Toolchain.SfmlBin
}

$runtimeEntries = $runtimeEntries |
    Where-Object { -not [string]::IsNullOrWhiteSpace($_) } |
    Select-Object -Unique

# Exe directory first: build-phase1.ps1 copies DLLs next to main.exe; then toolchain bins.
$prefixDirs = @($Root) + $runtimeEntries |
    Where-Object { -not [string]::IsNullOrWhiteSpace($_) } |
    Select-Object -Unique
if ($prefixDirs.Count -gt 0) {
    $env:PATH = ($prefixDirs -join ';') + ';' + $env:PATH
}

Set-Location $Root

$preflight = @("libstdc++-6.dll", "libsfml-window-3.dll")
foreach ($dll in $preflight) {
    $ok = $false
    if (Test-Path -LiteralPath (Join-Path $Root $dll)) {
        $ok = $true
    }
    if (-not $ok) {
        foreach ($dir in $runtimeEntries) {
            if (Test-Path -LiteralPath (Join-Path $dir $dll)) {
                $ok = $true
                break
            }
        }
    }
    if (-not $ok) {
        Write-Warning "Could not find $dll next to main.exe or in toolchain bin folders. Run .\scripts\build-phase1.ps1 (install SFML in MSYS2 UCRT64 if the build reports missing DLLs)."
    }
}

Write-Host "Launching main.exe (working directory: $Root) ..."
& $Exe
$code = $LASTEXITCODE
if ($code -ne 0) {
    Write-Host "main.exe exited with code $code. If it failed instantly, missing MinGW/SFML DLLs are the usual cause; rebuild with .\scripts\build-phase1.ps1 to copy DLLs beside the exe."
}
