# Lance Spearman — PC-first production and future console strategy

## Product decision
- **First platform:** Windows PC, Unreal Engine 5.
- **Later platforms, only if validated by audience demand and economics:** PlayStation 5 and Xbox Series X|S.
- Do not promise console availability, certification, devkit access or a release date. Console development requires platform-holder approval, licensed SDKs/devkits, compliance testing and performance work.

## Release gates
1. **Prototype:** UE5 Windows project compiles, Level 1 controls and contact interaction verified on a real Windows machine.
2. **Vertical slice:** One polished, original Nairobi market mission with licensed character meshes and animations, crowd behavior, guard AI, stealth, dialogue, mission UI, audio and measured performance.
3. **PC alpha:** Seven levels of Chapter 1 with progression and QA, controller support and accessibility baseline.
4. **PC beta:** Stability, save/load, optimization, playtesting and store/distribution readiness.
5. **PC launch:** Review feedback, retention, crash reports, wishlist/sales and community demand.
6. **Console feasibility:** Evaluate platform-holder onboarding, licensing, Unreal platform support, memory/performance, controller/UI, save system, achievements/trophies, age ratings and certification cost.
7. **Console port:** Only after feasibility and budget approval; separate QA and release approvals.

## Cross-platform engineering rules starting now
- Keep mission logic platform-agnostic; avoid Windows-specific APIs in gameplay code.
- Use Unreal Engine input mappings, with future migration to Enhanced Input and full gamepad support.
- Target scalable visuals; profile GPU/CPU/memory before deciding performance budgets.
- Abstract saves, achievements, storefronts and user identity behind platform-neutral interfaces.
- Keep assets licensed for commercial PC **and potential console** use.
- Keep secrets, proprietary SDKs, devkit files and console documentation **out of public GitHub**.
- Plan for text size, safe areas, remapping, subtitles, colorblind options and controller navigation.

## Current technical reality
This repository contains an **unverified source-code foundation** with primitive blockout geometry and guard stand-ins. It is not an AAA game and has not been compiled or packaged. Realistic visuals require original/licensed assets, animation and substantial production resources.

## Immediate next tasks
1. Compile on Windows with UE 5.4 and fix any compile/runtime errors.
2. Create and save a dedicated market map; remove runtime blockout generation.
3. Import an appropriately licensed realistic character and locomotion animation set.
4. Build objective-state system, proper HUD and navigation-aware guard AI.
5. Add a short original soundtrack and ambient audio.
6. Run playtests and capture frame-time, crashes and usability feedback.
