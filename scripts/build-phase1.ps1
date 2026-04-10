# Build Phase I (root main.exe).
# Toolchain discovery is centralized so teammates can use local installs without editing this script.
# Plain `g++ *.cpp` will fail: SFML headers need -I and the linker needs -L plus -lsfml-*.
$ErrorActionPreference = "Stop"
$Root = Split-Path -Parent $PSScriptRoot
$Resolver = Join-Path $PSScriptRoot "Resolve-Toolchain.ps1"
. $Resolver

$Toolchain = Resolve-BreakoutToolchain
$Gpp = $Toolchain.Gpp
$Sfml = $Toolchain.SfmlRoot
$Out = Join-Path $Root "main.exe"

if (-not $Gpp) {
    throw "Could not find g++.exe. Set BREAKOUT_GPP or put g++.exe on PATH."
}

if (-not $Sfml) {
    throw "Could not find an SFML install. Set BREAKOUT_SFML_ROOT to a folder with include/, lib/, and bin/."
}

Write-Host "Using compiler: $Gpp"
Write-Host "Using SFML root: $Sfml"

& $Gpp -std=c++20 -fdiagnostics-color=always -g `
    "-I$Sfml\include" `
    (Join-Path $Root "phase1_main.cpp") `
    (Join-Path $Root "Game.cpp") `
    (Join-Path $Root "src\GameManager.cpp") `
    "-L$Sfml\lib" `
    -lsfml-graphics -lsfml-window -lsfml-system `
    -o $Out

Write-Host "Built: $Out"
