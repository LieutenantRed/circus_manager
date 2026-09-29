# Trick Traits

Sources: `Circus rules.pdf`, printed pages 63-65. The catalog and signature-trick helpers are in `src/domain/trick_traits.h` and `.cpp`.

## Catalog

There are 19 named trick traits plus the universal Circus action trait. `TrickTrait` identifies these built-in rules. `TraitId` refers either to a built-in enum value or a stable custom string ID. `TrickTraitDefinition` stores that ID, display name, selection category, associated bonus skill, rule summary, and alternative prerequisites. Definition strings are owned, so editor input does not need to stay in memory.

For the skills below, the trait grants a **+1 circumstance bonus** when performing the trick using that skill. These are metadata for later roll resolution; storing the trait does not yet apply its effects.

| Trait | Bonus skill | Additional rule or meaning |
| --- | --- | --- |
| Aerial | Acrobatics | Magical or physical flight. |
| Air | Survival | Atmospheric effects such as mist or wind. |
| Alchemical | None | May consume one alchemical item for +1 circumstance on the check. |
| Agile | None | Second/third attempt penalties become -4/-8. |
| Animal | Nature | Trained animals. |
| Audience | Society | Audience participation. |
| Beast | Arcana | Intelligent beasts. |
| Dance | None | Circumstance bonuses from multiple Costar helpers can stack. |
| Earth | Occultism | Earth, mud, or stone. |
| Emotion | None | Requires Alchemical or Magical on the same trick. Successful checks may generate less Excitement and/or Anticipation, down to zero. |
| Fire | Intimidation | Fire, smoke, or pyrotechnics. |
| Injury | None | Compulsory for a PC trick with a saving-throw check. Critical failure risks injury. |
| Magical | None | May spend a spell slot; success adds Excitement equal to its level. |
| Musical | Performance | Music or sound effects. |
| Plant | Nature | Plants or magic affecting them. |
| Prop | Crafting | Physical props or stage setup. |
| Team | None | Compulsory when a PC accepts Costar assistance. |
| Time | None | Permits a fourth attempt at the third attempt's penalty; action-budget interpretation remains open. |
| Water | Athletics | Water-based performance. |
| Circus | None | Automatically applies to every Perform a Trick action. |

## PC Progression

`signature_trick_limits(level)` returns the base limits and rejects levels outside 1-20.

| PC level | Maximum check choices | Maximum selected traits |
| --- | --- | --- |
| 1-3 | 1 | 1 |
| 4-7 | 2 | 1 |
| 8-11 | 2 | 2 |
| 12-15 | 2 | 3 |
| 16-19 | 3 | 3 |
| 20 | 3 | 4 |

More slots permit additional choices; leveling does not select traits automatically. The Advanced Circus Trick feat is referenced but not described in this PDF; its additional allowances are not implemented. Redesign timing remains a separate check: leveling up or six consecutive downtime days under the PDF's redesign rules.

## Definitions, Access, and Validation

`Trick.traits` is a set of `TraitId`, preventing duplicate selection and supporting built-in and custom traits together. PC definitions store **selectable traits only**. NPC definitions can also list compulsory traits and are not subject to the PC level limits.

`Circus.unlocked_traits` starts with Agile, Animal, Fire, and Water. `available_trick_traits(circus)` combines recorded unlocks with selectable traits on current NPC tricks. PC tricks do not grant access. When recruitment is implemented, it must retain gained access in `unlocked_traits`; the helper itself is read-only and does not record hiring history.

`validate_signature_trick(pc, draft, access, circus.trait_catalog)` returns a `TrickValidation` containing readable errors. It checks level, check count and ownership, duplicate check IDs, trait limits, trait access, and prerequisites from the catalog, including Emotion's. It rejects manual selection of Circus, Injury, and Team. Run it before assigning a draft to `pc.signature_trick`; it does not mutate the character or authorize a redesign. Missing check modifiers can remain unset during design and must be supplied for later roll resolution.

`effective_signature_traits(pc, trick, accepts_costar)` derives the tags used during play from a valid definition:

- Always add Circus.
- Add Injury if any check offered by this trick is a saving throw, even when another check is chosen for an attempt.
- Add Team when Costar assistance is accepted.

Derived tags consume no selection slots and do not change the saved definition. `TraitSelection` distinguishes automatic, selectable, and compulsory tags. `SignatureTrickLimits` stores the two capacities; `TrickValidation.is_valid()` reports whether its error list is empty.

## GM-Created Traits

The GM must be able to add custom trait definitions through the future app interface. The domain API is implemented; the editor and save/load integration remain deferred with the rest of the UI and persistence work.

Each circus has a `TraitCatalog` containing the built-in defaults and its own custom definitions. `definitions()` lists both; `find(id)` returns a definition or null. `add_custom(definition)` returns validation errors and adds nothing on failure. Custom IDs are stable strings, independent of display names; a prefix such as `custom:` is a naming convention, not a rule requirement.

A new custom definition needs a unique nonblank ID, a name, and a rule description. It must be selectable. Optional prerequisites can reference existing selectable built-in or custom traits; at least one must appear on the same trick. Unknown references and self-references are rejected. Built-in definitions cannot be replaced, and duplicate IDs cannot overwrite custom entries.

For example, register an **Illusions** trait with ID `custom:illusions` and Magical as its prerequisite. An NPC can have Illusions on their trick. Once that NPC grants access, an eligible PC can select Illusions alongside Magical, using two normal trait slots.

Defining a trait does not grant PC access automatically. Access comes from NPC tricks or an explicit GM entry in `Circus.unlocked_traits`. Custom traits count toward normal PC limits. They are campaign additions, not additional rules claimed to be in the PDF.

The current metadata supports a rule description, an optional skill associated with a +1 circumstance bonus, and alternative trait prerequisites. Arbitrary numerical effects, scripts, or custom compulsory triggers are not implemented. Descriptive text alone is not executable game logic.

Runtime bonuses, resource spending, injury/recovery, and action changes are still pending for all traits. See [Rules Review](rules-review.md) for remaining source ambiguities.
