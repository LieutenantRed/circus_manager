# Development Plan

## Direction and Current State

Build a Godot/C++ companion for a GM running the circus rules on Windows and an Android tablet. Interlude, Preparation, circus management, money management, and running a show have separate views. Players roll outside the app; the GM enters results and situational adjustments. Built-in rules follow the full circus rules in `Circus rules.pdf`, with explicit support for GM-created traits. The “Simplified Circus Rules” variant on printed page 67 is entirely out of scope: no full or partial use of that variant is planned. Milestones may deliver subsets of the app, but must not substitute simplified mechanics for unfinished full-rule features.

Existing work includes domain structures, derived prestige with source explanations, the trait catalog, signature-trick validation, domain tests, and the first menu milestone. The native Godot main scene, build tooling, Windows debug package, and Android debug APK are implemented. Saving remains pending.

The first milestone is a working menu. Later milestones are the proposed delivery sequence; detailed layouts and unresolved rules will be settled before their dependent work. No schedule estimates are assigned yet.

## Confirmed Workflow Baseline

Every committed game change takes effect immediately and must be reversible, except that finished shows cannot be modified through the interface. Show history is a core feature and is read-only for finished shows. Preserve the information needed for undo, calculations, and resume without requiring a visible action-history feature. Use the explicit Finish Show action on Results as the finalization boundary; define dependent undo behavior before implementing it, keeping finished records unchanged.

Prestige gets an explanatory popup. Complex rules get dedicated guided interfaces; trick creation uses several screens with detailed instructions. Include the relevant guidance with each feature, then refine it during usability work. Immediate commitment does not settle disk-save timing or autosave policy; these remain milestone 2 decisions.

Interlude is the confirmed between-show stage. Its dedicated interface provides recruitment, guided trick creation, PC level changes, permanent-upgrade purchases, explained adjustments to next-show Anticipation or circus Prestige, and personal-fund contributions into the circus budget. Preparation retains all Interlude operations, including permanent purchases, and adds promotion and temporary-upgrade purchases. Promotion and temporary purchases are unavailable in Interlude. Deliver these shared flows with their supporting milestones below; Show Time begins with backstage assignments and random events after Preparation purchases; other transition details remain open. See [Design Notes — Interlude Stage](design-notes.md#interlude-stage).

Show Time uses the approved dedicated setup → four acts → Results flow, with the current act prominent and a compact four-act overview. Management controls are hidden during the show; active-show corrections remain available until Finish Show creates the read-only record. See [Design Notes — Show Time Stage](design-notes.md#show-time-stage--approved).

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
- Save and load the circus's actors, upgrades, funds, unlocked traits, and available history data. Extend the schema as later milestones add Interlude adjustment sources, their reasons and target scope, and contribution records. Loading must not apply committed effects a second time.
- Connect Continue to a valid save and present understandable errors for missing or damaged data.
- Implement safe save replacement and recovery from interrupted writes. Decide save slots, autosave timing, and file import/export needs here.
- Add navigation destinations for Interlude, circus management, money, show preparation/running, and history; identify unfinished screens clearly. Interlude and Preparation link to the shared management flows as they become available.

**Complete when:** representative built-in and custom data survive a restart on both platforms, and failed loading does not overwrite good data.

## Milestone 3 — Actors, Signature Tricks, and Custom Traits

**Deliverable:** the GM can maintain the troupe and its repertoire.

- Build separate PC and NPC editing flows, accessible through both Interlude and Preparation for recruitment and PC level changes. PCs track relevant campaign values and progression; NPCs store their listed checks, fixed trick level/DC, and requirements.
- Build signature-trick creation/editing using check ownership, trait access, prerequisites, and progression limits. Use several guided creation screens with detailed instructions and an explicit commitment point. Enforce permitted redesign timing once downtime/level-up records are available.
- Provide a custom-trait editor with stable IDs, names, descriptions, supported bonus metadata, and prerequisites. Make the distinction between defining a trait and granting access visible.
- Retain trait unlocks when recording NPC recruitment. Define actor retirement/removal so historical references remain valid.
- Keep unsupported custom effects explicitly manual; descriptions must not imply automatic execution.

**Complete when:** the GM can create both performer types, update a PC's skills, recruit an NPC that unlocks a trait, and create a valid signature trick using a custom trait. Invalid selections produce actionable explanations.

## Milestone 4 — Money, Permanent Upgrades, and Prestige

**Deliverable:** a usable circus-management and money-management workflow.

- Define and implement a transaction ledger for purchases, income, and GM-recorded contributions/corrections. Both Interlude and Preparation must support deposits from PCs' personal funds into the circus budget, distinct from show income. Settle opening-balance and correction behavior before implementation.
- Add the permanent-upgrade catalog with prices, minimum Prestige, prerequisites, and ownership validation. Make permanent purchases available in both Interlude and Preparation; temporary upgrades are available only in Preparation. Record purchases and deductions together to prevent partial updates.
- Implement tier replacement effects correctly; retained purchase records must not cause cumulative seating or tent bonuses.
- Add explained GM-entered Prestige adjustments from Interlude or Preparation as distinct calculation sources. Display derived Prestige; tapping it opens the required popup showing every starting, upgrade, completed-show, and Interlude contribution with its reason.
- Keep payout-only modifiers separate from actual Prestige. Treat circus profits as already net of baseline operating expenses.

**Complete when:** purchases and personal contributions update funds once, invalid purchases are rejected, and an explained Interlude Prestige adjustment survives save/load and agrees with the popup. Committed changes remain reversible without changing finished shows. Use completed-show fixtures until live shows are implemented.

## Milestone 5 — Rules Resolution and Modifier System

**Deliverable:** tested calculations ready to drive a show.

- Resolve the documented ambiguities in [Rules Review](rules-review.md), including NPC clown actions and the Time trait. Record the adopted rulings.
- Supply the referenced level-based DCs, Aid rules, core roll-resolution rules, and external feat details needed by supported features.
- Finalize roll-entry data: normal character modifiers, GM adjustments, original die information, and bonus types. Avoid double counting and preserve information needed for critical results and stacking.
- Implement check outcomes, repeated-attempt penalties, source-attributed modifiers, trait effects, resource spending, and injury/recovery rules.
- Separate check modifiers from changes to DCs, actions, Anticipation, Excitement, capacity, or payout. Define the initial limits of custom-effect support.

**Complete when:** focused tests cover the PDF's worked examples and relevant boundaries, with explainable inputs and outputs. No automated roll-resolution path depends on an unresolved ruling.

## Milestone 6 — Show Preparation

**Deliverable:** prepare the circus state and purchases for entry into Show Time setup.

- Retain every Interlude operation in Preparation: recruitment, guided trick creation, PC level changes, permanent purchases, explained Anticipation/Prestige adjustments, and personal-fund contributions. Reuse the existing management records and validation.
- Model the six preparation days, advertising purchase order, promotion attempts/Aid, and the one-show-per-week restriction. Define the transition from Interlude without assuming Interlude itself lasts six days.
- Add temporary upgrades in show preparation, including merchandise carryover and purchase restrictions; they cannot be bought in Interlude.
- Hand off purchased upgrades and preparation inputs to Show Time without reapplying them. Backstage assignments and random events belong to Show Time setup in milestone 7.
- Allow explained next-show Anticipation adjustments in both Interlude and Preparation, retaining each original source. Apply the normal Anticipation expiry and capacity rules to these entries. Define target-show assignment and cancellation/postponement handling within those rules before automating their lifecycle. Preserve the inputs and source contributions needed to derive starting values after Show Time setup, without reapplying an existing entry. Stage transitions alone must not restart expiry; management changes during Preparation must be reflected in the current derived state.

**Complete when:** Preparation provides all Interlude operations plus promotion and temporary upgrades, provides valid, explainable inputs for Show Time setup using current management data, and survives save/reload and stage navigation without repeating costs or applying effects twice.

## Milestone 7 — Run a Complete Show

**Deliverable:** the GM can complete Show Time setup and run all four acts through the dedicated interface.

- Implement Show Time setup: review purchased upgrades, assign eligible backstage PCs, enter externally rolled random events and required choices, resolve performer availability, and establish starting values. Follow the PDF's order and exceptions without repeating purchases or effects.
- Display circus name, settlement, and campaign date. Keep current Excitement, Anticipation, maximum Anticipation, and Prestige visible, with starting values preserved separately and the Prestige popup available.
- Use the approved current-act layout with a compact four-act overview and the 1/2/1/3 trick-slot sequence. Choose performers at each act's start; validate ownership, availability, and reuse restrictions or exceptions and explain unavailable choices. Keep every performer in the current act accessible.
- Hide management controls during Show Time, including recruitment, level changes, trick creation/editing, and purchases. Retain corrections to the active show.
- Support shared PC/NPC performance processing with their distinct action permissions. Display performer/trick names, level, traits, DC, check choices, remaining actions, repeat penalties, and effects. Provide Costar, clowns, skip, and applicable backstage controls with their rule timing and eligibility.
- Handle check selection, assistance, resource choices, external roll entry, and commitment through milestone 5's rules system. Apply results immediately, preserve inputs, show compact current-act action/result rows and value changes, and prompt for injury checks or other required decisions. Do not silently resolve the open Time/NPC-clown rulings or roll-entry contract.
- Design and test drag-and-drop assignment alongside an equivalent touch-friendly selection method.
- Save the active show's progress. Apply committed actions immediately and support reversing or correcting them before show finalization, without silently rerolling results or spending resources twice. Define how dependent changes are reversed; a visible action-history log is not required.

**Complete when:** a representative show proceeds from setup through the finale in the approved layout, including backstage effects and a random event, and resumes correctly after closing the app or suspending the tablet. Management controls remain unavailable during Show Time while active-show corrections work.

## Milestone 8 — Settlement and Historical Records

**Deliverable:** finished shows update the circus and remain understandable later.

- Present Results with final Excitement/Anticipation, failure/success/exact-match critical success, payout explanation, and earned Prestige. Apply the appropriate formulas, rounding, and event modifiers; allow corrections before finalization.
- Provide an explicit Finish Show action that commits the payout, show history, and earned Prestige exactly once and creates the read-only historical record. Use Prestige from before the current show's award for payout; viewing Results before or after finalization never repeats settlement.
- Preserve historical actor/check/modifier values so later character progression or catalog changes do not rewrite past shows.
- Build the required history list and read-only show-detail view, including results, payout explanation, and Prestige contribution. Finished shows cannot be edited, deleted, or reopened for modification through the interface.
- Carry forward injury/recovery and merchandise state. Keep corrections consistent with balance and derived Prestige before finalization. Later current-state changes must preserve finished-show records; define dependent undo behavior at this boundary before implementation.

**Complete when:** the full preparation → show → settlement → next-show cycle works. Reloading or viewing results never duplicates income or awards. Finished shows remain read-only, including after changes to current actor, trick, trait, or upgrade data.

## Milestone 9 — Usability, Reliability, and Release Builds

**Deliverable:** a tested GM companion suitable for actual sessions on both platforms.

- Refine the required Prestige popup, guided interfaces, and read-only show history using session feedback. Assess action previews, touch-control details, and brief animations from [Design Notes](design-notes.md). A visible action-history feature is not required; guidance and explanations are already part of the earlier feature milestones.
- Test tablet sizing, on-screen keyboard behavior, mouse/touch parity, app suspension, and interrupted saves.
- Run representative sessions covering PC progression, custom traits, upgrade tiers, failures, critical successes, and resuming across several shows.
- Finalize reproducible Windows/Android exports, deployment/signing configuration, installation instructions, save compatibility, and known limitations.

**Complete when:** agreed acceptance scenarios pass on Windows and the target tablet, data survives lifecycle tests, and installable builds plus concise operating instructions are available.

## Working Sequence and Validation

Implement milestones in order. Apply the confirmed workflow baseline to each new feature, including immediate commitment and reversibility with the finished-show exception. Reuse the existing domain tests throughout; add focused tests for new rules and persistence behavior. Exercise UI changes in Godot and on the tablet rather than relying only on headless checks. Keep Android build smoke checks working from milestone 1 onward.

Domain code remains independent of presentation. Keep [Circus Structures](circus-structures.md), [Trick Traits](trick-traits.md), and [Rules Review](rules-review.md) current as each milestone replaces a documented gap with implemented behavior. Explained Anticipation/Prestige adjustments in both Interlude and Preparation are confirmed scope. Other GM overrides remain a later design decision; neither Interlude nor custom-trait support implicitly authorizes them.
