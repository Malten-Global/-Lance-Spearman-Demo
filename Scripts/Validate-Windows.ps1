param([string]$Engine = 'C:\Program Files\Epic Games\UE_5.4', [Parameter(Mandatory)][string]$Output)
$ErrorActionPreference = 'Stop'
$Project = (Resolve-Path (Join-Path $PSScriptRoot '../LanceSpearman.uproject')).Path
if (Test-Path $Output) { throw 'Choose a new output directory for this run.' }
$Dir = (New-Item -ItemType Directory -Path $Output).FullName
Start-Transcript -Path (Join-Path $Dir 'validation.log')
try {
  git -C (Split-Path $Project) rev-parse HEAD
  if ($LASTEXITCODE) { throw 'Could not identify checkout' }
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
