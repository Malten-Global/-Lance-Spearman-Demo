# Chapter 1 / Level 1 — Arrival at the Market

**Location:** Fictionalized Nairobi market district. **Tone:** grounded espionage thriller. **Camera:** over-the-shoulder third person.

## Player goal
Lance arrives in Nairobi to identify a courier contact without drawing the attention of Victor Kane's watchers.

## Intended polished mission flow (design, not all implemented)
1. Opening establishing shot, clear movement tutorial.
2. Enter the market and blend into a moving civilian crowd.
3. Find a coded clue from a stallholder.
4. Identify the courier using dialogue and environmental observation.
5. Avoid suspicious guards; detection increases risk but should not automatically fail.
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
**Implemented as code, unverified:** movement, camera, sprint, jump, a single contact marker, generated market blockout and a basic patrol/detection actor.
**Not implemented:** realistic meshes, animation, crowd system, mission stages, dialogues, extraction, cinematic cutscenes, soundtrack, checkpointing, boss encounter.
