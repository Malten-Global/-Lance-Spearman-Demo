# Chapter 1 / Level 1 — Arrival at the Market

**Location:** Fictionalized Nairobi market district. **Tone:** grounded espionage thriller. **Camera:** over-the-shoulder third person.

## Player goal
Lance arrives in Nairobi to identify a courier contact without drawing the attention of Victor Kane's watchers.

## Intended polished mission flow (design, not all implemented)
1. Opening establishing shot, clear movement tutorial.
2. Enter the market and blend into a moving civilian crowd.
3. Find a coded clue from a stallholder.
4. Identify the courier using dialogue and environmental observation.
5. Confront the attackers guarding the courier route. Defeat the encounter using martial arts, with occasional firearm use against armed attackers.
6. Receive the encrypted package and reach an extraction point.
7. Closing scene reveals Victor Kane's network and unlocks Level 2.

## Quality bar
- No top-down view; natural behind-character camera.
- Realistic human silhouettes, movement and responsive controls.
- Clear objectives and interact prompts; no guessing what key to press.
- Pedestrians react believably; no constant overlapping dialogue.
- Multiple routes, readable stealth feedback and checkpointing.
- One original signature theme, adapted to exploration and danger.

## Current implementation versus design
**Implemented as code, unverified in Unreal:** movement, camera, sprint, jump, pause, restart, contact pickup and extraction, objective HUD, generated market blockout, guard patrol/detection and collision, short-range punches with cooldown and obstruction checks, three-hit guard defeat, and a guard-clear requirement before pickup.
**Not implemented:** realistic skeletal meshes and combat animation, enemy damage/attacks, player health and defeat, weapons, firearm aiming/shooting/ammunition, blocking/dodging/disarming, navigation routing, authored map, crowd system, dialogue, cinematic cutscenes, soundtrack and checkpointing.
No successful UE5.4 compilation, packaged Windows run or gameplay verification is recorded here.

## Combat direction — November 19, 2026
User requirement: attackers carry improvised weapons and guns to stop Lance reaching mission objectives. Lance primarily uses martial arts and sometimes shoots armed attackers.

### Planned encounter progression
1. Introduce an unarmed attacker and teach close-range strikes and defensive movement.
2. Introduce attackers with clubs or similar improvised weapons, with readable attack windups and recovery windows.
3. Introduce an armed attacker with cover available; teach aiming, firing and limited ammunition.
4. Combine enemy types near the objective while keeping an accessible route and clear objective feedback.

### Implementation sequence
- Build the shared health/damage/defeat system first. Prevent attacks during pause or after defeat; offer restart after Lance is defeated.
- Add enemy melee attacks, approach movement, attack cooldowns, obstruction checks and hit reactions. Use animation-timed strikes when production animation assets are integrated.
- Add Lance's martial-arts combinations, dodge/block and optional disarm moves.
- Add firearms with aiming, ammunition, reload, impact feedback and shots blocked by world geometry. Give armed enemies readable warnings and finite firing cadence.
- Integrate the encounter with objective clearance and reset all actors, health and ammunition on mission restart.
- Replace stand-ins with licensed character/weapon assets and authored animation; tune difficulty through Windows playtests.

### Acceptance checks — not yet run
- Weapons cannot damage Lance through walls, outside attack range, during pause or after the attacker is defeated.
- Lance cannot hit an enemy behind an obstruction; a single attack cannot repeatedly apply damage each frame.
- Incoming attacks visibly affect health; defeat disables combat and interaction while retaining restart.
- Gunfire consumes ammunition, empty weapons cannot fire, and reload respects the selected rules.
- The objective stays locked while required attackers remain, then unlocks after the encounter.
- Restart restores the initial encounter, health, ammunition and objective state.
- Test in both PIE and a packaged UE5.4 Win64 build, including low frame rates.
