param(
    [string]$BuildDir = "build",
    [switch]$Configure,
    [switch]$Force
)

$ErrorActionPreference = "Stop"

$repoRoot = Split-Path -Parent $PSScriptRoot
$expectedPath = Join-Path $repoRoot "tests/golden_master_expected.txt"
$buildPath = Join-Path $repoRoot $BuildDir

if ($Force -and (Test-Path $expectedPath)) {
    Remove-Item $expectedPath
}

if ($Configure -or -not (Test-Path $buildPath)) {
    cmake -S $repoRoot -B $buildPath
}

cmake --build $buildPath --target sentiment_tests

$testExe = Join-Path $buildPath "sentiment_tests.exe"
if (-not (Test-Path $testExe)) {
    $testExe = Join-Path $buildPath "Debug/sentiment_tests.exe"
}

if (-not (Test-Path $testExe)) {
    $testExe = Join-Path $buildPath "sentiment_tests"
}

if (-not (Test-Path $testExe)) {
    throw "sentiment_tests executable was not found under $buildPath"
}

& $testExe --gtest_filter=GoldenMasterTest.ApproveTextAnalyzerOutput
if ($LASTEXITCODE -ne 0) {
    if ($Force -and (Test-Path $expectedPath)) {
        & $testExe --gtest_filter=GoldenMasterTest.ApproveTextAnalyzerOutput
    }

    if ($LASTEXITCODE -ne 0) {
        exit $LASTEXITCODE
    }
}

Write-Host "Golden Master baseline is ready: $expectedPath"
