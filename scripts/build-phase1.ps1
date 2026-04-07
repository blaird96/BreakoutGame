# Build Phase I (root main.exe). Requires the same WinLibs + SFML paths as .vscode/tasks.json.
# Plain `g++ *.cpp` will fail: SFML headers need -I and the linker needs -L plus -lsfml-*.
$ErrorActionPreference = "Stop"
$Root = Split-Path -Parent $PSScriptRoot
$Gpp = "C:\winlibs-x86_64-posix-seh-gcc-14.2.0-mingw-w64ucrt-12.0.0-r2\mingw64\bin\g++.exe"
$Sfml = "C:\SFML-3.0.2"
$Out = Join-Path $Root "main.exe"

& $Gpp -std=c++20 -fdiagnostics-color=always -g `
    "-I$Sfml\include" `
    (Join-Path $Root "phase1_main.cpp") `
    (Join-Path $Root "Game.cpp") `
    (Join-Path $Root "src\GameManager.cpp") `
    "-L$Sfml\lib" `
    -lsfml-graphics -lsfml-window -lsfml-system `
    -o $Out

Write-Host "Built: $Out"
