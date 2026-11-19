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

## Contracts, dollars and points — November 19, 2026
**User requirement:** Lance accepts contracts to complete assignments. Successful completion awards dollars and points.
**Status:** design only; contract selection, wallet, scoring, reward persistence and reward UI are not implemented.

### Proposed rules
- Dollars are fictional in-game currency, with no real-money payout or cash value.
- Show each contract's assignment, completion conditions, dollar reward and points before acceptance.
- For Nairobi Level 1, require the encounter to be cleared, the package collected and successful extraction before awarding the contract.
- Award the completion payout once per contract in a campaign save. Replaying a completed contract is practice and does not grant the base payout again.
- Failed, abandoned or restarted attempts do not award a completion payout.
- Keep dollars and points separate: dollars support future equipment, ammunition and Tony's Garage services; points record mission achievement and progression. Spending and unlock systems remain planned.
- Display a completion receipt with contract name, dollars earned, points earned and updated totals.
- Reward amounts, bonus criteria, prices and progression thresholds remain to be balanced.

### Implementation requirements
- Give each contract a stable identifier and explicit available, active and completed states.
- Persist completed contract identifiers and balances together in one save record; do not mark the reward delivered independently of the recorded balance.
- Route all rewards through one completion operation that rejects duplicate completion calls.
- Validate loaded balances and contract identifiers; handle missing or damaged saves explicitly.
- Mission restart resets the encounter without erasing previously earned campaign rewards.

### Acceptance checks — not yet run
- Picking up the package alone grants no reward; valid extraction grants the displayed dollars and points.
- Repeated extraction input, completion callbacks, reloads and replays cannot duplicate the base payout.
- Failure and restart preserve prior earnings and do not award the current incomplete contract.
- Save and reload preserve the completed contract and both totals consistently.
- The completion receipt matches the persisted balances.

## Lance's garage, pursuits and Tony's Bank — November 19, 2026
**User requirements:** Lance is a detective in Nairobi City who follows bandits attempting to steal from Tony's Bank. His garage holds his Peugeot 504 and Harley-Davidson motorcycle, used to travel to assignments. Hostile cars trail him and ram his car to stop him. After pursuit damage, he must repair his car at the garage before proceeding to the mission.
**Status:** narrative and gameplay requirements only. These vehicles, driving, pursuit AI, vehicle damage, repair gating, bank environment and detective investigations are not implemented in the UE5 slice.

### Location and story integration
- Treat the previously named Tony's Garage as Lance's home garage and repair base.
- Add Tony's Bank as a Nairobi story location and investigation client.
- Use clues, surveillance and following suspects to establish which bandits are planning a robbery; build assignments around investigating and stopping those attempts.
- Preserve the existing courier mission as the introductory assignment. Connect its clues to the bank plot through authored story content rather than claiming that content already exists.

### Vehicle and mission flow
1. Accept a detective contract and select the Peugeot 504 or Harley-Davidson at Tony's Garage.
2. Travel toward the assignment, with readable pursuit cues when hostile vehicles begin following Lance.
3. Attackers attempt to intercept and ram the car. Vehicle damage affects its condition and is displayed clearly.
4. After pursuit damage requiring repair, the mission objective changes to returning to Tony's Garage. Arrival at the assignment cannot bypass the repair requirement.
5. Complete a repair, restore roadworthiness and resume the same contract without losing investigation progress.
6. Complete the contract to receive the previously specified dollars and points.

### Proposed implementation rules
- Persist each owned vehicle's condition independently; switching vehicles must not silently clear an active required-repair objective.
- Separate cosmetic scuffs from damage that triggers mandatory repair. Thresholds and collision tuning require playtesting.
- Apply collision damage from meaningful impacts with a cooldown to prevent one prolonged contact from draining condition every frame.
- Provide recovery/towing to the garage if the car cannot move. An introductory repair or recovery must remain available when Lance lacks dollars, so the mission cannot become permanently blocked.
- Show the repair cost and resulting condition before confirmation. Deduct payment and restore condition together; reject duplicate repair requests.
- Pause pursuit and repair timers with the game. Restart/reload rules must preserve saved vehicle ownership, balances and contract progress consistently.
- Motorcycle pursuit, rider falls and recovery need separate handling and animation; do not reuse car collision behavior without validation.
- Production Peugeot 504 and Harley-Davidson models, branding treatment, vehicle physics, audio and animation assets remain external asset/integration work.

### Acceptance checks — not yet run
- Both owned vehicles appear at the garage and can be selected, entered, driven and exited safely.
- Pursuers follow roads, avoid walls and civilians, and produce readable interception attempts without teleporting into Lance.
- A qualifying ram changes condition once per damage interval and activates the garage objective.
- The assignment stays blocked until the required repair completes; changing vehicles, restarting or reloading cannot bypass it.
- Repair restores the correct vehicle, charges the displayed amount once and resumes the same assignment.
- A disabled vehicle and an empty wallet have a usable recovery path.
- Bank investigation clues and suspect-following objectives advance in order and survive the intended save/reload flow.
