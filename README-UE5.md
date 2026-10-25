# Lance Spearman — Unreal Engine 5 Windows PC vertical slice

This is the **start of the native UE5 production implementation** for Chapter 1 Level 1, not a finished Hitman/GTA-scale game.

## Setup
1. Install Unreal Engine **5.4** and Visual Studio 2022 with **Game development with C++**.
2. Clone this branch, right-click `LanceSpearman.uproject`, choose **Generate Visual Studio project files** (Windows Unreal integration required).
3. Open `LanceSpearman.uproject`, allow Unreal to compile, then press **Play** in the editor.
4. Controls: WASD move, mouse look, Left Shift sprint, Space jump, E interact.
5. Walk to the gold objective at the market and press E to complete **Level 1: Arrival at the Market**.

## Implemented foundation
- Native UE5 C++ game module and game/editor targets
- Third-person controllable character and camera with movement and sprint
- Generated blockout Nairobi market district with street and stalls
- Pedestrian patrol stand-ins and gold contact objective
- Contact interaction, objective progress and on-screen completion feedback

## Production art/engineering backlog
- Import properly licensed rigged human character meshes, skeletal animations, facial animation and dialogue
- Replace primitives with authored Nairobi streets, stalls, signage, ambient crowds, taxis and traffic
- Implement proper pedestrian navmesh, animation blueprints, AI perception, dialogue and mission UI
- Add stealth, combat, driving, cutscenes, audio and full Level 2–7 systems
- Add Unreal automated tests, packaging and CI; run a Windows build/test before claiming playable

**Important:** No Unreal Editor or Windows build is available in this execution environment. Compilation and gameplay are **not verified**. The original browser prototype remains separate in `chapter1/`.
