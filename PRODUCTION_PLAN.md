# Lance Spearman: Shadows of Africa — Production Plan

Status: development specification; features below are planned, not implemented.

## Core loop
Explore a recognizable African city; investigate clues; meet and question NPCs; follow leads; defeat a chapter-specific boss to unlock the next chapter; earn in-game digital dollars.

## Campaign (10 chapters)
1. The Missing Courier — Nairobi
2. The Warehouse Conspiracy — Nairobi
3. The Cipher Exchange — Nairobi
4. Shadows Over Mombasa — Mombasa
5. The Lagos Connection — Lagos
6. The Accra Files — Accra
7. The Johannesburg Syndicate — Johannesburg
8. The Midnight Express — Southern Africa
9. Operation Black Spear — secret mountain compound
10. The Final Reckoning — Nairobi

## Required systems
- Human character models, locomotion, dialogue, pedestrians, and NPC schedules.
- Road-following traffic, signals, pedestrian crossings, collision detection, enterable vehicles.
- Landmark-informed open-world neighborhoods; discoverable fast travel; road and air travel transitions.
- Player combat: strike, block, dodge, counter, takedown; stamina and health; boss phases and checkpoints.
- One unique boss per chapter; boss defeat gates chapter completion.
- Difficulty: Novice default, Agent, Veteran; keep difficulty choice separate from player progression.
- Digital dollar collectibles: 10/50/100; mission 500; chapter 1000; boss bonus 1000. In-game only, no cash value.
- HUD, objectives, navigation, save/load, accessibility, performance budgets.

## Development sequence
1. Preserve existing public prototype and verify current controls, save, and mission completion.
2. Implement boss gate and rewards in a small vertical slice of Chapter One.
3. Improve traffic collision and pedestrian pathfinding.
4. Replace placeholders with licensed 3D assets and animation.
5. Expand Nairobi block by block; test performance and geography.
6. Build chapters 2–10, travel systems, and quality assurance.
7. Implement storefront, Stripe checkout with secure server-side fulfillment, licensing and distribution; do not publish secrets to GitHub Pages.

## Release criteria
Do not sell the game until core chapters, payments, downloads/access, save persistence, accessibility, security, asset rights, and cross-device testing pass. The GitHub Pages demo remains free while developing.
