# Run main.exe with WinLibs + SFML on PATH (same as VS Code debug / integrated terminal).
$ErrorActionPreference = "Stop"
$Root = Split-Path -Parent $PSScriptRoot
$WinLibsBin = "C:\winlibs-x86_64-posix-seh-gcc-14.2.0-mingw-w64ucrt-12.0.0-r2\mingw64\bin"
$SfmlBin = "C:\SFML-3.0.2\bin"
$Exe = Join-Path $Root "main.exe"

if (-not (Test-Path $Exe)) {
    Write-Error "main.exe not found. Build first (VS Code: Terminal > Run Build Task)."
}

$env:PATH = "$WinLibsBin;$SfmlBin;$env:PATH"
Set-Location $Root
& $Exe
