# Circus Structures

The C++17 model is defined in `src/domain/circus.h`, with trait definitions and validation in `src/domain/trick_traits.h`. It remains independent of Godot. The native `CircusApp` control in `src/app/` now owns an optional in-memory `Circus`, creating it through the naming form and reading its initial values for the overview. Persistence is not implemented yet.

## Circus

| Field | Purpose |
| --- | --- |
| `name` | Display name of the circus. |
| `actors` | Actor records keyed by stable IDs, independent of names. |
| `permanent_upgrades` | Purchased upgrades keyed by type, preventing duplicate ownership. |
| `show_history` | Completed shows keyed by stable IDs. Core feature and source of prestige; finished records are read-only through the interface. |
| `balance` | Current funds as an integer number of copper units. Transaction history is deferred. |
| `trait_catalog` | Built-in trait definitions plus GM-created definitions for this circus. |
| `unlocked_traits` | Starting and retained trait access; current NPC tricks also grant access through `available_trick_traits()`. |

There is no stored prestige total. `calculate_prestige()` produces its breakdown from current source records. The confirmed Interlude workflow requires additional source records described below; these are future requirements, not fields already present in this table.

## Interlude Records to Add

Interlude is a dedicated between-show interface that uses the actor, trick, permanent-upgrade, and money models. It also needs records for explained GM-entered changes to next-show Anticipation and circus Prestige. Preparation uses the same management and adjustment records: it retains every Interlude operation and adds promotion and temporary-upgrade purchases. These records and their API are not implemented by the current type reference.

Each adjustment needs a stable identity, the affected quantity, the numeric change, the GM's reason, and its scope (circus Prestige or next-show Anticipation). Preserve enough information to apply it once, reverse it consistently, save/load it, and explain the resulting value. The exact calendar/date fields and assignment of a next-show adjustment to a concrete show remain to be defined. Reasons are explanatory data, not executable rules.

Prestige adjustments must extend the typed source representation and derived breakdown; directly overwriting a Prestige total or fabricating a completed show would lose the actual source. The popup must include each adjustment's amount and reason. Anticipation adjustments must remain attributable during preparation and follow normal expiry/capacity rules: excess generation is ignored, and the shared next-show Anticipation pool resets after a show or six days after first generation without a show. Retain campaign timing and enough source information to explain the effective contribution; do not bank capped excess or assign each entry a fresh expiry window. Binding entries to a concrete show and cancellation/postponement handling within those rules remain to be designed.

Personal contributions into the circus budget need distinct money records with the contributed amount and source. They are not show income and must not change past Payout. Full tracking of personal wallets is not yet specified. Neither explained adjustments nor contribution records require a general action-history UI.

Commits in Interlude and Preparation apply immediately and remain reversible while preserving finished-show history. Both stages permit recruitment, trick creation, PC level changes, permanent purchases, explained adjustments, and personal contributions. Promotion and temporary purchases are available in Preparation only. Existing rule validation still applies. Shared operations must use the same source records so entering Preparation cannot duplicate an adjustment, deposit, recruitment, or purchase, or restart Anticipation expiry. Derived preparation values must reflect current management data.

## Actors

An `Actor` has a name and either a `PlayerCharacter` or `NpcPerformer` profile. Both profiles define available checks and a trick referencing those checks by ID.

- PCs have a character level, editable checks, and an optional signature trick. A backstage-only PC can exist without a trick.
- NPCs have a fixed trick level, a supplied DC, check modifiers, a trick, and requirements.
- Each check identifies its kind: skill, saving throw, or attack. An absent modifier means unknown, not zero.

The model provides places for character values without deciding whether roll entry includes their modifiers. Live show participation and backstage assignments remain separate future structures.

Rules constraints, partially validated by the signature-trick helpers (printed pages 62-66):

- Only the owning performer can perform a trick. Check IDs in that trick must resolve within that performer's profile.
- A PC signature trick's level follows `PlayerCharacter.level`; its base DC comes from the external level-based DC table. NPC tricks use their listed level, DC, and modifiers, with no PC progression limit on the number of checks or traits.
- PC limits progress from one check/one optional trait at level 1 to two checks at level 4, two traits at level 8, three traits at level 12, three checks at level 16, and four traits at level 20. Compulsory traits do not count against these trait limits. The PDF also references an external feat that can grant additional traits.
- Signature-trick redesign is allowed on gaining a level or after six consecutive downtime days. Editing a character's campaign values does not itself authorize redesigning their trick.
- Trait access comes from recruited NPCs; the starting troupe provides agile, animal, fire, and water. The typed trait catalog and signature-trick validator cover access, level limits, Emotion's prerequisite, and automatic/compulsory tags. See [Trick Traits](trick-traits.md) for the complete list and implemented rules.
- Non-performer roles are for PCs, exclude performing for that show, and stay fixed until the next show. Only one PC may fill a particular role in a show; some roles require upgrades.

## Permanent Upgrades

The upgrade enum covers all permanent upgrades on printed page 69 of the PDF. Each owned record stores the campaign purchase date and actual price paid. Catalog prices, purchase prerequisites, and effects other than prestige will be defined with the purchasing and modifier systems. Purchase validation is not implemented. Signature-trick drafts have a separate validator; redesign timing remains deferred.

Retain purchase records when moving to a higher tier. Their effects must follow the replacement rules: seating grants 5, 10, or 20 starting Excitement, not their sum; its capacity reduction is 10. Tent tiers set the capacity to 50, 100, or 200. Flooring sets injury/recovery check DCs to 10 or 5. Purchase history is not a list of bonuses to add indiscriminately.

## Prestige and Its Explanation

The detailed rules on printed pages 67 and 69 give:

- Starting prestige: **+1**.
- Each completed show: **+1** for failure, **+2** for success, or **+4** for critical success.
- Owning Spotlights: **+1** once.

For example, starting prestige, Spotlights, and one successful show total **4**. The popup will show all three contributions. Each contribution carries its points, label, campaign date where available, and a typed source reference. Both the displayed prestige value and the popup must use the same calculated breakdown.

In addition to those built-in rules, the confirmed app workflow must include explained GM-entered Prestige adjustments from Interlude or Preparation as distinct sources. This is a required extension to the current calculation/source types, not an implemented rule listed above.

Watermarked Tickets affect prestige only for payout calculation and do not add permanent prestige. Payout-related modifiers belong in that separate calculation.

Completed show outcomes supply historical awards; opening the popup never awards points again. Future payout calculation must use prestige before adding the current show's award. The minimal show record currently stores its name, date, outcome, and payout; detailed check history and historical character snapshots are deferred.

Spotlights grant a permanent increase. Keep their ownership record as the source of that increase; deleting it currently removes the calculated point. The PDF supplies no upgrade resale/removal rule. A future inventory-management feature must not silently revoke earned prestige.

## Money and Show Outcomes

`Money.copper` is an implementation storage choice. The PDF's payout formulas use gold pieces, and a failed show's payout is rounded down in gold before conversion to storage units (printed page 67).

`ShowOutcome` describes the whole show: Excitement below Anticipation is `Failure`, above is `Success`, and equality is `CriticalSuccess`. Individual checks additionally have critical failure, so they will need a separate result type. `CompletedShow.outcome` is currently supplied by the caller; the model does not yet calculate or validate it.

Payout is profit after baseline expenses and employee pay; those costs must not be deducted again. Circus profits are for circus expenses. PCs can contribute personal funds toward purchases. The confirmed Interlude and Preparation interfaces also let the GM record contributions directly into the circus budget, so the future ledger must distinguish these deposits from show income and avoid counting them twice when money is later spent.

## Show Time Records to Add

The approved Show Time interface needs a live-show record distinct from the completed historical record. It must retain circus/settlement/date, preparation inputs and purchased upgrades, backstage assignments, externally entered events and choices, starting values, current values, performer availability, and progress through setup, four acts, and Results.

Each act needs its 1/2/1/3 performer/trick assignments, the checks and DCs used, applicable traits/modifiers, actions/reactions and repeat penalties, resource and injury effects, pending choices, and compact action/result rows that support correction. Record sufficient source values for later management edits to leave completed history unchanged. This is a future information contract, not a claim that these types already exist.

The active Results state remains correctable. Finish Show settles payout and Prestige exactly once and creates the read-only completed record. Preserve pre-award Prestige and the other payout inputs; reopening a view must not repeat settlement. Management mutations such as recruitment, level/trick editing, and purchases are unavailable through Show Time, while active-show corrections remain supported.

The exact fields, undo dependencies, save mechanics, and unresolved Time/NPC-clown/roll-resolution rules still need design. See [Design Notes — Show Time Stage](design-notes.md#show-time-stage--approved).

## Required Mutation and History Behavior

The following are confirmed requirements for future mutation and persistence workflows, not claims about the current structs' enforcement. A committed change takes effect immediately and must be reversible. Finished shows are the exception: the interface cannot edit, delete, or reopen them for modification. Historical actor/check/modifier values must remain independent of later changes to current records.

Undo and correction must keep affected current values consistent without rewriting finished-show records. The finalization boundary is the explicit Finish Show action on Results. Handling changes with dependencies across that boundary still needs design. Immediate game-state application does not by itself specify when data is written to disk.

A visible action-history feature is unnecessary. Retain the data required for calculations, reversible changes, active-show resume, and finished-show details; a transaction ledger or internal undo data does not imply an action-log screen. Detailed historical fields and undo retention remain to be specified.

## Supporting Type Reference

These are the remaining named types in `src/domain/circus.h`; `Circus`, `Actor`, `PlayerCharacter`, and `NpcPerformer` are described above.

| Type | Stored fields or alternatives | Meaning |
| --- | --- | --- |
| `ActorId`, `ShowId`, `CheckId` | String aliases | Stable application keys; names may change. Check IDs are local to their owner's profile. |
| `Money` | `copper` | Exact signed integer amount; no transaction or spending validation yet. |
| `CheckKind` | `Skill`, `SavingThrow`, `Attack` | Category of a trick check; flat checks need separate handling. |
| `Check` | `name`, `kind`, optional `modifier` | A performer's available check. Missing modifiers require input before automated resolution. |
| `Trick` | `name`, `description`, `available_checks`, typed `traits` set | Owned trick definition; its level/DC come from the appropriate profile. |
| `PermanentUpgrade` | Eleven permanent upgrade identifiers | Acoustics; two flooring tiers; three seating tiers; Spotlights; three tent tiers; Watermarked Tickets. |
| `OwnedUpgrade` | `purchased_on`, `price_paid` | Purchase record; the containing map key identifies the upgrade. Dates are campaign labels. |
| `ShowOutcome` | `Failure`, `Success`, `CriticalSuccess` | Completed-show result, distinct from an individual roll result. |
| `CompletedShow` | `name`, `performed_on`, `outcome`, `payout` | Minimal finished-show record, keyed by `ShowId` in the circus. |
| `StartingPrestige` | Empty marker | Identifies the rules' initial prestige point. |
| `PrestigeSource` | `StartingPrestige`, `PermanentUpgrade`, or `ShowId` | Identifies the source of an explanation entry; this is not another actor type. |
| `PrestigeContribution` | `source`, `label`, `date`, `points` | One derived row in the prestige popup. Empty date is allowed, such as for the starting point. |
| `PrestigeBreakdown` | `contributions`; calculated `total()` | A derived snapshot shared by the displayed value and popup; recalculate after source changes. |

The additional types `TrickTrait`, `TraitId`, `TraitCatalog`, `TraitSelection`, `TrickTraitDefinition`, `SignatureTrickLimits`, and `TrickValidation` are described in [Trick Traits](trick-traits.md). `TraitId` distinguishes built-in identities from custom string IDs; trick selections, prerequisites, and unlocks all use it. See [Rules Review](rules-review.md) for missing structures and ambiguities in the source rules. The structures above support the initial scope, not full rules enforcement.
