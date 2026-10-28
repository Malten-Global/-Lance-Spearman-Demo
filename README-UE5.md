# Lance Spearman — UE 5.4 Windows foundation

Status: source foundation only. No Unreal compilation, cooking or Windows gameplay validation has been performed here. The browser prototype in chapter1/ is separate.

## Structure
Open the repository-root LanceSpearman.uproject (EngineAssociation 5.4).
Config/ contains map, legacy input and packaging settings. Source/LanceSpearman/
contains the runtime module, Build.cs, game/editor Target.cs rules and native actors.
The targets name the same LanceSpearman module as the descriptor. No project Content
map or production art is required for this blockout: /Engine/Maps/Entry is the
startup map; the game mode creates geometry, a player start, light, guards and contact.
DefaultGame.ini explicitly cooks Entry and the dynamically loaded BasicShapes.

## Windows prerequisites
Install UE **5.4.x** (including Windows platform support), Visual Studio 2022 with
Game development with C++, MSVC v143 x64/x86 **14.38 (VS 17.8)** and Windows SDK
**10.0.22621.0**. Install the older toolset alongside newer VS versions if needed.
Use a DX12-capable Windows development PC.
Epic setup reference: https://dev.epicgames.com/documentation/en-us/unreal-engine/setting-up-visual-studio-development-environment-for-cplusplus-projects-in-unreal-engine?application_version=5.4

## Clean checkout and build
In PowerShell, from the repository root on branch ue5-chapter1-level1.
Close Unreal Editor first (avoid Live Coding). A fresh checkout needs no generated
files. For a previously built checkout, remove only project Binaries/, Intermediate/,
Saved/ and .vs/ if a clean rebuild is needed; Saved/ includes local logs/settings.
Do not remove Source/ or Config/.

```powershell
$ErrorActionPreference = 'Stop'
$UE = 'C:\Program Files\Epic Games\UE_5.4'
$Project = (Resolve-Path '.\LanceSpearman.uproject').Path
& "$UE\Engine\Build\BatchFiles\Build.bat" -projectfiles "-project=$Project" -game -rocket -progress
if ($LASTEXITCODE -ne 0) { throw 'Project generation failed' }
& "$UE\Engine\Build\BatchFiles\Build.bat" LanceSpearmanEditor Win64 Development "-Project=$Project" -WaitMutex -NoHotReloadFromIDE
if ($LASTEXITCODE -ne 0) { throw 'Editor build failed' }
& "$UE\Engine\Build\BatchFiles\Build.bat" LanceSpearman Win64 Development "-Project=$Project" -WaitMutex
if ($LASTEXITCODE -ne 0) { throw 'Game build failed' }
& "$UE\Engine\Binaries\Win64\UnrealEditor.exe" $Project -log
```

Select Play > Spawn Player At > Default Player Start, then Play.
Use a Development build: objective/guard feedback currently uses on-screen debug
messages, not a Shipping-ready HUD.

## Cook and package
Run after the build passes, from the same PowerShell session. Archive outside the
checkout; use an empty output folder for each validation run.

```powershell
$Archive = Join-Path (Split-Path $Project -Parent) '..\LanceSpearman-Windows-Test'
& "$UE\Engine\Build\BatchFiles\RunUAT.bat" BuildCookRun "-project=$Project" -noP4 -platform=Win64 -clientconfig=Development -build -cook -map=/Engine/Maps/Entry -stage -pak -archive "-archivedirectory=$Archive" -prereqs -utf8output
if ($LASTEXITCODE -ne 0) { throw 'Build/cook/package failed; inspect UAT log' }
```

Launch the archived Windows/LanceSpearman.exe with -log, independently of the editor.
Do not count PIE success as packaged-game success. Check the cook log for missing
Entry, Cube, Cylinder or Sphere packages. Fix errors before calling the build passed.

## Manual smoke test (PIE AND packaged Development)
- Start at approximately (-1700,-450,130), stand on the floor, and see lit stalls.
  No falling through the map, overlapping start, or missing-mesh warnings.
- WASD/mouse: move and look; Shift: sprint then release to walk; Space: jump/land.
- Gamepad: left/right sticks, left shoulder sprint, bottom face button jump,
  left face button interact. Check camera usability and dead zones.
- Contact is a default sphere near (-1000,300,140), **not a gold material**.
  Outside 240 cm, E must do nothing. Approach and press E: completion text appears
  once and the sphere disappears. This tests the contact only, not a full mission.
- Guards patrol and show alert text in range/line of sight; cover blocks detection.
- Stop/restart PIE, then close/relaunch the package: the contact must reset.
- Record collisions, camera clipping, dark areas and input failures.

For each run record commit SHA (git rev-parse HEAD), UE patch version, VS/MSVC/SDK,
Windows version, GPU/driver, build and UAT exit codes, and each result above.
Keep Saved/Logs and AutomationTool logs (the UAT console prints their location).
Do not commit generated files. Mark unrun steps NOT RUN; attach logs for failures.

## Remaining release blockers
The character has no visible skeletal mesh or animation. Guards are primitive,
non-navigation-aware stand-ins; the contact is a sphere. No dedicated authored map,
crowds, multi-stage mission, extraction, dialogue, proper HUD, pause/restart UI,
checkpoint system or production audio exists. Licensed art and performance/crash/
controller/accessibility QA are outstanding. There are no Unreal automation tests
or Windows CI yet. A successful clean Windows build, cook and both smoke runs are
still required before claiming this foundation playable.
