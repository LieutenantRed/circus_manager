# Rules Review

Reviewed against `Circus rules.pdf`, printed pages 59-69 (PDF pages 1-11). This review distinguishes implemented behavior, documentation requirements, and unresolved source wording.

## Current Model

The implemented prestige calculation matches pages 67 and 69: start at 1, add 1/2/4 per failed/successful/critically successful show, and add 1 for Spotlights. Watermarked Tickets are correctly excluded from permanent prestige. The permanent-upgrade enum includes all eleven entries. PC/NPC profiles correctly separate character progression from fixed NPC trick levels.

The model now has a typed trait catalog and a signature-trick draft validator covering check references, progression limits, access, and trait prerequisites. See [Trick Traits](trick-traits.md). Full rules validation is still pending: direct struct edits bypass validation, NPC DCs can be missing, purchase prerequisites are not checked, and redesign timing is not enforced. These are implementation gaps, not supported exceptions to the rules.

The GM can also define custom selectable traits through the catalog API. This is an explicitly requested campaign extension; the PDF definitions remain immutable defaults. Custom traits follow the same slot/access validation and can declare prerequisites. Their descriptions do not automatically execute new effects.

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
| Preparation | Advertising tier, promotion attempts and Aid, downtime dates, and starting show values | 60-61 |
| Resource and money records | Purchase funding, spell slots/alchemical items, transactions, and historical payout inputs | 64-65, 67, 69 |
| Temporary upgrades | Per-show purchases and merchandise carryover to the following show | 69; deliberately outside current implementation scope |

## Source Wording to Handle Explicitly

- **Exact equality wins:** page 67 explicitly makes equal Excitement and Anticipation a critical success. Its later failure paragraph loosely says failing to exceed Anticipation is failure. Use the explicit three-way outcome rule, already documented in this project.
- **Actions and reactions:** page 62 broadly lists Costar and Send in the Clowns for each performer. Page 65 introduces these options for PCs, identifies Costar as a reaction, and explicitly prohibits NPCs from Costarring. Costar must not be treated as an ordinary one-action option. NPC eligibility for Send in the Clowns needs a recorded ruling before implementation.
- **Time trait:** page 65 allows a fourth trick attempt, while page 62 gives performers three actions. How the additional attempt fits the action budget needs a ruling; do not silently implement an extra general-purpose action.
- **Check difficulty:** page 60 loosely connects rising Anticipation to harder trick checks; the detailed rules on pages 62-63 use listed NPC DCs and level-based PC DCs. Do not automatically add Anticipation to a check DC. Explicit effects such as Stars Align can change DCs.

The PDF references external level-based DCs, Aid, and a trait-granting feat. These references and core roll-resolution rules must be supplied before full automation. The current signature-trick validator applies base progression only, without the external feat's additional allowances. This review does not invent their contents or treat every unresolved detail as permission to change the rules.

## Roll Entry Constraint

The GM's agreed workflow includes their situational adjustment in the entered roll. Such an adjusted number alone does not preserve the natural die or the type of that adjustment. Before automated check resolution, define how to retain that information where required and avoid double counting or incorrect bonus stacking. This remains an open data requirement, not a change to the agreed workflow.
