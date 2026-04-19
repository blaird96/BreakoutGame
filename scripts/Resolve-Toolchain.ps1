# Centralized toolchain discovery keeps per-machine paths out of the shared repo files.
# Teammates can override detection with environment variables instead of committing local paths:
# - BREAKOUT_GPP: full path to g++.exe
# - BREAKOUT_GDB: full path to gdb.exe
# - BREAKOUT_SFML_ROOT: root folder that contains include/, lib/, and bin/
# - BREAKOUT_RUNTIME_BIN: optional semicolon-separated DLL search path for debug/run
# - MSYS2_ROOT: optional root folder for MSYS2 installs, e.g. C:\msys64

function Get-FirstExistingPath {
    param(
        [string[]]$Candidates,
        [switch]$Directory
    )

    foreach ($candidate in $Candidates) {
        if ([string]::IsNullOrWhiteSpace($candidate)) {
            continue
        }

        if ($Directory) {
            if (Test-Path -LiteralPath $candidate -PathType Container) {
                return $candidate
            }
            continue
        }

        if (Test-Path -LiteralPath $candidate -PathType Leaf) {
            return $candidate
        }
    }

    return $null
}

function Get-FirstValidSfmlRoot {
    param([string[]]$Candidates)

    foreach ($candidate in $Candidates) {
        if ([string]::IsNullOrWhiteSpace($candidate)) {
            continue
        }

        $includeDir = Join-Path $candidate "include"
        $libDir = Join-Path $candidate "lib"
        $binDir = Join-Path $candidate "bin"

        if ((Test-Path -LiteralPath $includeDir -PathType Container) -and
            (Test-Path -LiteralPath $libDir -PathType Container) -and
            (Test-Path -LiteralPath $binDir -PathType Container)) {
            return $candidate
        }
    }

    return $null
}

function Get-Msys2RootFromCompilerPath {
    param([string]$CompilerPath)

    if ([string]::IsNullOrWhiteSpace($CompilerPath)) {
        return $null
    }

    $compilerDir = Split-Path -Parent $CompilerPath
    if ([string]::IsNullOrWhiteSpace($compilerDir)) {
        return $null
    }

    $ucrtDir = Split-Path -Parent $compilerDir
    if ([string]::IsNullOrWhiteSpace($ucrtDir)) {
        return $null
    }

    if ((Split-Path -Leaf $ucrtDir) -ne 'ucrt64') {
        return $null
    }

    $msys2Root = Split-Path -Parent $ucrtDir
    if ([string]::IsNullOrWhiteSpace($msys2Root)) {
        return $null
    }

    if (Test-Path -LiteralPath (Join-Path $msys2Root 'usr\bin') -PathType Container) {
        return $msys2Root
    }

    return $null
}

function Resolve-BreakoutToolchain {
    $gppCandidates = @(
        $env:BREAKOUT_GPP,
        $(if ($env:MSYS2_ROOT) { Join-Path $env:MSYS2_ROOT "ucrt64\bin\g++.exe" }),
        "C:\msys64\ucrt64\bin\g++.exe",
        "C:\winlibs-x86_64-posix-seh-gcc-14.2.0-mingw-w64ucrt-12.0.0-r2\mingw64\bin\g++.exe"
    )

    $gdbCandidates = @(
        $env:BREAKOUT_GDB,
        $(if ($env:MSYS2_ROOT) { Join-Path $env:MSYS2_ROOT "ucrt64\bin\gdb.exe" }),
        "C:\msys64\ucrt64\bin\gdb.exe",
        "C:\winlibs-x86_64-posix-seh-gcc-14.2.0-mingw-w64ucrt-12.0.0-r2\mingw64\bin\gdb.exe"
    )

    $sfmlRootCandidates = @(
        $env:BREAKOUT_SFML_ROOT,
        $(if ($env:MSYS2_ROOT) { Join-Path $env:MSYS2_ROOT "ucrt64" }),
        "C:\msys64\ucrt64",
        "C:\SFML-3.0.2"
    )

    $gpp = Get-FirstExistingPath -Candidates $gppCandidates
    if (-not $gpp) {
        $detectedGpp = Get-Command g++.exe -ErrorAction SilentlyContinue
        if ($detectedGpp) {
            $gpp = $detectedGpp.Source
        }
    }

    $gdb = Get-FirstExistingPath -Candidates $gdbCandidates
    if (-not $gdb) {
        $detectedGdb = Get-Command gdb.exe -ErrorAction SilentlyContinue
        if ($detectedGdb) {
            $gdb = $detectedGdb.Source
        }
    }

    $sfmlRoot = Get-FirstValidSfmlRoot -Candidates $sfmlRootCandidates

    $compilerBin = $null
    if ($gpp) {
        $compilerBin = Split-Path -Parent $gpp
    }

    $sfmlBin = $null
    if ($sfmlRoot) {
        $sfmlBin = Join-Path $sfmlRoot "bin"
    }

    $msys2Root = Get-FirstExistingPath -Candidates @(
        $env:MSYS2_ROOT,
        $(Get-Msys2RootFromCompilerPath -CompilerPath $gpp),
        'C:\msys64'
    ) -Directory

    $msys2UsrBin = $null
    if ($msys2Root) {
        $candidateUsrBin = Join-Path $msys2Root 'usr\bin'
        if (Test-Path -LiteralPath $candidateUsrBin -PathType Container) {
            $msys2UsrBin = $candidateUsrBin
        }
    }

    [pscustomobject]@{
        Gpp         = $gpp
        Gdb         = $gdb
        SfmlRoot    = $sfmlRoot
        CompilerBin = $compilerBin
        SfmlBin     = $sfmlBin
        Msys2Root   = $msys2Root
        Msys2UsrBin = $msys2UsrBin
    }
}
