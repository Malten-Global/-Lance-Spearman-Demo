# Lance Spearman — Chapter 1 Prototype (Phases 2 & 3)

## Run
Open `chapter1/index.html` via a local HTTP server (e.g. `python -m http.server 8000` from repository root), then visit `http://localhost:8000/chapter1/`. Requires internet for the Three.js module CDN.

## Controls
WASD / arrows: move; Shift: sprint; E or Interact: collect objective; Space / Evade: temporary protection; mouse drag: rotate camera; Restart level: retry current mission.

## Seven missions
1. Arrival at the Market — contact
2. The Suspicious Package — two receipts
3. Taxi Stand Pursuit — three checkpoints
4. Warehouse Shadows — two cameras and informant
5. The Encrypted Ledger — three ledger fragments
6. Kane's Security Compound — three jammers
7. Victor Kane: Final Confrontation — three relays then Kane

## Phase 3 validation checklist
- [ ] Load in Chrome and Edge without errors
- [ ] Confirm camera follows Lance at ground level
- [ ] Verify WASD/arrows and Shift
- [ ] Verify E only collects a nearby objective
- [ ] Verify guards return player to spawn on detection
- [ ] Verify all seven levels advance sequentially
- [ ] Verify localStorage restores the unlocked level on reload
- [ ] Verify final Kane objective is gated behind three relays
- [ ] Verify final victory message
- [ ] Test mobile controls and performance (not yet implemented)

## Known limitations
This is an early 3D gameplay scaffold: geometric placeholder characters, static block buildings, simplified patrol detection, no voice acting, no combat animations, no drivable vehicles, no sound, no realistic market crowds, no proper line-of-sight AI, no automated browser test harness. Mission completion is interaction-based. The first six levels automatically transition; the seventh ends at victory. Progress uses browser localStorage.

## Production acceptance criteria
Add GLTF characters and animation, detailed Nairobi environments, collision and navigation, branching dialogue, actual taxi chase, cameras and hacking puzzles, boss health phases, original soundtrack, accessibility options, mobile controller UI, browser automated tests, and deployment pipeline before production release.
