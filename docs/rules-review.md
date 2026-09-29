# Rules Review

Reviewed against `Circus rules.pdf`, printed pages 59-69 (PDF pages 1-11). This review distinguishes implemented behavior, documentation requirements, and unresolved source wording.

## Current Model

The implemented prestige calculation matches pages 67 and 69: start at 1, add 1/2/4 per failed/successful/critically successful show, and add 1 for Spotlights. Watermarked Tickets are correctly excluded from permanent prestige. The permanent-upgrade enum includes all eleven entries. PC/NPC profiles correctly separate character progression from fixed NPC trick levels.

The model now has a typed trait catalog and a signature-trick draft validator covering check references, progression limits, access, and trait prerequisites. See [Trick Traits](trick-traits.md). Full rules validation is still pending: direct struct edits bypass validation, NPC DCs can be missing, purchase prerequisites are not checked, and redesign timing is not enforced. These are implementation gaps, not supported exceptions to the rules.

The GM can also define custom selectable traits through the catalog API. This is an explicitly requested campaign extension; the PDF definitions remain immutable defaults. Custom traits follow the same slot/access validation and can declare prerequisites. Their descriptions do not automatically execute new effects.

## Confirmed App Extension: Interlude

The user has requested a dedicated Interlude interface for between-show campaign activity: NPC recruitment, trick creation, PC level changes, permanent upgrades, explained next-show Anticipation or circus Prestige adjustments, and contributions from personal funds into the circus budget. Preparation retains all of these Interlude capabilities, including permanent-upgrade purchases, and adds promotion and temporary-upgrade purchases. Promotion and temporary purchases are excluded from Interlude. This is the confirmed app-stage organization; normal rule eligibility and timing still apply.

The ability to record an external campaign event and its numerical consequence with a reason is confirmed app scope; it does not assert a new automatic reward formula in the PDF. Prestige must retain these entries as distinct sources in its explanation. Existing game-rule checks still apply to recruitment, progression/redesign, and purchases.

The user confirmed that Interlude Anticipation follows the PDF's normal expiry/capacity rules (printed p. 60): ignore excess over the applicable maximum, and reset Anticipation after a show or six days after its first generation if no show occurs. Interlude entries use the shared next-show Anticipation window, not indefinite reservation or an independent timer. Preserve the distinction between next-show effects and circus-wide Prestige, and do not reinterpret a one-show adjustment as a recurring bonus. Current-state changes remain reversible, and completed shows remain read-only through the interface. See [Design Notes — Interlude Stage](design-notes.md#interlude-stage).

## Approved Show Time Mapping

The app follows the Circus Show Sheet on printed p. 68 (PDF p. 10) and the ordered procedure on printed p. 61 (PDF p. 3). Temporary purchases finish in Preparation; Show Time begins with backstage assignments, then random events and their required choices, and establishes the starting values before the acts. Required availability/recovery checks must be resolved before an affected performer participates; their finer timing remains subject to rule clarification.

The approved interface shows the current act prominently with a compact four-act overview, 1/2/1/3 slots, performer controls, external roll entry, immediate results, and compact active-act correction rows. Costar, clowns, and backstage choices use their rule eligibility and timing. Management controls are hidden while the show runs. Results remain correctable until the explicit Finish Show action creates the read-only historical record and settles awards once.

These are approved UI/workflow decisions, not rulings that resolve the Time action budget, NPC clown eligibility, or the remaining roll-entry and reaction/resource questions. See [Design Notes — Show Time Stage](design-notes.md#show-time-stage--approved).

## Missing Records for Later Work

These concepts are required for broader rules support but do not yet have dedicated C++ structures:

| Concept | Needed information | PDF pages |
| --- | --- | --- |
| Live show and act participation | Four acts with 1/2/1/3 tricks, actor assignments, actions, reactions, repeated-check penalties, Anticipation/Excitement/capacity, source values for history | 60-65, 68 |
| Individual check result | Entered value, original die where needed, applicable modifiers, DC, and four degrees of success; distinct from `ShowOutcome` | 63-65; external core rules |
| Backstage role assignment | Role, PC, show, prerequisites, effects, and role availability | 66 |
| Upgrade definition | Catalog price, minimum Prestige, prerequisites, and typed effects; distinct from `OwnedUpgrade` | 69 |
| Runtime modifier/event effects | Trait metadata exists; executable effects still need source, target, bonus or penalty type, duration, exceptions, and choices. Some change DCs, capacity, payouts, or actions rather than rolls | 63-66, 69 |
| Performer availability | Injury and recovery across shows, and show-specific exclusions | 64-66 |
| Preparation | Advertising tier, promotion attempts and Aid, downtime dates, and starting show values; retains all Interlude management operations using shared records | 60-61; shared-stage availability is confirmed app workflow |
| Resource and money records | Purchase funding, spell slots/alchemical items, transactions, and historical payout inputs | 64-65, 67, 69 |
| Temporary upgrades | Per-show purchases in show preparation, excluded from Interlude; merchandise carryover to the following show | 69; implementation pending |
| Shared Interlude/Preparation adjustments and contributions | Stable sources, numeric changes, reasons, next-show/circus scope, personal-fund deposits, and reversible application without duplicate effects | Confirmed app workflow; normal Anticipation expiry/capacity confirmed; show binding still to decide |

## Source Wording to Handle Explicitly

- **Exact equality wins:** page 67 explicitly makes equal Excitement and Anticipation a critical success. Its later failure paragraph loosely says failing to exceed Anticipation is failure. Use the explicit three-way outcome rule, already documented in this project.
- **Actions and reactions:** page 62 broadly lists Costar and Send in the Clowns for each performer. Page 65 introduces these options for PCs, identifies Costar as a reaction, and explicitly prohibits NPCs from Costarring. Costar must not be treated as an ordinary one-action option. NPC eligibility for Send in the Clowns needs a recorded ruling before implementation.
- **Time trait:** page 65 allows a fourth trick attempt, while page 62 gives performers three actions. How the additional attempt fits the action budget needs a ruling; do not silently implement an extra general-purpose action.
- **Check difficulty:** page 60 loosely connects rising Anticipation to harder trick checks; the detailed rules on pages 62-63 use listed NPC DCs and level-based PC DCs. Do not automatically add Anticipation to a check DC. Explicit effects such as Stars Align can change DCs.

The PDF references external level-based DCs, Aid, and a trait-granting feat. These references and core roll-resolution rules must be supplied before full automation. The current signature-trick validator applies base progression only, without the external feat's additional allowances. This review does not invent their contents or treat every unresolved detail as permission to change the rules.

## Roll Entry Constraint

The GM's agreed workflow includes their situational adjustment in the entered roll. Such an adjusted number alone does not preserve the natural die or the type of that adjustment. Before automated check resolution, define how to retain that information where required and avoid double counting or incorrect bonus stacking. This remains an open data requirement, not a change to the agreed workflow.
