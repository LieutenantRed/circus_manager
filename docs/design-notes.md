# Design Notes

See [Development Plan](development-plan.md) for the staged roadmap, beginning with a working main menu.

Milestone 1 now has a native C++ menu, naming form, and in-memory overview. Windows and Android debug packages are available; tablet testing is deferred at the user's request. Continue stays disabled until persistence is implemented. Returning to the menu preserves the active in-memory circus. The broader management/show interfaces remain future work.

## Confirmed Direction

- Build a GM companion mini-game for managing a Pathfinder circus during a tabletop campaign.
- Use Godot with C++, targeting Windows and Android tablets.
- Track the circus's current money and performer roster. Show history is a core feature; finished shows are read-only through the interface. A visible action-history feature is not required.
- Derive prestige from its sources, including starting prestige, permanent upgrades, completed shows, and explained GM-entered Interlude adjustments. Tapping the value must open a popup explaining every contribution. This specific interaction is confirmed even though broader UI design remains deferred.
- Distinguish player-character performers from NPC performers. Both participate in the same show routine, with different abilities, data, and management needs.
- Provide separate interfaces for Interlude, Preparation, running a show, managing the circus, and managing money. Interlude and Preparation share the relevant management flows. Show Time has the approved dedicated flow and current-act layout described below; detailed styling remains undecided.
- Follow the full circus rules in `Circus rules.pdf` faithfully. The “Simplified Circus Rules” variant on printed page 67 is excluded entirely, including partial use of its substitutions. This applies to all development stages; an incomplete milestone does not authorize simplified mechanics. Explained Interlude adjustments to next-show Anticipation and circus Prestige are a confirmed app extension. Other GM override fields remain a later decision; they are not implied by this feature.
- Players make rolls outside the app. The GM enters the roll with any GM-decided situational adjustment included. The app applies applicable bonuses from tracked sources such as show events and inventory, then calculates the result and its consequences.
- Use a simple 2D presentation with animations, drag-and-drop elements, and interfaces that calculate values from entered game data. Detailed UI design is deferred.

## Interlude Stage

Interlude is the between-show stage for campaign activity, such as adventuring and character progression. It has its own interface and is distinct from the structured preparation and running of a particular show. Its duration is not defined as the six-day preparation period; the exact transition into show preparation remains to be designed.

During Interlude the GM can:

- Hire NPC performers, retaining the existing recruitment and trait-access rules.
- Create signature tricks through the guided creation flow and record PC level changes. Existing progression and redesign eligibility still apply; entering Interlude does not itself authorize unrestricted redesign.
- Buy permanent circus upgrades through the purchase workflow. Temporary upgrades are excluded from Interlude and belong to show preparation.
- Record campaign events that change the next show's Anticipation or the circus's Prestige, with the amount and an explanation of what happened and why the value changed.
- Record money contributed from PCs' personal funds into the circus budget, distinct from show Payout.

An explained adjustment is a source of the resulting value, not a replacement of the total. The GM supplies the mechanical change explicitly; descriptive text alone does not calculate an effect. Prestige adjustments must appear with their reasons in the existing Prestige explanation popup. Anticipation adjustments must retain their reasons and next-show scope for use in preparation. These entries provide explanations for affected values without requiring a general action-history screen.

Committing an Interlude change applies it immediately, and it must remain reversible under the agreed finished-history boundary. Saving/loading or revisiting Interlude must not apply the same adjustment or contribution again. Future changes must not rewrite finished-show snapshots or payouts.

**Anticipation lifecycle decision:** Interlude Anticipation follows the normal rules in the PDF (printed p. 60): the applicable maximum caps generation, excess is ignored, and Anticipation resets after a show or six days after its first generation if no show occurs. These entries belong to that same next-show Anticipation pool and expiry window; they are not indefinitely reserved bonuses or separate timers that restart the window. Record the campaign timing and the effective contribution needed to explain caps and expiry.

**Still to decide:** When an adjustment becomes attached to a concrete show record, and how the interface handles cancellation/postponement within those normal expiry rules. Do not silently turn a next-show adjustment into a bonus for every future show. Preparation retains all Interlude operations, as confirmed below. Show Time management restrictions are confirmed below. Exact Interlude-to-Preparation controls and cancellation/back-navigation behavior remain open. Recording contributions does not yet specify full PC-wallet tracking.

## Preparation Stage

Preparation retains every Interlude capability and adds promotion and temporary-upgrade purchases. The GM can continue recruiting NPCs, creating tricks, recording PC level changes, buying permanent upgrades, recording explained Anticipation/Prestige changes, and adding personal-fund contributions while preparing the show. These are shared management workflows, not separate copies of the troupe, budget, or adjustment records.

| Operation | Interlude | Preparation |
| --- | --- | --- |
| Hire NPC performers | Available | Available |
| Create tricks through the guided flow | Available | Available |
| Record PC level changes | Available | Available |
| Buy permanent upgrades | Available | Available |
| Record explained Anticipation or Prestige adjustments | Available | Available |
| Add personal funds to the circus budget | Available | Available |
| Promote the Circus | Unavailable | Available |
| Buy temporary upgrades | Unavailable | Available |

Availability in Preparation does not waive the applicable rules: promotion takes downtime and uses the normal checks/Aid limits; purchases use their prices, prerequisites, and per-show restrictions; tricks use their access, progression, and redesign rules. The existing advertising-before-promotion requirement also remains. Preparation must account for management changes when deriving the upcoming show's state, without duplicating committed costs or effects.

Explained Anticipation changes follow the same normal capacity/expiry rules in both stages. Changing stages alone must not reset the Anticipation window or apply existing contributions again. Committed changes take effect immediately and remain reversible under the finished-history boundary.

Preparation ends before Show Time setup: temporary purchases are completed here, and backstage assignments and random events follow in Show Time. Calendar handling of overlapping downtime activities and detailed transition/back-navigation controls still need discussion.

## Show Time Stage — Approved

Show Time is a dedicated interface following the full circus rules and the Circus Show Sheet on printed page 68 (PDF page 10). The sequence follows printed page 61 (PDF page 3), with the already agreed purchase workflow in Preparation:

**Preparation purchases → Show Time setup → Opener → Build-up → Big Number → Finale → Results → Finish Show.**

Show Time begins with backstage assignments and random events. Recruitment, character level changes, trick creation/editing, and purchases are unavailable through the management interface while the show runs; their controls are hidden. Interlude/Preparation management workflows are not carried into Show Time. Corrections to the active show remain available before finalization.

### Setup

Review the upgrades already purchased in Preparation without charging for or applying them again. Assign eligible PCs to backstage roles, then enter the externally rolled random event and any additional rolls or choices it requires. Apply prerequisites, role exclusions, event exceptions, and performer-availability rules. Resolve required recovery checks before allowing affected performers to participate; their exact ordering relative to other setup steps still depends on the relevant rule decisions. Establish the starting values after the applicable setup effects.

### Current-act layout

Show the current act prominently with a compact overview of all four acts. The acts have 1, 2, 1, and 3 trick slots respectively. Choose eligible performers and their own tricks when each act begins, enforcing reuse restrictions and exceptions. Explain why an unavailable performer cannot participate. During Build-up and Finale, keep all performers in that act accessible so assistance and clown actions can target the appropriate performer.

| Interface area | Required content and behavior |
| --- | --- |
| Show information | Circus name, settlement, and campaign date. |
| Persistent values | Current Excitement, Anticipation, maximum Anticipation, and Prestige with its explanation popup. Preserve starting values separately from changing totals. |
| Setup context | Purchased upgrades, backstage assignments, random events, their effects, and performer availability. |
| Performer controls | Performer/trick names, level, traits, DC, available checks, actions remaining, repeat penalty, and applicable effects. |
| Performance resolution | Choose a check, handle assistance and resource choices at the applicable rule timing, enter the external roll, and commit. Apply and display the result and Excitement/Anticipation changes immediately. Prompt for injury checks and other required decisions when triggered. |
| Other show actions | Costar, Send in the Clowns, skipping remaining actions, and applicable backstage choices, with eligibility and timing enforced. Costar remains a reaction. |
| Active-act results | Compact action/result rows for each performer, including generated or lost Excitement/Anticipation, with correction controls. These are part of running the active show, not a separate action-history screen. |
| Progression | Advance through the acts as their actions and required choices are resolved. The overview shows progress without requiring a full seven-slot sheet as the primary layout. |
| Results | Final Excitement/Anticipation, show outcome, payout explanation, and earned Prestige, available for review and correction before finalization. |

### Finalization and remaining rule decisions

An explicit **Finish Show** action on Results finalizes the show and creates its read-only historical record. Before that action, corrections remain possible. Finalization records the payout and Prestige award exactly once, using pre-award Prestige for payout; reviewing or reopening results must not duplicate awards. After finalization, the interface cannot edit, delete, or reopen the show for modification. Later management changes must preserve its historical values.

The sheet's three action rows do not resolve the Time trait's fourth-attempt action budget. That issue and NPC eligibility for Send in the Clowns remain open rulings. Approval of this interface also does not settle the unresolved normal-modifier/natural-die roll-entry contract, optional-resource timing, reaction budgets, or detailed undo dependency handling. Refer to [Rules Review](rules-review.md) and the corresponding TODO items before automating those paths.

## Committed Changes and History

All game changes take effect immediately when the user commits them. Committed changes must be reversible, with one exception: a finished show in show history cannot be changed through the interface. This is required behavior for future workflows, not a claim that undo is already implemented.

Finishing a show establishes the historical boundary. The interface must not edit, delete, or reopen a finished show for modification, and later edits to current actors, tricks, traits, or upgrades must not rewrite its recorded values. Corrections to an active show must be possible before finalization. The approved finalization interaction is the explicit Finish Show action on Results. How undo handles dependencies that cross this boundary remains to be specified and must preserve finished history.

A visible action-history screen or chronological action log is unnecessary. Keep the data needed for reversible changes, active-show resume, calculations, and finished-show records; this does not require exposing an action log. The depth and persistence of undo information remain design decisions.

Immediate application at commitment defines game-state behavior. Save timing, autosave, and crash-recovery guarantees still need a separate persistence decision. Multi-screen editors must define their commitment point so unfinished draft input is distinguishable from committed game changes.

## Player Characters and NPC Performers

Use "player" for a person at the table, "PC" for their character, and "NPC" for a non-player character. Players can use NPC performers to fill show slots; who handles a roll does not change the performer's type.

Confirmed requirements:

- NPC performers have a compact set of available checks (for example, one or two) and one assigned trick. Their records must support the trick's requirements.
- PCs can perform their own signature tricks or take backstage roles with separate mechanics.
- PCs need a signature-trick creation and editing interface, following the rules for available checks, traits, progression, and redesign. Trick creation uses several guided screens with detailed instructions.
- Trick traits now have a typed catalog and draft-validation helpers. See [Trick Traits](trick-traits.md) for the full PDF list, PC progression limits, NPC unlocks, and compulsory tags. The creation interface and runtime effects remain deferred.
- The GM must be able to create custom trait definitions in the app. The extensible catalog API now supports selectable custom traits with stable IDs, descriptions, and prerequisites. These additions remain distinct from the built-in PDF rules and use normal PC trait limits. Defining a trait and unlocking it for PCs are separate operations.
- PC skills can improve through campaign progression outside circus management. Interlude and Preparation provide access to level changes and the relevant character-management flows. Circus calculations must use updated values; detailed skill-editing fields remain to be decided.
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

## Confirmed Interface Behavior and Deferred Details

Prestige uses a popup with notes and an explanation of every contribution, as described in [Circus Structures](circus-structures.md). Complex rule concepts use dedicated interfaces with contextual explanations and instructions. Trick creation specifically uses several guided screens. The design does not require a calculation popup for every field.

These explanations belong in the relevant feature's workflow when it is implemented. Later usability work refines them; it does not defer the required guidance until the final milestone. Show history is required and read-only for finished shows. A visible action-history feature is not required.

The following are presentation ideas or details to refine during UI work; their layouts are not yet decided.

| Idea | Intended benefit |
| --- | --- |
| Action previews | Show the difficulty, repeat penalty, and possible consequences before committing an action. |
| Touch-friendly controls | Support dragging and a tap-card/tap-slot alternative on tablets. |
| Brief feedback animations | Use moving counters, spotlights, card reactions, and applause to make changes easier to follow. |
| Save timing and autosave | Decide when committed state is persisted so progress survives between tabletop sessions; persistence behavior remains to be specified. |

The Show Time current-act layout, compact four-act overview, 1/2/1/3 slots, and Results payout explanation are approved above. Remaining presentation ideas include performer-card styling, an optional provisional lineup before an act begins, and the six-day preparation schedule layout. These details do not postpone the confirmed requirements for guided workflows and show history.

## Rules and Scope Notes

- The detailed outcome rules on printed page 67 make equal Excitement and Anticipation a critical success; higher Excitement is a success, and lower Excitement is a failure.
- The PDF references external Pathfinder rules, including level-based DCs and Aid, and NPC trick descriptions that are not included in the file. Identify these dependencies before implementing full calculation support.
- The previously suggested one-show prototype is a proposal awaiting scope agreement.

## Open Mechanics Questions

- Where is the performer's normal check modifier applied, and how is the unadjusted die result retained alongside any GM adjustment?
- Beyond the confirmed level-change workflow in Interlude and Preparation, which PC values and skill-editing fields should the tool maintain?
- What additional performer and trick fields are needed beyond the PC/NPC distinction above?
- How should money changes be recorded, including purchases, show payouts, and contributions from adventuring funds?
- What information must finished shows preserve, and how should reversible current-state changes handle dependencies while leaving those finished records unchanged?
- Beyond the confirmed explained adjustments to Anticipation and Prestige in Interlude and Preparation, which GM override fields, if any, belong in a later version?
