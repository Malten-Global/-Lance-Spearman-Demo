param([string]$Engine = 'C:\Program Files\Epic Games\UE_5.4', [Parameter(Mandatory)][string]$Output)
$ErrorActionPreference = 'Stop'
if ($env:OS -ne 'Windows_NT') { throw 'Win64 validation requires Windows.' }
$VersionFile = Join-Path $Engine 'Engine/Build/Build.version'
if (!(Test-Path $VersionFile)) { throw 'Unreal Engine Build.version is missing.' }
$Version = Get-Content -Raw $VersionFile | ConvertFrom-Json
if ($Version.MajorVersion -ne 5 -or $Version.MinorVersion -ne 4) {
  throw 'This validation requires Unreal Engine 5.4.x.'
}
foreach ($Required in 'Engine/Build/BatchFiles/Build.bat','Engine/Build/BatchFiles/RunUAT.bat') {
  if (!(Test-Path (Join-Path $Engine $Required))) { throw "Missing engine tool: $Required" }
}
$Project = (Resolve-Path (Join-Path $PSScriptRoot '../LanceSpearman.uproject')).Path
if (Test-Path $Output) { throw 'Choose a new output directory for this run.' }
$Dir = (New-Item -ItemType Directory -Path $Output).FullName
Start-Transcript -Path (Join-Path $Dir 'validation.log')
try {
  git -C (Split-Path $Project) rev-parse HEAD
  if ($LASTEXITCODE) { throw 'Could not identify checkout' }
  $Dirty = git -C (Split-Path $Project) status --porcelain
  if ($LASTEXITCODE) { throw 'Could not inspect checkout status' }
  if ($Dirty) { throw 'Use a clean checkout so the recorded commit identifies the build source.' }
  Write-Host "Engine: $($Version.MajorVersion).$($Version.MinorVersion).$($Version.PatchVersion)"
  Write-Host "Windows: $([Environment]::OSVersion.VersionString)"
  $Build = Join-Path $Engine 'Engine/Build/BatchFiles/Build.bat'
  foreach ($Target in 'LanceSpearmanEditor','LanceSpearman') {
    & $Build $Target Win64 Development "-Project=$Project" -WaitMutex
    if ($LASTEXITCODE) { throw "Failed to build $Target" }
  }
  & (Join-Path $Engine 'Engine/Build/BatchFiles/RunUAT.bat') BuildCookRun "-project=$Project" -noP4 -platform=Win64 -clientconfig=Development -build -cook -map=/Engine/Maps/Entry -stage -pak -archive "-archivedirectory=$Dir" -prereqs -utf8output
  if ($LASTEXITCODE) { throw 'Package failed' }
  if (!(Test-Path (Join-Path $Dir 'Windows/LanceSpearman.exe'))) { throw 'Archived executable missing' }
  Write-Host 'Package present. Launch it on Windows and complete the gameplay checks.'
} finally { Stop-Transcript }
