# Design Notes

See [Development Plan](development-plan.md) for the staged roadmap, beginning with a working main menu.

Milestone 1 now has a native C++ menu, naming form, and in-memory overview. Windows and Android debug packages are available; tablet testing is deferred at the user's request. Continue stays disabled until persistence is implemented. Returning to the menu preserves the active in-memory circus. The broader management/show interfaces remain future work.

## Confirmed Direction

- Build a GM companion mini-game for managing a Pathfinder circus during a tabletop campaign.
- Use Godot with C++, targeting Windows and Android tablets.
- Track the circus's current money, performer roster, and show history.
- Derive prestige from its sources, including starting prestige, permanent upgrades, and completed shows. Tapping the value must open a popup explaining every contribution. This specific interaction is confirmed even though broader UI design remains deferred.
- Distinguish player-character performers from NPC performers. Both participate in the same show routine, with different abilities, data, and management needs.
- Provide separate interfaces for running a show, managing the circus, and managing money. Their layouts remain undecided.
- Follow `Circus rules.pdf` faithfully. Possible future GM override fields are an extension to assess later, not permission to change the default rules.
- Players make rolls outside the app. The GM enters the roll with any GM-decided situational adjustment included. The app applies applicable bonuses from tracked sources such as show events and inventory, then calculates the result and its consequences.
- Use a simple 2D presentation with animations, drag-and-drop elements, and interfaces that calculate values from entered game data. Detailed UI design is deferred.

## Player Characters and NPC Performers

Use "player" for a person at the table, "PC" for their character, and "NPC" for a non-player character. Players can use NPC performers to fill show slots; who handles a roll does not change the performer's type.

Confirmed requirements:

- NPC performers have a compact set of available checks (for example, one or two) and one assigned trick. Their records must support the trick's requirements.
- PCs can perform their own signature tricks or take backstage roles with separate mechanics.
- PCs need a signature-trick creation and editing interface, following the rules for available checks, traits, progression, and redesign.
- Trick traits now have a typed catalog and draft-validation helpers. See [Trick Traits](trick-traits.md) for the full PDF list, PC progression limits, NPC unlocks, and compulsory tags. The creation interface and runtime effects remain deferred.
- The GM must be able to create custom trait definitions in the app. The extensible catalog API now supports selectable custom traits with stable IDs, descriptions, and prerequisites. These additions remain distinct from the built-in PDF rules and use normal PC trait limits. Defining a trait and unlocking it for PCs are separate operations.
- PC skills can improve through campaign progression outside circus management. Circus calculations must use their updated values; the mechanism for maintaining those values remains to be decided.
- Both performer types follow the same act and check-resolution flow, while retaining their respective restrictions.

Relevant PDF constraints: a PC taking a non-performer role cannot also perform in that show; NPCs cannot take those roles or Costar. NPC trick levels remain fixed, while PC signature tricks scale with their character's level. Do not impose an arbitrary two-check limit on all NPC tricks; the PDF allows NPC trick definitions to specify their checks.

Proposed organization, pending detailed design:

- Keep persistent character/performer information separate from each show's participation record.
- A PC profile holds the character values needed for circus rules and their editable signature trick. An NPC profile holds their assigned trick, available check modifiers, and requirements.
- A show participation record refers to either type and tracks the act assignment, actions, checks, and show effects; backstage assignments apply only to eligible PCs.
- Preserve the values used for completed shows so later character progression does not alter show history.

The current C++ types and validation constraints are documented in [Circus Structures](circus-structures.md). [Rules Review](rules-review.md) lists additional records still needed and source ambiguities; shared show processing does not imply identical action permissions for PCs and NPCs.

## Roll Resolution

Confirmed input direction: enter a numeric roll rather than only a degree of success. GM situational bonuses can be included directly in the entered value; the app must not apply them a second time.

The intended flow is: entered roll with GM adjustment → apply relevant tracked modifiers under the rules → resolve the check → update show values. Event and inventory modifiers should come from the active game state. The exact bonus system and inventory scope are still to be designed.

For later design, define whether the performer's normal check modifier is stored and applied automatically or included in the entered value. Also decide how to preserve the unadjusted die result when the entered value includes a GM bonus. These details remain open; no input layout is selected yet.

## Interface Ideas to Assess Later

These are discussion candidates, not an approved implementation checklist. Revisit them when UI work begins.

Exception: the prestige explanation popup is now a confirmed requirement. Its underlying structures are described in `docs/circus-structures.md`.

| Idea | Intended benefit |
| --- | --- |
| Explainable numbers | Select a value to inspect its base, modifiers, and sources. |
| Action previews | Show the difficulty, repeat penalty, and possible consequences before committing an action. |
| Touch-friendly controls | Support dragging and a tap-card/tap-slot alternative on tablets. |
| Brief feedback animations | Use moving counters, spotlights, card reactions, and applause to make changes easier to follow. |
| Autosave and a show log | Preserve progress between tabletop sessions and make past actions reviewable. |

Other deferred presentation ideas: performer cards; an act board with 1, 2, 1, and 3 trick slots; a provisional lineup editable until each act begins; a six-day preparation schedule; and a payout breakdown. Show history is confirmed scope, while the detail and presentation of an action log are undecided.

## Rules and Scope Notes

- The detailed outcome rules on printed page 67 make equal Excitement and Anticipation a critical success; higher Excitement is a success, and lower Excitement is a failure.
- The PDF references external Pathfinder rules, including level-based DCs and Aid, and NPC trick descriptions that are not included in the file. Identify these dependencies before implementing full calculation support.
- The previously suggested one-show prototype is a proposal awaiting scope agreement.

## Open Mechanics Questions

- Where is the performer's normal check modifier applied, and how is the unadjusted die result retained alongside any GM adjustment?
- Which PC values should the tool maintain, and how are changes from external campaign progression entered?
- What additional performer and trick fields are needed beyond the PC/NPC distinction above?
- How should money changes be recorded, including purchases, show payouts, and contributions from adventuring funds?
- What information must completed shows preserve, and how should corrections affect their records and the current circus state?
- Which GM override fields, if any, belong in a later version?
