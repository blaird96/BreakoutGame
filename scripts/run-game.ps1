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

if ($runtimeEntries.Count -gt 0) {
    $env:PATH = (($runtimeEntries + $env:PATH) -join ';')
}

Set-Location $Root
& $Exe
