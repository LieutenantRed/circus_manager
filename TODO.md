

# Documentation review TODO

Review date: 2026-09-29.

## Scope and assessment

Reviewed only [AGENTS.md](AGENTS.md) and every file listed in [docs/](docs/):
[Design Notes](docs/design-notes.md), [Development Plan](docs/development-plan.md),
[Circus Structures](docs/circus-structures.md), [Trick Traits](docs/trick-traits.md),
and [Rules Review](docs/rules-review.md).
No source code, README, rules PDF, build configuration, or external references were inspected.
Statements about existing implementation and validation below are documentation claims, not independently verified findings.

**The documents give a coherent high-level picture, but not a complete specification of the intended app.**
They establish the GM workflow, platforms, PC/NPC distinction, custom traits, source-derived Prestige,
and the preparation → show → settlement cycle. Many rules, record contracts, and interaction decisions
remain deferred. This is a review backlog for later decisions, not authorization to invent rules or implement features.

Items marked **Clarify** concern wording that could mislead a reader; **Specify** identifies missing detail;
**Resolve** identifies an explicitly open decision. Proposed data fields below identify information to account
for, not a mandated class design. Complete an item by documenting the adopted behavior and a concrete example
or acceptance case in the relevant source document.

## PDF answer pass — 2026-09-29

The scope assessment above describes the original documentation-only review. This follow-up
reads [Circus rules.pdf](<Circus rules.pdf>) and answers each of the 30 original items below,
in their original order. Every original statement and checkbox is retained.

**[NOT STATED IN PDF]** marks the end of each unanswered response or unresolved-part statement.
A partial answer does not resolve the entire TODO. No quotation is invented for an absent answer.
Blockquotes reproduce the PDF's wording; line wrapping and table-column spacing are normalized.
Page references give both the printed page and the 1-based PDF page (printed 59–69 = PDF 1–11).
Table headings or surrounding prose identify the columns in quoted table transcriptions.
The upgrade-table indentation was also checked on the rendered page.

These are source findings, not new app decisions or completed implementation tasks. All checkboxes
remain open for review, and source ambiguities are explicitly distinguished from direct answers.

## Scope, authority, and delivery

- [ ] **Clarify — Separate agreed scope from proposals and mandatory behavior from optional presentation.**
  Design Notes calls the one-show prototype unapproved and lists autosave, explanations, touch alternatives,
  and action history as ideas; the Development Plan requires several related behaviors in milestones 2–8
  while calling later milestones proposed. State the intended first usable release, what is committed,
  and which choices remain optional. Distinguish required persistence/resume and calculation records from
  optional autosave policy and visible action-log UI. Reconcile the milestone 9 revisit of number explanations
  with earlier requirements for explainable preparation, calculations, and payouts.
  Sources: [Design Notes — Interface Ideas / Rules and Scope Notes](docs/design-notes.md),
  [Development Plan — Direction / milestones 2–9](docs/development-plan.md).

  **PDF answer (partial):** The source offers both full circus management and an optional simplified mode. Simplified mode ignores Anticipation/Excitement, uses Performance or GM-approved skill checks, ignores Payout, and retains Prestige (p. 67). That is a rules alternative, not approval of a software prototype.

  > Ignore the Anticipation and Excitement rules; instead, use a simple Performance check for each act.
  >
  > — Printed p. 67 (PDF p. 9).
  > Ignore the rules for Payout but tally Prestige as normal, since the party’s Prestige may still affect other aspects of the campaign.
  >
  > — Printed p. 67 (PDF p. 9).

  **Unresolved:** The app's release scope, milestone commitments, autosave, explanations, touch alternatives, and action-log presentation are not specified by this tabletop rules excerpt. Whether to support its simplified mode is also an app decision. [NOT STATED IN PDF]

  **User decision — 2026-09-29 (partial resolution):** Exclude simplified mode completely, including partial use. The app uses only the full circus rules. Recorded in [Design Notes — Confirmed Direction](docs/design-notes.md) and [Development Plan — Direction and Current State](docs/development-plan.md). The PDF answer and unresolved paragraph above are preserved as the original review record; simplified-mode support is now decided.

  **Discussion note:** This item concerns product scope and requirement status, including delivery stages. It does not establish an architectural inconsistency. Whether features are mandatory or optional can affect later implementation choices.

  **User clarification — 2026-09-29:** All committed game changes apply immediately and must be reversible. Finished shows are the exception: show history cannot be changed through the interface. Prestige gets a popup with notes and calculation explanations; complex rule concepts get dedicated guided interfaces, with several detailed instruction screens for trick creation. Show history is a core feature; visible action history is unnecessary.

  **Applied documentation changes:** [Design Notes](docs/design-notes.md) records the commitment/history and interface baseline; [Development Plan](docs/development-plan.md) includes guided creation with milestone 3, reversible active-show changes with milestone 7, read-only history with milestone 8, and refinement of existing guidance with milestone 9. [Circus Structures](docs/circus-structures.md) records the required mutation/history boundary as future behavior, not existing enforcement.

  **Discussion status:** Baseline recorded; continue the review with the next item. Detailed first-release scope/milestone commitments, save timing/autosave, touch-layout details, undo depth/persistence, and finalization/dependency handling remain deferred. Immediate application does not alone decide disk-save timing. The original statement and PDF findings are retained above; user decisions supersede the affected open questions.

  **Interlude decision — 2026-09-29:** A dedicated Interlude stage/interface is confirmed for NPC recruitment, guided trick creation, PC level changes, permanent upgrades, explained Anticipation/Prestige adjustments, and contributions to the circus budget. Temporary upgrades are excluded. These explained adjustments are now authorized scope; other overrides are still undecided. Anticipation follows normal PDF expiry and capacity rules, as explicitly confirmed by the user; it is not reserved indefinitely for a future show. See [Design Notes — Interlude Stage](docs/design-notes.md#interlude-stage) and [Circus Structures — Interlude Records to Add](docs/circus-structures.md#interlude-records-to-add). Original review questions and PDF findings remain above for context.

  **Show Time approval — 2026-09-29:** The full Show Time recommendation is approved: a dedicated interface from setup through four acts and Results, current-act layout with compact overview, hidden management controls, active-show corrections, and explicit Finish Show finalization. This resolves those layout/workflow choices; it does not settle all earlier release/save/undo questions. See [Design Notes — Show Time Stage](docs/design-notes.md#show-time-stage--approved). Original review statements and PDF findings remain above for reference.

- [ ] **Clarify — State Android validation status and milestone completion consistently.**
  Milestone 1 requires a usable menu on both platforms; its status reports Windows validation and a prepared
  Android APK, with physical-tablet testing deferred. Explicitly distinguish packaged, launch-tested,
  device-tested, and accepted status, including any agreed waiver and later acceptance gate.
  Do not treat an APK export as evidence of tablet behavior.
  Sources: [Development Plan — milestone 1 / Working Sequence](docs/development-plan.md),
  [AGENTS.md — Testing Guidelines](AGENTS.md).

  **PDF answer:** No direct answer. The PDF contains tabletop rules, not Android/Windows build or test results, waivers, or software milestone acceptance evidence. [NOT STATED IN PDF]

- [ ] **Specify — Establish rules authority, edition, and dependency coverage.**
  Record the intended Pathfinder rules edition/version, the authoritative circus reference, and how
  later rulings supersede ambiguous wording. Inventory externally required DC tables, Aid, degree-of-success
  rules, Advanced Circus Trick, and NPC trick definitions; identify which are bundled, entered by the GM,
  deferred, or unsupported. These are acknowledged dependencies, but their actual contents and support
  boundaries are absent. The permitted documents alone cannot verify PDF fidelity.
  Sources: [Rules Review — Source Wording](docs/rules-review.md),
  [Design Notes — Rules and Scope Notes](docs/design-notes.md).

  **PDF answer (partial):** The article is “Life in the Circus,” in an excerpt headed “The Show Must Go On,” for the Extinction Curse Adventure Path (pp. 59–69). It explicitly permits use in other campaigns. Dependencies are the Core Rulebook's level-based DC table (Table 10–5, p. 503), multiple attack penalty discussion (p. 446), Aid (p. 470), Advanced Circus Trick in the Extinction Curse Player's Guide, and NPC tricks on the adventure volumes' inside covers. Simplified mode additionally references DC adjustments in Table 10–6, p. 504 (excerpt p. 67). These referenced materials are not reproduced here.

  > While intended for use throughout the Extinction Curse Adventure Path, the rules are flexible enough to be used in any campaign.
  >
  > — Printed p. 59 (PDF p. 1).
  > The DC for the trick check is determined by your level, as shown on Table 10–5 on page 503 of the Core Rulebook.
  >
  > — Printed p. 63 (PDF p. 5).
  > This reaction otherwise acts as the Aid action described on page 470 of the Core Rulebook.
  >
  > — Printed p. 65 (PDF p. 7).
  > A PC can add additional trick traits to their signature trick by taking the Advanced Circus Trick general feat. See the Extinction Curse Player’s Guide for more details.
  >
  > — Printed p. 64 (PDF p. 6).
  > NPC tricks appear on the inside covers of each volume of the Extinction Curse Adventure Path.
  >
  > — Printed p. 63 (PDF p. 5).

  **Unresolved:** No explicit edition/version identifier or errata precedence is given in this excerpt. Core natural-die/degree-resolution rules, the full referenced tables/feat/NPC entries, and the app's bundled/manual/unsupported coverage are not supplied. [NOT STATED IN PDF]

- [ ] **Resolve — Make milestone dependencies executable.**
  Milestone 3 promises redesign timing once downtime/level-up records exist, but does not schedule those
  records; preparation time arrives in milestone 6. Identify when each prerequisite is delivered and
  the allowed interim workflow. Specify what milestones 2–4 can load or edit when earlier saves contain
  minimal completed shows and later live-show records do not yet exist.
  Source: [Development Plan — milestones 2–6](docs/development-plan.md).

  **PDF answer (partial):** The rules establish a redesign prerequisite: a level gain or six consecutive downtime days.

  > A PC can change their signature trick (including its trick checks and trick traits) whenever they gain a level or by spending 6 consecutive downtime days redesigning the trick.
  >
  > — Printed p. 63 (PDF p. 5).

  **Unresolved:** Delivery order, interim editing permissions, and migration of early saves or minimal show records are software decisions absent from the PDF. [NOT STATED IN PDF]

## Rules required for calculation

- [ ] **Resolve — Finalize the roll-entry contract.**
  Specify whether the entered number includes the normal character modifier; preserve natural die
  information where required; distinguish GM adjustments from tracked modifiers and retain enough bonus
  typing to enforce stacking. Define missing-input handling and examples that demonstrate no double counting.
  The current requirement to include the GM adjustment in the entered value must remain explicit.
  Sources: [Design Notes — Roll Resolution](docs/design-notes.md),
  [Rules Review — Roll Entry Constraint](docs/rules-review.md).

  **PDF answer (partial):** The worked example resolves a total that already includes the character modifier; NPC rolls use the modifier and DC in their trick description. These explain tabletop calculation inputs, not what an app input box should accept.

  > Including his check modifier, his result is 26, which handily overcomes the DC of 19 for 4th‑level characters and generates 4 Excitement.
  >
  > — Printed p. 65 (PDF p. 7).
  > When an NPC performs their trick, either a player or the GM can roll the trick checks for the NPC, using the DC and the modifiers listed in the trick description.
  >
  > — Printed p. 62 (PDF p. 4).

  **Unresolved:** The PDF does not define app roll entry, recording the natural die, representing GM adjustments, missing-input errors, or preventing double counting. It does not supply the general typed-bonus stacking rules. [NOT STATED IN PDF]

- [ ] **Specify — Document the complete individual-check calculation.**
  Supply DC lookup/override rules, four-degree resolution, natural-die behavior, ordinary repeated-attempt
  penalties, what increments/resets the attempt counter, and each result's Anticipation/Excitement effects.
  Define skill/save/attack and flat-check handling. The docs give Agile penalties and whole-show outcomes,
  but not the complete ordinary check algorithm or worked examples.
  Sources: [Trick Traits — Catalog](docs/trick-traits.md),
  [Circus Structures — Actors / Money and Show Outcomes / Supporting Type Reference](docs/circus-structures.md),
  [Development Plan — milestone 5](docs/development-plan.md).

  **PDF answer (partial):** Use the PC's level-based DC (external Table 10–5); for NPCs use the listed DC/modifiers (pp. 62–63). Stars Align lowers trick DCs by 2 (p. 66). For trick level L, a critical success adds L Excitement and ceil(L/2) Anticipation; success adds L Excitement; failure has no effect; critical failure subtracts ceil(L/2) Excitement. Apply these changes to show totals, with Anticipation subject to capacity (p. 60).

  > Critical Success You generate Excitement equal to the trick’s level; this Excitement is added to the circus’s total Excitement for the show. You also generate Anticipation equal to half the trick’s level (rounded up); this Anticipation is added to the circus’s total Anticipation for the show.
  >
  > — Printed p. 63 (PDF p. 5).
  > Success You generate Excitement equal to the trick’s level; this Excitement is added to the circus’s total Excitement for the show.
  >
  > — Printed p. 63 (PDF p. 5).
  > Failure No effect.
  >
  > — Printed p. 63 (PDF p. 5).
  > Critical Failure The circus’s Excitement value decreases by a value equal to half the trick’s level (rounded up).
  >
  > — Printed p. 63 (PDF p. 5).

  Count Perform a Trick attempts within the same act, even if the selected check changes: the second and third take −5/−10, or −4/−8 with Agile. Time permits a fourth check at the third check's penalty (p. 65). The wording makes the counter act-local.

  > You can Perform a Trick multiple times per act, and can choose a different possible trick check for each attempt.
  >
  > — Printed p. 63 (PDF p. 5).
  > If you Perform a Trick twice during the same act, you take a –5 penalty to your second trick check. If you Perform a Trick three times, the penalty for the third check is –10.
  >
  > — Printed p. 63 (PDF p. 5).
  > The penalties are reduced to –4 and –8, respectively, if your trick has the agile trait.
  >
  > — Printed p. 63 (PDF p. 5).

  Skill checks, saving throws, and attack rolls are permitted trick checks (p. 62); injury/recovery uses flat checks (pp. 64–65), with DC 15 normally and flooring substitutions of 10/5 (p. 69).

  > A trick consists of one or more trick checks—this is a skill check, saving throw, or attack roll that represents the performer’s feat of grace or strength.
  >
  > — Printed p. 62 (PDF p. 4).

  **Unresolved:** The full DC table, general four-degree thresholds/natural-die rules, generic flat-check resolution rules, and a minimum show Excitement value are not defined here. Page 60 says rising Anticipation makes later checks harder but supplies no formula; do not invent an Anticipation-to-DC adjustment. Exact timing/order of all overlapping effects also remains unspecified. [NOT STATED IN PDF]

- [ ] **Resolve — Record action permissions, budgets, and exceptions.**
  Settle the already identified Time-trait action-budget issue and NPC eligibility for Send in the Clowns.
  Also specify Perform a Trick, Costar, and clown action/reaction costs, timing, helper eligibility,
  number of uses/helpers, and per-act/show performer reuse limits. Give an eligibility/action matrix
  for PCs, NPCs, and backstage PCs; shared processing does not imply equal permissions.
  Sources: [Rules Review — Actions and reactions / Time trait](docs/rules-review.md),
  [Development Plan — milestone 7](docs/development-plan.md).

  **PDF answer (partial):** Each onstage performer has up to three actions per act and must Perform a Trick at least once. Remaining actions may repeat the trick or be skipped. Perform a Trick and Send in the Clowns have one-action headings; Costar has a reaction heading (pp. 63, 65).

  > Just like in combat encounters, each performer in an act can use up to 3 actions. At least 1 action must be used to Perform a Trick (page 63); otherwise, each performer can Costar with another performer, Send in the Clowns, Perform their Trick again, or skip their remaining actions.
  >
  > — Printed p. 62 (PDF p. 4).

  Costar requires a willing performer in the same act who is about to roll; roll the same check against that trick's DC and otherwise use external Aid rules. NPCs cannot Costar. The other-show-actions section restricts its actions to PCs performing in an act.

  > A PC must be performing in an act to do so and must use the indicated number of actions.
  >
  > — Printed p. 65 (PDF p. 7).
  > Trigger Another performer in the same act as you is about to attempt a trick check.
  >
  > — Printed p. 65 (PDF p. 7).
  > Requirements The performer is willing to accept your aid.
  >
  > — Printed p. 65 (PDF p. 7).
  > Attempt the same check as the trick check you are attempting to aid. The DC to Costar is equal to the DC of the trick check. NPCs cannot Costar.
  >
  > — Printed p. 65 (PDF p. 7).

  Clowns change one failed check in the current act to success, or one critical failure to failure; ordinarily once per act. Backup Clown adds one use per act. Clown Coordinator allows a reaction instead of one action, despite being a backstage role (p. 66).

  > Requirements You or another performer has failed or critically failed a trick check during the current act.
  >
  > — Printed p. 65 (PDF p. 7).
  > A failed trick becomes a success instead, or if it was a critical failure, it is instead a failure.
  >
  > — Printed p. 65 (PDF p. 7).
  > The clowns can be sent in only once per act, and only one trick check is affected.
  >
  > — Printed p. 65 (PDF p. 7).

  A trick is used once per show, with repeated checks allowed within its act. Animal Handler explicitly lets a PC with an animal signature trick perform twice in different acts (p. 66). Backstage PCs do not perform tricks; NPCs cannot take backstage roles.

  > each trick can be performed only once per show.
  >
  > — Printed p. 62 (PDF p. 4).
  > a PC whose signature trick has the animal trait can perform twice in the same show (though not in the same act).
  >
  > — Printed p. 66 (PDF p. 8).
  > A performer whose trick has the time trait can perform that trick one additional time per act, taking a penalty to the fourth trick check equal to the penalty to the third trick check.
  >
  > — Printed p. 65 (PDF p. 7).

  **Unresolved:** The text does not explain how Time's fourth attempt fits the three-action budget. Pages 62 and 65 give conflicting breadth for NPC clown eligibility. Reaction refresh limits, maximum Costar helpers, a Clown Coordinator reaction trigger, and whether clown correction reverses an already resolved injury/resource consequence are not explicitly supplied. A definitive permission/budget matrix needs those rulings. [NOT STATED IN PDF]

- [ ] **Specify — Expand trait summaries into operational rules.**
  For each built-in effect, document its trigger, timing, targets, value, duration, choices, and exceptions.
  In particular, clarify Emotion's reduction choices, Magical's resource spending and qualifying results,
  Alchemical consumption timing, Dance stacking, and Injury consequences. Cross-reference the general
  rules for effects already shared by multiple traits. Short descriptions are insufficient to determine
  runtime behavior, and metadata is explicitly not execution.
  Sources: [Trick Traits — Catalog / GM-Created Traits](docs/trick-traits.md),
  [Rules Review — Runtime modifier/event effects](docs/rules-review.md).

  **PDF answer (partial):** Built-in skill-linked traits grant +1 circumstance when that skill performs the trick. The mapping is Aerial–Acrobatics, Air–Survival, Animal–Nature, Audience–Society, Beast–Arcana, Earth–Occultism, Fire–Intimidation (p. 64), Musical–Performance, Plant–Nature, Prop–Crafting, and Water–Athletics (p. 65).

  > If a trick trait’s name is followed by the name of a skill in parentheses, then a performer gains a +1 circumstance bonus to Perform a Trick with that trait using that skill check.
  >
  > — Printed p. 64 (PDF p. 6).

  Alchemical consumes one possessed item as part of the trick for +1 circumstance on that check. Agile changes second/third penalties to −4/−8 (p. 64).

  > As part of the trick, the performer can expend one alchemical item in their possession. Upon doing so, the performer gains a +1 circumstance bonus to their trick check. This destroys the item.
  >
  > — Printed p. 64 (PDF p. 6).

  Dance specifically allows Costar circumstance bonuses to stack; the example gives +6 from two successful master-proficient helpers rather than +3.

  > Circumstance bonuses to trick checks gained from performers using the Costar reaction (page 65) stack.
  >
  > — Printed p. 64 (PDF p. 6).

  Emotion requires Alchemical or Magical. On success or critical success, the performer may independently reduce generated Excitement, Anticipation, or both, as low as zero; this concerns the check's generated amount, not an arbitrary reduction of accumulated show totals.

  > A trick must have either the alchemical or magical trait in order to have the emotion trait.
  >
  > — Printed p. 64 (PDF p. 6).
  > Whenever a performer succeeds or critically succeeds at a trick check with the emotion trait, they can reduce the amount of Excitement or Anticipation (or both) the trick generates however they wish, down to a minimum of 0 Excitement or Anticipation.
  >
  > — Printed p. 64 (PDF p. 6).

  Injury is compulsory if any PC trick-check choice is a saving throw. Any critical failure on an Injury trick risks injury, including when another check type was chosen. Use the injury/recovery answer below.

  > any signature trick that uses a saving throw for one of its trick checks must have the injury trait.
  >
  > — Printed p. 64 (PDF p. 6).
  > If an NPC or PC performing a trick with the injury trait critically fails any trick check, they have a chance of becoming injured.
  >
  > — Printed p. 64 (PDF p. 6).

  Magical spends a spell slot while performing; a success or critical success adds the slot's level in Excitement.

  > While Performing the Trick, the performer can expend one spell slot of any level. If the performance succeeds or critically succeeds, the trick generates an additional amount of Excitement equal to the expended spell slot’s level.
  >
  > — Printed p. 65 (PDF p. 7).

  Team is compulsory when a PC accepts Costar assistance. Compulsory traits use no selection slots. Circus always applies to Perform a Trick. Time grants a fourth attempt using the third penalty.

  > Anytime a PC performing a signature trick accepts the Costar reaction from a performer, the trick has this trait.
  >
  > — Printed p. 65 (PDF p. 7).
  > These compulsory trick traits do not count toward a signature trick’s maximum number of traits.
  >
  > — Printed p. 64 (PDF p. 6).
  > This action always has the circus trait.
  >
  > — Printed p. 63 (PDF p. 5).
  > A performer whose trick has the time trait can perform that trick one additional time per act, taking a penalty to the fourth trick check equal to the penalty to the third trick check.
  >
  > — Printed p. 65 (PDF p. 7).

  **Unresolved:** The source does not explicitly say whether optional item/slot spending is chosen before or after seeing the roll, how to order Emotion with doubling/additional Excitement, or how Time obtains its extra attempt within the action budget. Arbitrary custom-trait execution is not defined. [NOT STATED IN PDF]

- [ ] **Specify — Define modifier identity, stacking, and calculation order.**
  Document source/target identifiers, affected quantity, bonus or penalty type, applicability, duration,
  precedence, caps/floors, and consumption/expiry. Distinguish check modifiers, DC changes, and changes to
  actions, capacity, Anticipation, Excitement, or payout. Include overlapping effects and exception cases
  so a source cannot be applied twice and each displayed result has an explanation.
  Sources: [Rules Review — Missing Records](docs/rules-review.md),
  [Development Plan — milestone 5](docs/development-plan.md).

  **PDF answer (partial):** Many individual effects are typed and scoped: trait skill bonuses and Costar assistance are circumstance bonuses; Dance is an explicit Costar stacking exception (p. 64). Food Poisoning provides −1 generally and −2 for two selected traits; Stars Align changes DCs, not rolls; Carnival Barker changes maximum Anticipation after successful checks (p. 66). Temporary upgrades normally affect one show; permanent upgrades affect subsequent shows (p. 69).

  > Food Poisoning: Trick checks take a –1 circumstance penalty. The GM randomly selects two trick traits; trick checks with those traits take a –2 circumstance penalty.
  >
  > — Printed p. 66 (PDF p. 8).
  > Stars Align: Trick check DCs decrease by 2.
  >
  > — Printed p. 66 (PDF p. 8).
  > Circumstance bonuses to trick checks gained from performers using the Costar reaction (page 65) stack.
  >
  > — Printed p. 64 (PDF p. 6).
  > Any Anticipation generated in excess of this (either from downtime, random events, or any other source) is ignored.
  >
  > — Printed p. 60 (PDF p. 2).

  Explicit multiplicative exception: critical-success Payout and Bad Weather stack to four times normal Payout. Tier effects use replacement wording, not accumulated seating/tent values (p. 69).

  > This doubling stacks with the increase granted by the bad weather event (see opposite page), in which case the Payout is effectively quadrupled.
  >
  > — Printed p. 67 (PDF p. 9).

  **Unresolved:** General same-type bonus/penalty stacking, global effect ordering, source/target IDs, deduplication, an Excitement floor, and explanation storage are not specified. In particular, ordering the Scalpers minimum with Watermarked Tickets, duplicate random events, and competing capacity changes needs a direct ruling or external rule, not an invented algorithm. [NOT STATED IN PDF]

- [ ] **Specify — Provide the preparation procedure and its catalogs.**
  Document baseline capacity/Anticipation/Excitement, the six-day sequence, advertising tiers/prices/order,
  promotion frequency and eligible participants, Aid handling, and how each outcome changes the starting
  state. Define the random-event table, externally entered results, event choices, duration, and ordering
  exceptions. The roadmap names these mechanics without specifying their values or sequence in enough detail.
  Sources: [Development Plan — milestone 6](docs/development-plan.md),
  [Rules Review — Preparation / Live show records](docs/rules-review.md).

  **PDF answer (partial):** Preparation lasts six days; Anticipation expires after a show or six days after first generation if no show occurs. Starting maximum Anticipation is 20; excess generation is ignored. Advertisements cost no downtime, must precede promotion, and only one tier may be purchased per week, for one show. Promotions take two consecutive days, with only one promoting PC at a time and at most one aiding PC, giving three promotion opportunities per show.

  > It resets to 0 after each show or 6 days after the first Anticipation is generated (in the event the PCs don’t put on a show).
  >
  > — Printed p. 60 (PDF p. 2).
  > The circus’s starting maximum Anticipation is 20.
  >
  > — Printed p. 60 (PDF p. 2).
  > The PCs can purchase only one advertising tier per week.
  >
  > — Printed p. 60 (PDF p. 2).
  > Only one PC can Promote the Circus at a time (unless that PC is being aided by another PC; see below), meaning the party has three chances to Promote the Circus before each circus show.
  >
  > — Printed p. 61 (PDF p. 3).

  Advertisement catalog, exact table entries (columns: Tier, Cost, Anticipation):

  > 1 1 gp 1
  > 2 5 gp 2
  > 3 20 gp 4
  > 4 40 gp 6
  > 5 80 gp 9
  > 6 150 gp 12
  > 7 250 gp 16
  > 8 500 gp 20
  > 9 800 gp 25
  > 10 1,200 gp 30
  > 11 2,000 gp 40
  > 12 3,000 gp 50
  >
  > — Printed p. 61 (PDF p. 3).

  Promotion is an untrained Society activity against the party-level DC from external Table 10–5. For promoter level L and Charisma modifier C: critical success gives max(2, 2×(L+C)) Anticipation; success max(1, L+C); failure 1; critical failure 0. Aid here has a directly specified DC 20 Society check and +2 circumstance on success, so this particular Aid procedure is not wholly absent from the PDF.

  > One other PC can spend 2 downtime days to Aid you, providing a +2 circumstance bonus to your Society check if they succeed at a DC 20 Society check.
  >
  > — Printed p. 61 (PDF p. 3).
  > Critical Success You generate Anticipation equal to twice the sum of your level plus your Charisma modifier (minimum 2).
  > Success You generate Anticipation equal to your level plus your Charisma modifier (minimum 1).
  > Failure You generate 1 Anticipation.
  > Critical Failure You generate no Anticipation.
  >
  > — Printed p. 61 (PDF p. 3).

  Pre-show Excitement carries into the show and can come from upgrades/events (p. 61). The show setup sequence is explicitly:

  > 1. Purchase Temporary Upgrades (page 69): The PCs purchase temporary upgrades (if any) for the show.
  > 2. Choose Non-Performer Roles (page 66): The PCs choose which non-performer roles, if any, they will each take during the show. A PC who selects a non-performer role can’t perform any tricks during the show.
  > 3. Roll for Random Events (page 66): The GM rolls to determine which random event affects the show.
  > 4. Tally Starting Anticipation (page 60): The GM marks the starting Anticipation for the show (Anticipation may change throughout the show).
  > 5. Perform Acts and Tricks (below): The PCs choose which tricks to perform during each act, then follow the rules for performing tricks until all four acts are over.
  > 6. Calculate Payout (page 67): The GM calculates the PCs’ Payout, which depends on the success of the show.
  >
  > — Printed p. 61 (PDF p. 3).

  Roll a d12 at the start of each show. The event definitions below are exact source text; each effect is for that show unless it gives a more specific timing.

  | d12 | Event |
  | --- | --- |
  | 1 | Animals Break Loose |
  | 2 | Bad Weather |
  | 3 | Clown Lung |
  | 4 | Equipment Malfunction |
  | 5 | Food Poisoning |
  | 6 | Hecklers |
  | 7 | Injured Performer |
  | 8 | Overflowing Crowd |
  | 9 | Scalpers |
  | 10 | Stars Align |
  | 11 | Tent Breaks |
  | 12 | Roll again twice; reroll subsequent 12s |

  > Animals Break Loose: Animal tricks can’t be performed during the show, and the crowd’s Excitement and Anticipation each increase by 2d6 (rolled separately).
  >
  > — Printed p. 66 (PDF p. 8).
  > Bad Weather: Trick checks with the aerial or fire trait take a –2 circumstance penalty and trick checks with the earth trait gain a +2 circumstance bonus. If the show is a success, the Payout is doubled.
  >
  > — Printed p. 66 (PDF p. 8).
  > Clown Lung: Performers cannot Send in the Clowns unless a PC takes the backup clown non-performer role.
  >
  > — Printed p. 66 (PDF p. 8).
  > Equipment Malfunction: The NPC with the highest trick level (chosen randomly in the case of a tie) cannot perform in the show.
  >
  > — Printed p. 66 (PDF p. 8).
  > Food Poisoning: Trick checks take a –1 circumstance penalty. The GM randomly selects two trick traits; trick checks with those traits take a –2 circumstance penalty.
  >
  > — Printed p. 66 (PDF p. 8).
  > Hecklers: During each act, one performer (chosen randomly for acts with more than one performer, after the PCs have selected which tricks will be performed) takes a –1 circumstance penalty to trick checks.
  >
  > — Printed p. 66 (PDF p. 8).
  > Injured Performer: One of the PCs (chosen randomly) cannot perform during this show. The PC can still take on a non-performer role.
  >
  > — Printed p. 66 (PDF p. 8).
  > Overflowing Crowd: The crowd’s starting Anticipation increases by 4d6 and the maximum Anticipation limit for the show increases by 20.
  >
  > — Printed p. 66 (PDF p. 8).
  > Scalpers: The PCs’ Prestige (page 67) is treated as 3 less (minimum 1) when calculating Payout.
  >
  > — Printed p. 66 (PDF p. 8).
  > Stars Align: Trick check DCs decrease by 2.
  >
  > — Printed p. 66 (PDF p. 8).
  > Tent Breaks: The circus’s maximum Anticipation for the show decreases by 10.
  >
  > — Printed p. 66 (PDF p. 8).
  > 12 Roll again twice (reroll subsequent 12s)
  >
  > — Printed p. 66 (PDF p. 8).

  Animal Handler rerolls Animals Break Loose; Security Guard negates Hecklers/Scalpers; Beer adds Hecklers (pp. 66, 69). These are explicit exceptions, not an instruction to reroll all negated events.

  **Unresolved:** The PDF does not explicitly state a baseline starting Excitement number or a numeric Prestige-to-starting-Anticipation formula despite the overview mentioning Prestige. Duplicate-event handling, random selection with no eligible targets, the two-trait selection pool, and whether roles may be reassigned after an event are not fully specified. It directs the GM to roll events but does not prescribe software entry/storage for these rolls. [NOT STATED IN PDF]

  **Interlude decision — 2026-09-29:** Interlude is separate from structured show preparation. It can record explained next-show Anticipation changes. Temporary upgrades belong to preparation. The user confirmed normal Anticipation expiry and capacity rules; transfer to a concrete next-show record remains to be designed. See [Design Notes — Interlude Stage](docs/design-notes.md#interlude-stage) and [Circus Structures — Interlude Records to Add](docs/circus-structures.md#interlude-records-to-add). Original review questions and PDF findings remain above for context.

  **Preparation decision — 2026-09-29:** Preparation is all Interlude capabilities plus promotion and temporary-upgrade purchases. It also permits permanent purchases, recruitment, guided trick creation, PC level changes, explained Anticipation/Prestige adjustments, and personal contributions. Normal game-rule timing, validation, and Anticipation expiry/capacity still apply. See [Design Notes — Preparation Stage](docs/design-notes.md#preparation-stage).

  **Show Time approval — 2026-09-29:** Temporary purchases finish in Preparation. Show Time starts with backstage assignments followed by random events and their effects, then establishes starting values before the acts. The roadmap now places these setup operations in milestone 7, not Preparation milestone 6. See [Design Notes — Show Time Stage](docs/design-notes.md#show-time-stage--approved). Original review statements and PDF findings remain above for reference.

- [ ] **Specify — Provide backstage role definitions and assignment constraints.**
  List role names, prerequisites/upgrades, effect formulas, timing, and any required input.
  Clarify whether one PC may hold multiple roles: one PC per role and exclusion from performing do not
  settle that separate question. Define assignment lock time and treatment of an unavailable assigned PC.
  Sources: [Circus Structures — Actors](docs/circus-structures.md),
  [Development Plan — milestone 6](docs/development-plan.md).

  **PDF answer (partial):** Backstage roles are PC-only, exclude performing tricks for that show, lock until the next show, and allow only one PC per particular role. Roles are chosen before rolling the random event (p. 61).

  > Each of the following non-performer roles requires a PC to abstain from performing in the show but grants a bonus to various parts of the performance. NPCs cannot perform these roles; it is assumed that they are fully occupied with preparing for their acts.
  >
  > — Printed p. 66 (PDF p. 8).
  > Once chosen, a non-performer role cannot be changed until the next show. Only one PC can perform a particular non-performer role per show (for example, two PCs can’t both choose the role of animal handler).
  >
  > — Printed p. 66 (PDF p. 8).

  The ten named roles, with their exact effect definitions:

  > Animal Handler: Trick checks with the animal trait gain a +2 circumstance bonus, and a PC whose signature trick has the animal trait can perform twice in the same show (though not in the same act). If the animals break loose event is rolled on Table 3: Random Circus Events (below), reroll on that table instead.
  >
  > — Printed p. 66 (PDF p. 8).
  > Backup Clown: Performers can Send in the Clowns one additional time per act.
  >
  > — Printed p. 66 (PDF p. 8).
  > Bandleader: After each trick is completed, the bandleader can choose to generate Anticipation equal to half the bandleader’s level rounded up. The circus must have the acoustics permanent upgrade (page 69) before a PC can choose the bandleader role.
  >
  > — Printed p. 66 (PDF p. 8).
  > Carnival Barker: The carnival barker draws in more audience members as the show goes on and increases the show’s maximum Anticipation. For every successful trick check performed, the carnival barker can choose to increase the show’s maximum Anticipation by 5.
  >
  > — Printed p. 66 (PDF p. 8).
  > Clown Coordinator: You can Send in the Clowns as a reaction instead of using 1 action.
  >
  > — Printed p. 66 (PDF p. 8).
  > Costumer: Performers get a +1 circumstance bonus to trick checks with the audience trait.
  >
  > — Printed p. 66 (PDF p. 8).
  > Lighting: Performers gain a +1 circumstance bonus to Deception and Thievery trick checks. The circus must have the spotlights permanent upgrade before a PC can choose the lighting role.
  >
  > — Printed p. 66 (PDF p. 8).
  > Medic: Performers can’t become injured from critically failing tricks with the injury trait.
  >
  > — Printed p. 66 (PDF p. 8).
  > Pyrotechnic: Trick checks with the fire trait generate double Excitement.
  >
  > — Printed p. 66 (PDF p. 8).
  > Security Guard: Any rolls of hecklers or scalpers on Table 3: Random Circus Events are negated and have no effect on the performance.
  >
  > — Printed p. 66 (PDF p. 8).

  The GM may create additional roles. The Injured Performer event explicitly permits its chosen PC to take a backstage role (p. 66).

  **Unresolved:** The PDF does not explicitly limit each PC to one role, explain replacement of an unavailable role-holder, or reconcile the event's role permission with the earlier role lock. It does not define Clown Coordinator's reaction trigger, whether “successful” for Carnival Barker includes critical success, or how Pyrotechnic interacts with a negative Excitement result. [NOT STATED IN PDF]

  **Show Time approval — 2026-09-29:** Role assignment belongs to Show Time setup before entering random events. The UI validates prerequisites and performer exclusions and exposes applicable backstage choices during the acts. The earlier rule ambiguities about role multiplicity and event exceptions are not resolved by this UI approval. See [Design Notes — Show Time Stage](docs/design-notes.md#show-time-stage--approved). Original review statements and PDF findings remain above for reference.

- [ ] **Specify — Complete the permanent and temporary upgrade catalogs.**
  Supply stable identities, prices, minimum Prestige, prerequisites, purchase windows, effects,
  and temporary-upgrade restrictions. Explain tier purchase/replacement and capacity-effect ordering;
  the existing seating/tent/flooring summary does not establish all interactions. Define when merchandise
  carryover starts and expires, including a cancelled or postponed show.
  Sources: [Circus Structures — Permanent Upgrades](docs/circus-structures.md),
  [Development Plan — milestones 4 and 6](docs/development-plan.md).

  **PDF answer (partial):** Upgrades may be bought between shows using circus Payout or personal funds. Permanent upgrades are bought once and affect every later show; each temporary upgrade is normally bought once per show for the next show. Merchandise is an explicit delayed-effect exception.

  > The PCs can upgrade their circus anytime between shows. Each upgrade has a price; the PCs can pay for the upgrade using either Payout or their own personal funds.
  >
  > — Printed p. 69 (PDF p. 11).
  > Permanent upgrades can be purchased only once, and convey their benefits to every circus show thereafter.
  >
  > — Printed p. 69 (PDF p. 11).
  > Each temporary upgrade can be purchased only once before each show. A temporary upgrade affects only the next show.
  >
  > — Printed p. 69 (PDF p. 11).

  Exact Table 4 entries (columns: Upgrade, Price, Min. Prestige; “—” is the source's absence of a minimum):

  > Acoustics 30 gp 5
  > Flooring
  > Safety net 20 gp —
  > Padded floors 100 gp 6
  > Seating
  > Bleachers 50 gp 5
  > Assigned seats 100 gp 10
  > Upholstered seats 250 gp 15
  > Spotlights 40 gp 4
  > Tent Expansions
  > Big 40 gp 3
  > Huge 100 gp 10
  > Massive 300 gp 15
  > Watermarked tickets 50 gp —
  >
  > — Printed p. 69 (PDF p. 11).
  > Beer 5 gp —
  > Confections 15 gp 5
  > Disposable binoculars 25 gp 8
  > Merchandise, basic 20 gp 3
  > Merchandise, quality 40 gp 6
  > Merchandise, extraordinary 60 gp 10
  >
  > — Printed p. 69 (PDF p. 11).

  Predecessor prerequisites follow the original table's indentation: Huge follows Big, and Massive follows Huge. The rendered table places flooring alternatives at equal indentation and seating alternatives at equal indentation; it does not show those as the same nested prerequisite chain as the tents.

  > Certain upgrades can be purchased only after the PCs have purchased a preceding upgrade, such as the huge and massive tent size increases. These upgrades are indented on Table 4: Circus Upgrades, and must be purchased in the order presented.
  >
  > — Printed p. 69 (PDF p. 11).

  Permanent effects, in source wording:

  > Acoustics: PCs and NPCs gain a +1 circumstance bonus to trick checks with the musical trait. After purchasing this upgrade, the bandleader role becomes available to PCs.
  >
  > — Printed p. 69 (PDF p. 11).
  > With a safety net, the DC of the flat checks to determine if a performer becomes injured or can perform at the next show decreases to 10. With padded floors, the flat check DC decreases to 5.
  >
  > — Printed p. 69 (PDF p. 11).
  > Seating: Quality seating options generate additional Excitement for the circus’s shows but reduce the circus’s maximum Anticipation by 10. At the start of each show, a circus with bleachers generates 5 Excitement. A circus with assigned seats generates 10 Excitement instead, and upholstered seats instead generate 20 Excitement.
  >
  > — Printed p. 69 (PDF p. 11).
  > Spotlights: This upgrade grants a permanent +1 increase to the circus’s Prestige. In addition, after purchasing this upgrade, a PC can choose the lighting role during circus shows.
  >
  > — Printed p. 69 (PDF p. 11).
  > A big tent increases the circus’s maximum Anticipation to 50, a huge tent increases the Anticipation limit to 100, and a massive tent increases the Anticipation limit to 200.
  >
  > — Printed p. 69 (PDF p. 11).
  > For the purpose of calculating Payout, the circus’s Prestige is treated as 2 points higher than it actually is.
  >
  > — Printed p. 69 (PDF p. 11).

  Temporary effects:

  > Beer: The circus generates an additional 2d6 Anticipation for the next show, and tricks with the audience trait gain a +2 circumstance bonus. However, the hecklers event (page 66) is automatically triggered, in addition to any other random event rolled.
  >
  > — Printed p. 69 (PDF p. 11).
  > Confections: The circus generates an additional 2d6 Excitement at the start of the next show.
  >
  > — Printed p. 69 (PDF p. 11).
  > Disposable Binoculars: There is no maximum Anticipation limit for the next show.
  >
  > — Printed p. 69 (PDF p. 11).
  > Merchandise: This temporary upgrade has no effect on the next show; instead, a fraction of the final Anticipation total of the next show is carried on to the show after that. With basic merchandise, the circus retains 25% of its final Anticipation (rounded down).
  >
  > — Printed p. 69 (PDF p. 11).
  > This amount is instead 50% with quality merchandise, or 75% with extraordinary merchandise.
  >
  > — Printed p. 69 (PDF p. 11).
  > cannot be purchased for two shows in a row (that is, it cannot “stack” with itself).
  >
  > — Printed p. 69 (PDF p. 11).

  Thus seating Excitement is 5, 10, or 20 rather than their sum, and a tent sets its capacity rather than adding all tent values. Merchandise bought for show N carries a fraction of N's final Anticipation into N+1; it is not extra Anticipation for N.

  **Unresolved:** Stable software IDs, cancellation/postponement and refund behavior, simultaneous purchase of different merchandise grades, and a general ordering rule for capacity changes are not specified. Flooring/seating predecessor purchases must not be inferred merely from increasing price. The text explicitly rounds basic merchandise down but does not separately restate rounding for the other percentages. [NOT STATED IN PDF]

  **Preparation decision — 2026-09-29:** Permanent upgrades may be purchased during either Interlude or Preparation. Temporary upgrades may be purchased in Preparation only. This stage availability does not change catalog prices, prerequisites, or per-show restrictions. See [Design Notes — Preparation Stage](docs/design-notes.md#preparation-stage).

- [ ] **Specify — Document payout formulas and settlement ordering.**
  Give the actual failure/success/critical-success formulas, all required inputs, gold-to-copper conversion,
  rounding order, Watermarked Tickets behavior, and event adjustments. Clarify when pre-award Prestige and
  other payout inputs are captured. The existing rules establish exact equality as critical success,
  failure rounding in gold, and pre-award Prestige, but omit the complete calculation.
  Sources: [Circus Structures — Prestige / Money and Show Outcomes](docs/circus-structures.md),
  [Development Plan — milestone 8](docs/development-plan.md).

  **PDF answer (partial):** Let A/E be final Anticipation/Excitement and P be Prestige before the current show's award, with applicable payout-only modifiers. E>A is success, E<A failure, and E=A critical success. Success pays P+A gp; critical success doubles that; failure pays floor((P+E)/4) gp.

  > If the PCs generate more Excitement than Anticipation, the show is a success. If they generate less Excitement than Anticipation, the show is a failure.
  >
  > — Printed p. 67 (PDF p. 9).
  > in order to put on a critically successful show, the PCs must generate exactly as much Excitement as Anticipation.
  >
  > — Printed p. 67 (PDF p. 9).
  > (Prestige + Final Anticipation) = Payout (in gp)
  >
  > — Printed p. 67 (PDF p. 9).
  > If the show was a critical success, the Payout is doubled.
  >
  > — Printed p. 67 (PDF p. 9).
  > then multiply the final amount by one-quarter (rounded down).
  >
  > — Printed p. 67 (PDF p. 9).
  > (Prestige + Final Excitement) × 1/4 = Payout (in gp)
  >
  > — Printed p. 67 (PDF p. 9).
  > Note that the PCs earn Payout before earning Prestige, so they use the Prestige value they had when they performed the show, not their new Prestige value after the show.
  >
  > — Printed p. 67 (PDF p. 9).

  Bad Weather doubles successful Payout, explicitly stacking with critical success for four times normal Payout. Watermarked Tickets treats Prestige as +2 for Payout only. Scalpers treats it as −3 with minimum 1 for Payout only.

  > This doubling stacks with the increase granted by the bad weather event (see opposite page), in which case the Payout is effectively quadrupled.
  >
  > — Printed p. 67 (PDF p. 9).
  > For the purpose of calculating Payout, the circus’s Prestige is treated as 2 points higher than it actually is.
  >
  > — Printed p. 69 (PDF p. 11).
  > Scalpers: The PCs’ Prestige (page 67) is treated as 3 less (minimum 1) when calculating Payout.
  >
  > — Printed p. 66 (PDF p. 8).

  After Payout, award +1/+2/+4 permanent Prestige for failure/success/critical success; baseline Prestige is 1. Profit is already net of baseline expenses and employee pay, so do not deduct those again.

  > The circus starts with a Prestige of 1, which the PCs increase by performing shows. After a failed show, the circus earns 1 Prestige. If the show was a success, then the circus earns 2 Prestige instead, or 4 Prestige if the show was a critical success.
  >
  > — Printed p. 67 (PDF p. 9).
  > The circus always earns enough money to cover its baseline expenses and pay its employees; Payout represents profit in excess of this baseline.
  >
  > — Printed p. 67 (PDF p. 9).

  **Source inconsistency:** The same page later says “If the PCs fail to generate more Excitement than Anticipation, their show is a failure.” That includes equality in ordinary language, conflicting with its explicit exact-match critical-success rule. The formulas above follow the explicit three-way definition; the conflicting sentence is retained here for review.

  **Unresolved:** The excerpt does not state the gold-to-copper conversion, how to order Watermarked Tickets with the Scalpers minimum, a floor for negative Payout, or the app's exact snapshot/transaction boundary. It gives no explicit reconciliation of the contradictory failure sentence. [NOT STATED IN PDF]

- [ ] **Specify — Define injury, recovery, and consumable-resource rules.**
  Document injury triggers, checks/DCs, availability restrictions, recovery timing, and flooring interactions.
  Define ownership and tracking of spell slots/alchemical items, when resources are spent/restored,
  and whether the app tracks full inventory or only show allocations. State how externally changed
  campaign resources are reconciled and how unavailable resources block actions.
  Sources: [Rules Review — Performer availability / Resource and money records](docs/rules-review.md),
  [Design Notes — Roll Resolution](docs/design-notes.md),
  [Development Plan — milestone 5](docs/development-plan.md).

  **PDF answer (partial):** A PC signature trick with any saving-throw choice gains Injury. A PC or NPC critically failing any check on an Injury trick rolls a flat DC 15 check; failure injures them and prevents further tricks for the show.

  > If an NPC or PC performing a trick with the injury trait critically fails any trick check, they have a chance of becoming injured. To determine if the performer is injured, roll a flat DC 15 check. On a failure, the performer becomes injured.
  >
  > — Printed p. 64 (PDF p. 6).
  > An injured performer (whether PC or NPC) cannot perform tricks for the rest of the show.
  >
  > — Printed p. 64 (PDF p. 6).

  At the next show's beginning, recovery requires another flat DC 15 check. Failure costs that next show, but there is no indefinite recovery loop: later shows require no check.

  > at the beginning of the next show, the injured performer must succeed at a flat DC 15 check to determine if they have recovered sufficiently to perform again.
  >
  > — Printed p. 64 (PDF p. 6).
  > A performer can miss only one show after the show in which they were injured. On subsequent shows, no check is necessary and the PC or NPC can once again perform as normal.
  >
  > — Printed p. 65 (PDF p. 7).

  Safety Net substitutes DC 10 for both injury and next-show checks; Padded Floors substitutes DC 5. Medic prevents becoming injured from critical failures of Injury tricks.

  > With a safety net, the DC of the flat checks to determine if a performer becomes injured or can perform at the next show decreases to 10. With padded floors, the flat check DC decreases to 5.
  >
  > — Printed p. 69 (PDF p. 11).
  > Medic: Performers can’t become injured from critically failing tricks with the injury trait.
  >
  > — Printed p. 66 (PDF p. 8).

  Alchemical spends and destroys one item in the performer's possession for +1 circumstance on the check. Magical spends one spell slot while performing, adding its level to Excitement only if the check succeeds or critically succeeds.

  > As part of the trick, the performer can expend one alchemical item in their possession. Upon doing so, the performer gains a +1 circumstance bonus to their trick check. This destroys the item.
  >
  > — Printed p. 64 (PDF p. 6).
  > While Performing the Trick, the performer can expend one spell slot of any level. If the performance succeeds or critically succeeds, the trick generates an additional amount of Excitement equal to the expended spell slot’s level.
  >
  > — Printed p. 65 (PDF p. 7).

  **Unresolved:** Inventory schema, spell-slot restoration, allocation versus complete inventory tracking, reconciliation with external campaign changes, precise optional-spending decision time, and app error handling for missing resources are not specified. The ordering of recovery checks versus role assignment/events is not fully stated. [NOT STATED IN PDF]

## Domain structures and invariants

- [ ] **Specify — Define the initial circus and new-game setup.**
  State starting funds, roster, owned upgrades, campaign date, and required PC/NPC input.
  Distinguish the naming-only milestone 1 shell from the intended usable setup.
  Four starting unlocked traits do not define the starting troupe, and NPC source data is an external gap.
  Sources: [Development Plan — milestones 1 and 3](docs/development-plan.md),
  [Trick Traits — Definitions, Access, and Validation](docs/trick-traits.md).

  **PDF answer (partial):** The adventure starts with the Circus of Wayward Wonders. It has six NPC tricks and an optional signature trick for each PC; its default Prestige is 1, maximum Anticipation 20, and initial accessible traits Agile, Animal, Fire, and Water.

  > At the start of this adventure, the PCs inherit the Circus of Wayward Wonders
  >
  > — Printed p. 59 (PDF p. 1).
  > At the beginning of the Extinction Curse Adventure Path, the Circus of Wayward Wonders has six NPC tricks and one signature trick for every PC in the party who wants to create one.
  >
  > — Printed p. 62 (PDF p. 4).
  > The default Prestige of the PCs’ circus starts at 1.
  >
  > — Printed p. 60 (PDF p. 2).
  > The circus’s starting maximum Anticipation is 20.
  >
  > — Printed p. 60 (PDF p. 2).
  > At the start of the Extinction Curse Adventure Path, the PCs have access to the following traits: agile, animal, fire, and water.
  >
  > — Printed p. 64 (PDF p. 6).

  PC trick definitions need the selected check, trait, name, and description, with level equal to the PC's (p. 63). NPC definitions require the fields described in the actor/check answer; the actual starting entries are outside this excerpt.

  **Unresolved:** Starting funds, specific starting NPC names/stat blocks, starting owned-upgrade inventory, campaign start date, and a numerical baseline Excitement are not supplied. Nor does the PDF specify a new-game form or custom-campaign defaults. [NOT STATED IN PDF]

- [ ] **Specify — Define the live-show record and state transitions.**
  Describe preparation, act assignment, active act, completed/unsettled, settled, and any supported
  cancellation states. Account for show/act/slot/participation IDs, actor and trick references, action/reaction
  budgets, checks, source values, resources, and pending choices. Define the allowed transitions and
  invariants for the 1/2/1/3 slots, empty slots, unavailable actors, and advancing an act.
  Sources: [Rules Review — Live show and act participation](docs/rules-review.md),
  [Development Plan — milestones 6–8](docs/development-plan.md).

  **PDF answer (partial):** The tabletop sequence is preparation → temporary upgrades → roles → random event → tally starting Anticipation → four acts → Payout (p. 61), followed by the Prestige award (p. 67). Acts use 1/2/1/3 tricks.

  > the opener (one trick), the build-up (two tricks), the big number (one trick), and the finale (three tricks).
  >
  > — Printed p. 60 (PDF p. 2).
  > At the beginning of each act, the PCs choose which trick or tricks to include in that act.
  >
  > — Printed p. 62 (PDF p. 4).
  > For acts with multiple tricks, the tricks happen concurrently in separate rings, but the PCs take turns describing their performances.
  >
  > — Printed p. 62 (PDF p. 4).
  > After each performer has used their actions for the act, the PCs choose the tricks for the next act; they repeat this until they’ve used their actions for the finale, after which the show is over.
  >
  > — Printed p. 62 (PDF p. 4).

  The paper Circus Show Sheet supplies circus/settlement/date, six downtime days, advertisement cost/Anticipation, initial values, temporary upgrades, PC role assignments, random event, performer/level/DC for each trick, three action/result rows with Excitement/Anticipation changes, and final Payout inputs (p. 68). These are useful domain information requirements, not a software state-machine specification.

  > CIRCUS SHOW SHEET
  >
  > — Printed p. 68 (PDF p. 10).
  > Performer Level Trick DC
  >
  > — Printed p. 68 (PDF p. 10).
  > Action (Result) EXC ANT
  >
  > — Printed p. 68 (PDF p. 10).

  **Unresolved:** Stable IDs, explicit active/unsettled/settled state records, cancellation, missing-slot handling, replacing unavailable performers mid-act, pending-choice persistence, and enforced transition guards are not defined. The three-row paper sheet also does not settle Time's fourth action/attempt. [NOT STATED IN PDF]

  **Interlude decision — 2026-09-29:** Include a distinct Interlude stage before show preparation for campaign activity and management. Its interface is confirmed; Preparation now retains every Interlude operation; Show Time management controls are now confirmed unavailable; finer transition/cancellation behavior remains open. See [Design Notes — Interlude Stage](docs/design-notes.md#interlude-stage) and [Circus Structures — Interlude Records to Add](docs/circus-structures.md#interlude-records-to-add). Original review questions and PDF findings remain above for context.

  **Preparation decision — 2026-09-29:** Preparation retains every Interlude operation and adds promotion and temporary purchases. Reuse shared current-state records and preserve existing adjustment identities across the transition. Stage navigation alone must not apply effects twice or restart Anticipation expiry. Show Time management controls are now confirmed unavailable; finer transition/cancellation behavior remains open. See [Design Notes — Preparation Stage](docs/design-notes.md#preparation-stage).

  **Show Time approval — 2026-09-29:** Approved flow: Show Time setup → Opener → Build-up → Big Number → Finale → Results → Finish Show. Preserve starting/current values separately; choose performers at each act start. Management controls are hidden during Show Time. Results remain correctable until Finish Show creates the read-only record; cancellation/back-navigation and detailed state mechanics remain open. See [Design Notes — Show Time Stage](docs/design-notes.md#show-time-stage--approved). Original review statements and PDF findings remain above for reference.

- [ ] **Specify — Introduce a usable campaign-time model.**
  Current dates are labels, but six consecutive downtime days, one show per week, recovery,
  and next-show carryover require ordering and intervals. Define dates/sequence numbers, week boundaries,
  level-up/redesign eligibility records, and handling of backdated corrections. Decide whether ordinary
  preparation and redesign downtime may overlap under the adopted rules.
  Sources: [Circus Structures — Supporting Type Reference / Actors](docs/circus-structures.md),
  [Trick Traits — PC Progression](docs/trick-traits.md),
  [Development Plan — milestone 6](docs/development-plan.md).

  **PDF answer (partial):** A show may occur at most once per week; there are six preparation days. Promotions use two consecutive downtime days, and redesign uses six consecutive downtime days unless triggered by gaining a level. Anticipation resets after a show or six days after its first generation without a show. Recovery and merchandise are keyed to subsequent shows, not a stated number of calendar days.

  > The PCs can put on up to one show per week.
  >
  > — Printed p. 61 (PDF p. 3).
  > You spend 2 consecutive days in town generating Anticipation for your next circus show.
  >
  > — Printed p. 61 (PDF p. 3).
  > A PC can change their signature trick (including its trick checks and trick traits) whenever they gain a level or by spending 6 consecutive downtime days redesigning the trick.
  >
  > — Printed p. 63 (PDF p. 5).
  > Anticipation lasts only 1 week, meaning the PCs have 6 days leading up to a show to build Anticipation. It resets to 0 after each show or 6 days after the first Anticipation is generated (in the event the PCs don’t put on a show).
  >
  > — Printed p. 60 (PDF p. 2).

  **Unresolved:** Calendar representation, fixed-week versus rolling-week enforcement, counting boundaries, overlapping redesign and preparation activities, preserving an unused level-up redesign opportunity, and backdated corrections are not specified. “1 week” versus “6 days after” needs an explicit counting convention for automation. [NOT STATED IN PDF]

  **Interlude decision — 2026-09-29:** Interlude represents between-show campaign activity and is not automatically the six-day preparation period. The user confirmed that its next-show Anticipation entries follow normal expiry/capacity rules, using the shared Anticipation window. Calendar representation and postponement handling within those rules remain to be designed. See [Design Notes — Interlude Stage](docs/design-notes.md#interlude-stage) and [Circus Structures — Interlude Records to Add](docs/circus-structures.md#interlude-records-to-add). Original review questions and PDF findings remain above for context.

- [ ] **Specify — Complete actor/check identities and NPC requirements.**
  The documented Check fields are a name, kind, and modifier, while trait bonuses depend on a specific skill.
  Define a stable skill/save/attack discriminator independent of editable names, relevant PC fields
  including any required proficiency data, and the structure/enforcement of NPC trick requirements.
  State which incomplete records may be saved and which missing values block participation.
  Sources: [Circus Structures — Actors / Supporting Type Reference](docs/circus-structures.md),
  [Trick Traits — Catalog / Definitions, Access, and Validation](docs/trick-traits.md).

  **PDF answer (partial):** An NPC trick has a name, level/DC, traits, check types, description, and any extra requirements. Use its listed check modifiers; it does not scale with PC progression or use PC limits. Its actual requirements/stat block must come from the separate NPC entry.

  > NPC tricks include the name of the trick, the trick’s level (and associated DC for the trick check), any traits associated with it, the types of trick checks used to perform the trick, a description of the trick, and additional requirements (if any).
  >
  > — Printed p. 63 (PDF p. 5).
  > NPC tricks may have any number of trick traits and types of trick checks; these are not limited by their level, as PC tricks are.
  >
  > — Printed p. 62 (PDF p. 4).

  PC trick choices can be a skill, saving throw, or attack roll. The PC's level sets trick level; other relevant values explicitly used include Charisma modifier for promotion, check modifier, and Costar proficiency (the Dance example refers to master rank).

  > The player decides their signature trick’s trick check (which can be a skill check, saving throw, or attack roll), chooses a trick trait (below), and names and dramatically describes the trick.
  >
  > — Printed p. 63 (PDF p. 5).
  > The signature trick’s level is equal to the PC’s level and increases whenever the PC gains a level.
  >
  > — Printed p. 63 (PDF p. 5).
  > if two other PCs successfully Costar with their ally and have the master proficiency rank in that trick check, the total circumstance bonus granted from the Costar reaction is +6 (rather than +3).
  >
  > — Printed p. 64 (PDF p. 6).

  Base check/trait capacities come from Table 2: level 1 has 1/1; level 4 increases checks to 2; level 8 traits to 2; level 12 traits to 3; level 16 checks to 3; level 20 traits to 4. Compulsory traits do not consume these slots.

  > 1 1 trick check, 1 trick trait
  > 4 2 trick checks
  > 8 2 trick traits
  > 12 3 trick traits
  > 16 3 trick checks
  > 20 4 trick traits
  >
  > — Printed p. 63 (PDF p. 5).

  **Unresolved:** Stable skill/save/attack identifiers, full proficiency/Aid calculation, structured NPC requirement encoding, complete relevant-PC-field schema, incomplete draft saving, and missing-data blocking behavior are not provided. [NOT STATED IN PDF]

- [ ] **Specify — Define actor and trick editing across time.**
  Explain recruitment, retained unlocks, retirement/removal, check deletion/renaming, PC progression,
  and trick redesign eligibility. Decide what happens to a trick invalidated by an edit and whether
  actor/check changes affect an already prepared or active show. Preserve historical references without
  assuming that retaining only the current actor record is sufficient.
  Sources: [Design Notes — Player Characters and NPC Performers](docs/design-notes.md),
  [Development Plan — milestones 3 and 8](docs/development-plan.md).

  **PDF answer (partial):** NPC trick levels remain fixed. PC signature tricks grow with the PC and can be redesigned on a level gain or after six consecutive downtime days. Hiring an NPC grants access to that NPC trick's traits.

  > a 6th-level NPC trick is always a 6th-level NPC trick.
  >
  > — Printed p. 62 (PDF p. 4).
  > The signature trick’s level is equal to the PC’s level and increases whenever the PC gains a level.
  >
  > — Printed p. 63 (PDF p. 5).
  > A PC can change their signature trick (including its trick checks and trick traits) whenever they gain a level or by spending 6 consecutive downtime days redesigning the trick.
  >
  > — Printed p. 63 (PDF p. 5).
  > These NPC tricks might have new trick traits (below), to which the PCs gain access as soon as they hire the NPC.
  >
  > — Printed p. 62 (PDF p. 4).
  > to gain access to a trait, the circus must have hired an NPC performer whose trick includes that trait.
  >
  > — Printed p. 63 (PDF p. 5).

  **Unresolved:** The text does not explicitly state what happens to trait access after an NPC leaves, even though “must have hired” supports the project's retained-access interpretation. Retirement/removal, check renaming/deletion, skill-edit workflows, edits during an active show, invalidated tricks, and historical versioning are not specified. [NOT STATED IN PDF]

  **Interlude decision — 2026-09-29:** Interlude provides NPC recruitment, trick creation, and PC level changes. This does not by itself waive existing trick progression or redesign timing rules, or waive the confirmed restriction on management editing during Show Time. Recruitment, trick creation, and PC level changes are explicitly available in Preparation. See [Design Notes — Interlude Stage](docs/design-notes.md#interlude-stage) and [Circus Structures — Interlude Records to Add](docs/circus-structures.md#interlude-records-to-add). Original review questions and PDF findings remain above for context.

- [ ] **Resolve — Define custom-trait lifecycle and manual-effect support.**
  Creation is specified, but editing, retirement/deletion, existing references, and historical versions
  are not. Define prerequisite validation during load/edit, including cyclic references or definitions
  arriving out of order, and the UI for explicit unlock grants. Explain how a GM applies an unsupported
  descriptive effect when broader override fields remain undecided; do not imply every custom trait
  can already be represented by the numeric roll adjustment.
  Sources: [Trick Traits — GM-Created Traits](docs/trick-traits.md),
  [Development Plan — milestones 3 and 5 / Working Sequence](docs/development-plan.md).

  **PDF answer (partial):** Built-in selection requires access from a hired NPC, respects progression limits, and includes the Emotion prerequisite and compulsory-tag rules. The PDF explicitly permits GM-created backstage roles and random events, but that is not a custom-trait lifecycle specification.

  > A PC must have access to a trait to add it to their signature trick
  >
  > — Printed p. 63 (PDF p. 5).
  > A trick must have either the alchemical or magical trait in order to have the emotion trait.
  >
  > — Printed p. 64 (PDF p. 6).
  > The GM can create additional non-performer roles for the PCs, using the roles listed here as baselines.
  >
  > — Printed p. 66 (PDF p. 8).
  > The GM can create additional random events, using the following events as baselines.
  >
  > — Printed p. 66 (PDF p. 8).

  **Unresolved:** Custom-trait creation/editing/deletion, stable IDs, explicit GM unlocks, prerequisite graphs and cycles, save-load ordering, historical versions, executable effects, and manual-override UI are not defined in the PDF. These remain project extensions. [NOT STATED IN PDF]

- [ ] **Specify — Define the transaction and ownership model.**
  Set opening balance, contribution/correction categories, insufficient-funds/negative-balance policy,
  allowed monetary ranges, purchase funding, and transaction links to shows/upgrades.
  Explain whether balance is derived or cached and how it stays consistent with the ledger.
  Define reversal behavior and any supported resale/removal; retained tier purchase records and permanent
  Spotlight Prestige must remain consistent with the chosen ownership/history representation.
  Sources: [Circus Structures — Circus / Permanent Upgrades / Prestige / Money](docs/circus-structures.md),
  [Development Plan — milestone 4](docs/development-plan.md).

  **PDF answer (partial):** Circus Payout may fund circus expenses; PCs may use personal funds for advertisements/upgrades. Payout is already net of routine expenses and wages. Permanent upgrades are bought once and provide continuing benefits; Spotlights gives permanent +1 Prestige.

  > Each upgrade has a price; the PCs can pay for the upgrade using either Payout or their own personal funds.
  >
  > — Printed p. 69 (PDF p. 11).
  > The PCs can purchase an advertisement tier using their circus Payout or their own adventuring money
  >
  > — Printed p. 61 (PDF p. 3).
  > The circus always earns enough money to cover its baseline expenses and pay its employees; Payout represents profit in excess of this baseline.
  >
  > — Printed p. 67 (PDF p. 9).
  > Payout can be used only for circus-related expenses
  >
  > — Printed p. 67 (PDF p. 9).
  > Spotlights: This upgrade grants a permanent +1 increase to the circus’s Prestige.
  >
  > — Printed p. 69 (PDF p. 11).

  **Unresolved:** Opening balance, transaction categories/IDs, mixed funding, debt/negative balances, monetary limits, cached versus derived balance, corrections/reversals, refunds/resale, ownership deletion, and handling retained purchase records are not defined. The source does not specify removing an already earned Spotlight Prestige point when an inventory record is removed. [NOT STATED IN PDF]

  **Interlude decision — 2026-09-29:** Interlude permits permanent-upgrade purchases and explicit deposits from personal funds into the circus budget, distinct from show Payout. Temporary purchases are excluded. Full personal-wallet accounting is not specified. See [Design Notes — Interlude Stage](docs/design-notes.md#interlude-stage) and [Circus Structures — Interlude Records to Add](docs/circus-structures.md#interlude-records-to-add). Original review questions and PDF findings remain above for context.

- [ ] **Specify — Define validation boundaries and referential integrity.**
  List invariants enforced during creation, editing, save loading, and show execution, with handling for
  duplicate/blank IDs, dangling actor/check/trait references, missing NPC DCs, and invalid ownership.
  Clarify which drafts may remain incomplete. The documents acknowledge that direct struct edits bypass
  the signature-trick validator; specify the future authoritative validation boundary.
  Sources: [Rules Review — Current Model](docs/rules-review.md),
  [Trick Traits — Definitions, Access, and Validation](docs/trick-traits.md),
  [Development Plan — milestone 2](docs/development-plan.md).

  **PDF answer (partial):** The source supplies game invariants to validate: performers use only their own tricks; PC traits require access and progression limits; Emotion needs Alchemical or Magical; upgrades have prices/minimum Prestige and some predecessor requirements; each trick normally occupies only one act per show. NPC rolls need their listed DC/modifiers.

  > A performer, whether NPC or PC, can perform only their own trick
  >
  > — Printed p. 62 (PDF p. 4).
  > A PC must have access to a trait to add it to their signature trick
  >
  > — Printed p. 63 (PDF p. 5).
  > A trick must have either the alchemical or magical trait in order to have the emotion trait.
  >
  > — Printed p. 64 (PDF p. 6).
  > When an NPC performs their trick, either a player or the GM can roll the trick checks for the NPC, using the DC and the modifiers listed in the trick description.
  >
  > — Printed p. 62 (PDF p. 4).
  > Some circus upgrades (page 69) require the circus to have a minimum Prestige before they can be purchased.
  >
  > — Printed p. 67 (PDF p. 9).

  **Unresolved:** Application validation boundaries, blank/duplicate IDs, reference integrity, incomplete drafts, malformed saves, and bypass-proof mutation APIs are not covered. Rules constraints do not themselves prescribe a software validation architecture. [NOT STATED IN PDF]

## Persistence, corrections, and user workflows

- [ ] **Resolve — Define save selection and lifecycle behavior.**
  Decide single versus multiple circuses, Continue selection, save locations/slots, explicit save/autosave,
  import/export scope, and backup/recovery behavior. Specify persistence on Android suspension or process
  termination and how interrupted writes are reported. Preserve corrupt data for recovery and define
  unsupported/newer-version handling and schema migration policy.
  Source: [Development Plan — milestones 2, 7, and 9](docs/development-plan.md).

  **PDF answer:** No direct answer. Save slots, multiple circuses, Continue selection, paths, autosave, import/export, backup, interrupted writes, Android lifecycle behavior, schema versions, and migration are not discussed in the tabletop rules. [NOT STATED IN PDF]

  **Earlier user decision — 2026-09-29:** Committed game changes must take effect immediately. Save timing/autosave and durability remain separate decisions; immediate application alone does not specify when a disk write occurs. See [Design Notes — Committed Changes and History](docs/design-notes.md). The original PDF-only findings above are retained for reference.

- [ ] **Clarify — Define access to an existing in-memory circus from the menu.**
  Design Notes says returning to the menu preserves the active circus while Continue stays disabled.
  Explain how the GM reopens that circus, and what New Circus, Quit, Android Back, and closing a naming
  form do when unsaved work exists. Specify this behavior for both the current shell and the saved app.
  Sources: [Design Notes — opening status](docs/design-notes.md),
  [Development Plan — milestones 1 and 2](docs/development-plan.md).

  **PDF answer:** No direct answer. The PDF has no application menu, in-memory record model, Continue/New Circus behavior, Quit/Android Back handling, or unsaved-work policy. [NOT STATED IN PDF]

- [ ] **Specify — Define correction/undo boundaries and settlement transactions.**
  Distinguish correcting an entered number from changing a chosen action or an external roll.
  Define how later dependent checks, resources, injuries, outcomes, payouts, and Prestige are recomputed.
  Set policy for editing settled shows after subsequent purchases/shows; record intentional changes
  without silently rerolling anything. Explain how show completion, payment, awards, and carryover remain
  exactly once across save interruption/retry.
  Sources: [Design Notes — Open Mechanics Questions](docs/design-notes.md),
  [Development Plan — milestones 7 and 8](docs/development-plan.md).

  **PDF answer (partial):** Settlement uses Payout before the current show's Prestige award. Clowns are a specific in-game result-changing action, not a general permission to undo anything: one failure becomes success or one critical failure becomes failure.

  > Note that the PCs earn Payout before earning Prestige, so they use the Prestige value they had when they performed the show, not their new Prestige value after the show.
  >
  > — Printed p. 67 (PDF p. 9).
  > A failed trick becomes a success instead, or if it was a critical failure, it is instead a failure.
  >
  > — Printed p. 65 (PDF p. 7).

  **Unresolved:** User correction versus new roll/action, dependency recomputation, edits after later shows/purchases, audit records, atomic settlement, retry protection, and reversal of resources/injury after a corrected check are not specified. [NOT STATED IN PDF]

  **Earlier user decision — 2026-09-29:** Every committed game change must be reversible, except finished shows, which cannot be changed through the interface. Corrections to active shows remain required. A visible action-history log is unnecessary. Finish Show on Results is now the approved finalization boundary. Remaining design work concerns undo depth/persistence, dependencies across finished shows, and exactly-once settlement mechanics; it must preserve finished history. See [Design Notes — Committed Changes and History](docs/design-notes.md). The original PDF-only findings above are retained for reference.

  **Show Time approval — 2026-09-29:** Finish Show on Results is the explicit finalization boundary. Active-show results can be corrected beforehand. It records payout, Prestige, and history once and creates the read-only finished record. Compact current-act result rows provide correction controls without a separate action-history screen. Dependency handling and transaction implementation remain open. See [Design Notes — Show Time Stage](docs/design-notes.md#show-time-stage--approved). Original review statements and PDF findings remain above for reference.

- [ ] **Specify — Define the historical snapshot contract.**
  Enumerate which actor/check values, trait and effect definitions, die/entered values, modifiers, DCs,
  preparation/event decisions, resource changes, and payout inputs must remain reproducible.
  Stable IDs alone do not preserve mutable values. Decide whether detailed history can be edited/deleted
  or archived while retaining the completed-show awards on which derived Prestige depends.
  Sources: [Circus Structures — Prestige / CompletedShow](docs/circus-structures.md),
  [Development Plan — milestone 8](docs/development-plan.md).

  **PDF answer (partial):** The source explicitly recommends tracking Anticipation, Excitement, and trick/act outcomes using its show sheet. Page 68 includes performer level/DC, action results and EXC/ANT changes, initial values, preparation/roles/event, and final Payout inputs.

  > The players can track the progress of each circus show, including Anticipation, Excitement, and the outcome of tricks and acts, using a copy of the Circus Show Sheet on page 68.
  >
  > — Printed p. 59 (PDF p. 1).
  > Performer Level Trick DC
  >
  > — Printed p. 68 (PDF p. 10).
  > Action (Result) EXC ANT
  >
  > — Printed p. 68 (PDF p. 10).
  > Final EXC
  >
  > — Printed p. 68 (PDF p. 10).
  > Final ANT
  >
  > — Printed p. 68 (PDF p. 10).
  > Total Payout
  >
  > — Printed p. 68 (PDF p. 10).

  **Unresolved:** The PDF does not mandate immutable actor/trait/effect snapshots, natural dice and modifier provenance, history deletion/editing/archival policy, or deriving total Prestige from retained records. Its paper sheet identifies useful information but not a complete historical replay contract. [NOT STATED IN PDF]

  **Earlier user decision — 2026-09-29:** Show history is a core feature. Finished shows are read-only through the interface and must not be rewritten by changes to current records. A visible action-history feature is unnecessary. Detailed snapshot fields and retention mechanics still need review within that boundary. See [Design Notes — Committed Changes and History](docs/design-notes.md). The original PDF-only findings above are retained for reference.

  **Show Time approval — 2026-09-29:** The approved interface preserves starting versus current values and produces the read-only historical record when Finish Show is committed. Retain the values used for results and payout so later management edits cannot rewrite them. Exact snapshot fields still need design. See [Design Notes — Show Time Stage](docs/design-notes.md#show-time-stage--approved). Original review statements and PDF findings remain above for reference.

- [ ] **Specify — Document the core screen workflows and error states.**
  Beyond the menu and Prestige popup, define the minimum fields/actions and transitions for roster,
  trick/custom-trait editing, purchases, preparation, live acts, settlement, and history.
  Show how invalid input and incomplete data are repaired, where actions lock, and how drag assignments
  work through touch selection. Detailed styling can remain deferred; these behavior contracts are needed
  to make the separate views a complete usable workflow.
  Sources: [Design Notes — Confirmed Direction / Interface Ideas](docs/design-notes.md),
  [Development Plan — milestones 3–8](docs/development-plan.md).

  **PDF answer (partial):** The show sheet gives a paper workflow: downtime, showtime upgrades/roles/event, four acts, and Payout. The rules choose performers at each act's start and forbid changing a backstage role until the next show.

  > Downtime Activities
  >
  > — Printed p. 68 (PDF p. 10).
  > TEMPORARY UPGRADES
  >
  > — Printed p. 68 (PDF p. 10).
  > NON-PERFORMER ROLES
  >
  > — Printed p. 68 (PDF p. 10).
  > At the beginning of each act, the PCs choose which trick or tricks to include in that act.
  >
  > — Printed p. 62 (PDF p. 4).
  > Once chosen, a non-performer role cannot be changed until the next show.
  >
  > — Printed p. 66 (PDF p. 8).

  **Unresolved:** Screen fields beyond the paper record, navigation, save/edit controls, invalid-input repair, incomplete-data UI, touch/drag behavior, and application action locks are not specified. The paper sheet is a reference, not an approved screen layout. [NOT STATED IN PDF]

  **Earlier user decision — 2026-09-29:** Prestige uses a popup with explanatory notes and contributions. Complex concepts use dedicated guided interfaces; trick creation uses several screens with detailed instructions. Committed changes apply immediately and remain reversible except for finished shows. Field layouts, draft/commit transitions, and validation/error flows remain to be specified. See [Design Notes — Committed Changes and History](docs/design-notes.md). The original PDF-only findings above are retained for reference.

  **Interlude decision — 2026-09-29:** Add an Interlude interface for recruitment, tricks, level changes, permanent purchases, explained next-show Anticipation/circus Prestige adjustments, and personal-fund contributions. Prestige adjustment reasons belong in its popup; keep explanations for next-show Anticipation in preparation. A general action-history screen remains unnecessary. See [Design Notes — Interlude Stage](docs/design-notes.md#interlude-stage) and [Circus Structures — Interlude Records to Add](docs/circus-structures.md#interlude-records-to-add). Original review questions and PDF findings remain above for context.

  **Preparation decision — 2026-09-29:** Preparation exposes all Interlude management workflows plus promotion and temporary-upgrade purchases. It must continue to provide permanent purchases, recruitment, tricks, PC level changes, explained adjustments, and personal contributions through shared data and validation. See [Design Notes — Preparation Stage](docs/design-notes.md#preparation-stage).

  **Show Time approval — 2026-09-29:** The current-act Show Time layout and its complete content are approved: circus/settlement/date; persistent EXC/ANT/max ANT/Prestige; setup roles/events/upgrades; performer/trick/DC/check/action/effect controls; roll entry and immediate results; eligible assistance/clowns/backstage choices; compact correction rows; Results and Finish Show. Use a compact overview of all four acts and keep same-act performers accessible. Management controls are hidden. Detailed error messages and styling remain to be designed. See [Design Notes — Show Time Stage](docs/design-notes.md#show-time-stage--approved). Original review statements and PDF findings remain above for reference.

## Acceptance and documentation maintenance

- [ ] **Specify — Turn broad completion criteria into reference scenarios.**
  Document expected inputs and outputs for ordinary/Agile/Time attempts, Costar/Dance, Injury,
  trait prerequisites and unlock retention, upgrade replacements, payout rounding and equality,
  custom traits, corrupt/interrupted saves, and correction/resume across multiple shows.
  Distinguish unresolved rules from accepted expected results. The plan calls for worked examples
  and acceptance scenarios but does not supply them.
  Sources: [Development Plan — milestones 5–9](docs/development-plan.md),
  [Rules Review — Source Wording](docs/rules-review.md).

  **PDF answer (partial):** The PDF supplies several concrete rules examples suitable as reference scenarios:

  | Source | Stated scenario and expected result |
  | --- | --- |
  | p. 63 (PDF 5) | Level-3 trick: success +3 EXC; critical success +3 EXC/+2 ANT; critical failure −2 EXC. |
  | p. 65 (PDF 7) | Gerard, level 4, DC 19, Agile: results 26, 20, 9 produce +4, +4, −2 EXC; injury flat check 16 avoids injury. |
  | p. 65 (PDF 7) | Janelle, level 4: 29 is a critical success (+4 EXC/+2 ANT); 17 fails; clowns convert the failure to success, for a total +8 EXC/+2 ANT. |
  | p. 64 (PDF 6) | Dance with two successful master-proficient Costar helpers gives +6 circumstance, not +3. |
  | p. 67 (PDF 9) | Prestige 3 and successful show with 20 ANT pays 23 gp; failed show with 15 EXC pays 4 gp after rounding down. |
  | p. 69 (PDF 11) | Merchandise applied to final ANT 20 gives the following show +5/+10/+15 ANT for basic/quality/extraordinary. |

  Exact evidence for these examples:

  > For example, a 3rd-level trick generates 3 Excitement with each successful trick check, 3 Excitement and 2 Anticipation for each critical success, and –2 Excitement for each critical failure.
  >
  > — Printed p. 63 (PDF p. 5).
  > Including his check modifier, his result is 26, which handily overcomes the DC of 19 for 4th‑level characters and generates 4 Excitement.
  >
  > — Printed p. 65 (PDF p. 7).
  > taking the –4 and –8 penalties on his rolls (because his trick has the agile trait) and getting results of 20 ( just beating the DC) and 9 (a critical failure). His second roll generates 4 Excitement, but his last roll, a critical failure, subtracts 2 Excitement from the circus’s running total.
  >
  > — Printed p. 65 (PDF p. 7).
  > Thankfully he rolls a 16, allowing him to avoid injury.
  >
  > — Printed p. 65 (PDF p. 7).
  > Janelle attempts a Nature trick check for her first action, and her result is a 29—a critical success! She generates 4 Excitement but also 2 Anticipation.
  >
  > — Printed p. 65 (PDF p. 7).
  > She decides to attempt another Nature trick check for her second action but gets only a 17—a failure. For her last action, she Sends in the Clowns, changing her failed trick check to a success instead and generating a total of 8 Excitement and 2 Anticipation from her performance.
  >
  > — Printed p. 65 (PDF p. 7).
  > if two other PCs successfully Costar with their ally and have the master proficiency rank in that trick check, the total circumstance bonus granted from the Costar reaction is +6 (rather than +3).
  >
  > — Printed p. 64 (PDF p. 6).
  > For example, if the PCs’ circus has a Prestige of 3 and they perform a successful show with 20 Anticipation, then they would earn 23 gp as their Payout (3 + 20 = 23 gp). However, if they generated only 15 Excitement during the show and thus their performance was a failure, they would earn only 4 gp instead (3 + 15 = 18, and 18 × 1/4 = 4.5 gp).
  >
  > — Printed p. 67 (PDF p. 9).
  > For example, if this upgrade were purchased for a show that ultimately generated a final Anticipation of 20, then the show after that would start with an additional 5, 10, or 15 Anticipation (for basic, quality, or extraordinary merchandise, respectively).
  >
  > — Printed p. 69 (PDF p. 11).

  Rules also directly specify ordinary repeat penalties (−5/−10), Emotion's prerequisite, noncumulative seating values, and exact-match critical success; the earlier answers quote these. Time's fourth penalty is stated, but its action budget is not.

  **Unresolved:** These examples are not a complete acceptance suite. Expected results for unresolved interactions, custom traits, corrupt/interrupted saves, corrections, resume, and multi-show software behavior are not supplied. Additional boundary scenarios require derived tests or design decisions, not claims that the PDF states them. [NOT STATED IN PDF]

- [ ] **Specify — Define target-device and release acceptance limits.**
  Record supported Windows/Android versions, representative tablet sizes/orientations and input methods,
  and concrete readability, keyboard, suspension/resume, and installation checks.
  Define which physical-device checks are required before acceptance and what known limitations are
  acceptable. Architecture targets and GL Compatibility alone do not define the supported user environment.
  Sources: [AGENTS.md — Project Structure / Testing Guidelines](AGENTS.md),
  [Development Plan — milestones 1 and 9](docs/development-plan.md).

  **PDF answer:** No direct answer. Supported operating-system versions, tablet dimensions/orientation, input methods, readability, keyboard behavior, suspension, installation, signing, device testing, and release limitations are not defined by this tabletop rules excerpt. [NOT STATED IN PDF]

- [ ] **Clarify — Separate requirements, implementation reports, and validation evidence.**
  The docs mix intended behavior with claims that APIs, builds, and checks are implemented/passing.
  Establish a clear status convention and precedence between design decisions, rule rulings,
  structure descriptions, and the roadmap. Date or link validation evidence when documenting completion,
  and keep known gaps consistent across the documents.
  Sources: [Rules Review — Current Model](docs/rules-review.md),
  [Circus Structures — opening status](docs/circus-structures.md),
  [Development Plan — Direction and Current State](docs/development-plan.md).

  **PDF answer:** No direct answer. The PDF does not describe this project's requirements/status conventions, software implementation, test evidence, document precedence, or maintenance process. Its rules can substantiate game mechanics, but cannot verify claims that project features or builds work. [NOT STATED IN PDF]

Suggested review order: agree scope and rules authority; settle roll/action and preparation/settlement
rules; define record invariants and time; finalize save/correction workflows; then refine screens and
acceptance cases. Already acknowledged gaps remain on this list because they prevent the documents
from fully specifying the app, not because unfinished milestones are themselves defects.
