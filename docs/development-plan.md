# Development Plan

## Direction and Current State

Build a Godot/C++ companion for a GM running the circus rules on Windows and an Android tablet. Circus management, money management, and running a show have separate views. Players roll outside the app; the GM enters results and situational adjustments. Built-in rules follow `Circus rules.pdf`, with explicit support for GM-created traits.

Existing work includes domain structures, derived prestige with source explanations, the trait catalog, signature-trick validation, domain tests, and the first menu milestone. The native Godot main scene, build tooling, Windows debug package, and Android debug APK are implemented. Saving remains pending.

The first milestone is a working menu. Later milestones are the proposed delivery sequence; detailed layouts and unresolved rules will be settled before their dependent work. No schedule estimates are assigned yet.

## Milestone 1 — Working Main Menu

**Deliverable:** the application starts at a usable menu on both target platforms.

**Status:** implemented and validated on Windows; signed ARM64 Android APK prepared. Physical-tablet testing is deferred at the user's request. Menu interaction tests and landscape/portrait rendering checks pass. See [README](../README.md) for build/run instructions.

- Establish the C++ build and Godot integration, with compatible engine/binding versions and reproducible build instructions.
- Create and assign a main scene displaying the game title and menu controls.
- Provide **New Circus**, **Continue**, and desktop **Quit**. New Circus opens a minimal naming form and creates an in-memory circus, then opens a basic management shell. Continue remains disabled until save support arrives in milestone 2.
- Support returning from the naming form or shell to the menu. Handle Android Back consistently.
- Establish basic mouse, keyboard, and touch navigation with readable, resizable controls. Decide menu styling here; defer detailed management/show layouts.
- Produce a Windows build and an Android test build early to verify that the native C++ component loads on both.

**Complete when:** both builds launch the menu, New Circus creates an in-memory record, back navigation works, unavailable actions are clearly disabled, and no input requires a mouse hover. Closing the app does not yet preserve the circus.

## Milestone 2 — Saved Circus and Application Navigation

**Deliverable:** create a circus, close the app, and continue it later.

- Define a versioned save format with stable IDs and validation on load, including custom trait definitions and their prerequisite references.
- Save and load the circus's actors, upgrades, funds, unlocked traits, and available history data. Extend the schema as later milestones add records.
- Connect Continue to a valid save and present understandable errors for missing or damaged data.
- Implement safe save replacement and recovery from interrupted writes. Decide save slots, autosave timing, and file import/export needs here.
- Add navigation destinations for circus management, money, show preparation/running, and history; identify unfinished screens clearly.

**Complete when:** representative built-in and custom data survive a restart on both platforms, and failed loading does not overwrite good data.

## Milestone 3 — Actors, Signature Tricks, and Custom Traits

**Deliverable:** the GM can maintain the troupe and its repertoire.

- Build separate PC and NPC editing flows. PCs track relevant campaign values and progression; NPCs store their listed checks, fixed trick level/DC, and requirements.
- Build signature-trick creation/editing using check ownership, trait access, prerequisites, and progression limits. Enforce permitted redesign timing once downtime/level-up records are available.
- Provide a custom-trait editor with stable IDs, names, descriptions, supported bonus metadata, and prerequisites. Make the distinction between defining a trait and granting access visible.
- Retain trait unlocks when recording NPC recruitment. Define actor retirement/removal so historical references remain valid.
- Keep unsupported custom effects explicitly manual; descriptions must not imply automatic execution.

**Complete when:** the GM can create both performer types, update a PC's skills, recruit an NPC that unlocks a trait, and create a valid signature trick using a custom trait. Invalid selections produce actionable explanations.

## Milestone 4 — Money, Permanent Upgrades, and Prestige

**Deliverable:** a usable circus-management and money-management workflow.

- Define and implement a transaction ledger for purchases, income, and GM-recorded contributions/corrections. Settle opening-balance and correction behavior before implementation.
- Add the permanent-upgrade catalog with prices, minimum Prestige, prerequisites, and ownership validation. Record purchases and deductions together to prevent partial updates.
- Implement tier replacement effects correctly; retained purchase records must not cause cumulative seating or tent bonuses.
- Display derived Prestige. Tapping it opens the required popup showing every starting, upgrade, and completed-show contribution.
- Keep payout-only modifiers separate from actual Prestige. Treat circus profits as already net of baseline operating expenses.

**Complete when:** purchases update ownership and funds once, invalid purchases are rejected, and the displayed Prestige agrees with its explanation after saving/loading. Use completed-show fixtures until live shows are implemented.

## Milestone 5 — Rules Resolution and Modifier System

**Deliverable:** tested calculations ready to drive a show.

- Resolve the documented ambiguities in [Rules Review](rules-review.md), including NPC clown actions and the Time trait. Record the adopted rulings.
- Supply the referenced level-based DCs, Aid rules, core roll-resolution rules, and external feat details needed by supported features.
- Finalize roll-entry data: normal character modifiers, GM adjustments, original die information, and bonus types. Avoid double counting and preserve information needed for critical results and stacking.
- Implement check outcomes, repeated-attempt penalties, source-attributed modifiers, trait effects, resource spending, and injury/recovery rules.
- Separate check modifiers from changes to DCs, actions, Anticipation, Excitement, capacity, or payout. Define the initial limits of custom-effect support.

**Complete when:** focused tests cover the PDF's worked examples and relevant boundaries, with explainable inputs and outputs. No automated roll-resolution path depends on an unresolved ruling.

## Milestone 6 — Show Preparation

**Deliverable:** prepare a valid show from the saved circus state.

- Model the six preparation days, advertising purchase order, promotion attempts/Aid, and the one-show-per-week restriction.
- Add temporary upgrades, including merchandise carryover and purchase restrictions.
- Assign eligible PCs to backstage roles, enforcing role exclusivity, prerequisites, and the restriction against also performing.
- Record externally rolled random events and resource outcomes; apply their effects in the PDF's preparation order, including event-specific exceptions.
- Derive starting Anticipation, Excitement, capacity, performer availability, and relevant modifiers from their sources.

**Complete when:** preparation produces a valid, explainable starting state and survives save/reload without repeating costs or applying effects twice.

## Milestone 7 — Run a Complete Show

**Deliverable:** the GM can run all four acts from the show interface.

- Implement the 1/2/1/3 trick-slot sequence, choosing performers at each act's start and validating ownership, availability, and reuse restrictions or exceptions.
- Support shared PC/NPC performance processing with their distinct action permissions. Track actions, reactions, assistance, clowns, resources, and injuries.
- Enter player rolls and resolve them through milestone 5's rules system. Update the show values and preserve the calculation inputs.
- Design and test drag-and-drop assignment alongside an equivalent touch-friendly selection method.
- Save the active show's progress. Define correction/undo behavior so correcting an entry cannot silently reroll results or spend resources twice.

**Complete when:** a representative show runs from opener to finale, including backstage effects and a random event, and resumes correctly after closing the app or suspending the tablet.

## Milestone 8 — Settlement and Historical Records

**Deliverable:** finished shows update the circus and remain understandable later.

- Calculate failure, success, or exact-match critical success and apply the appropriate payout formula, rounding, and event modifiers.
- Use Prestige from before the current show's award, then record payout, show history, and earned Prestige exactly once.
- Preserve historical actor/check/modifier values so later character progression or catalog changes do not rewrite past shows.
- Build the history list and show-detail view, including results, payout explanation, and Prestige contribution.
- Carry forward injury/recovery and merchandise state. Make corrections consistent across history, balance, and derived Prestige.

**Complete when:** the full preparation → show → settlement → next-show cycle works. Reloading or reopening results never duplicates income or awards.

## Milestone 9 — Usability, Reliability, and Release Builds

**Deliverable:** a tested GM companion suitable for actual sessions on both platforms.

- Revisit the deferred priorities in [Design Notes](design-notes.md): number explanations, action previews, touch controls, brief animations, and action history. Select and refine them using session feedback.
- Test tablet sizing, on-screen keyboard behavior, mouse/touch parity, app suspension, and interrupted saves.
- Run representative sessions covering PC progression, custom traits, upgrade tiers, failures, critical successes, and resuming across several shows.
- Finalize reproducible Windows/Android exports, deployment/signing configuration, installation instructions, save compatibility, and known limitations.

**Complete when:** agreed acceptance scenarios pass on Windows and the target tablet, data survives lifecycle tests, and installable builds plus concise operating instructions are available.

## Working Sequence and Validation

Implement milestones in order. Reuse the existing domain tests throughout; add focused tests for new rules and persistence behavior. Exercise UI changes in Godot and on the tablet rather than relying only on headless checks. Keep Android build smoke checks working from milestone 1 onward.

Domain code remains independent of presentation. Keep [Circus Structures](circus-structures.md), [Trick Traits](trick-traits.md), and [Rules Review](rules-review.md) current as each milestone replaces a documented gap with implemented behavior. Broader GM overrides remain a later design decision; they are not implied by custom-trait support.
