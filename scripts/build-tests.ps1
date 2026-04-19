# Configure, build, and run CTest for the lightweight unit-test harness.
$ErrorActionPreference = "Stop"
$Root = Split-Path -Parent $PSScriptRoot
Set-Location $Root

cmake --preset tests-debug
if ($LASTEXITCODE -ne 0) {
    throw "cmake configure (tests-debug) failed with exit code $LASTEXITCODE."
}
cmake --build --preset tests-debug
if ($LASTEXITCODE -ne 0) {
    throw "cmake build (tests-debug) failed with exit code $LASTEXITCODE."
}
ctest --preset tests-debug
if ($LASTEXITCODE -ne 0) {
    throw "ctest (tests-debug) failed with exit code $LASTEXITCODE."
}
Write-Host "Tests completed successfully."
