#include "trick_traits.h"

#include "circus.h"

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace circus {

const std::array<TrickTraitDefinition, 20>& trick_trait_definitions() {
    using T = TrickTrait;
    using S = TraitSelection;
    static const std::array<TrickTraitDefinition, 20> definitions{{
        {T::Circus, "Circus", S::Automatic, "",
         "Every Perform a Trick action has this trait.", {}},
        {T::Aerial, "Aerial", S::Selectable, "Acrobatics",
         "Flight using magic or physical means; +1 circumstance to Acrobatics checks.", {}},
        {T::Air, "Air", S::Selectable, "Survival",
         "Manipulates mist, wind, or atmospheric props; +1 circumstance to Survival checks.", {}},
        {T::Alchemical, "Alchemical", S::Selectable, "",
         "May consume one alchemical item for a +1 circumstance bonus to the trick check.", {}},
        {T::Agile, "Agile", S::Selectable, "",
         "Repeat-check penalties become -4 and -8 instead of -5 and -10.", {}},
        {T::Animal, "Animal", S::Selectable, "Nature",
         "Uses trained animals; +1 circumstance to Nature checks.", {}},
        {T::Audience, "Audience", S::Selectable, "Society",
         "Involves the audience; +1 circumstance to Society checks.", {}},
        {T::Beast, "Beast", S::Selectable, "Arcana",
         "Uses intelligent beasts; +1 circumstance to Arcana checks.", {}},
        {T::Dance, "Dance", S::Selectable, "",
         "Costar circumstance bonuses from multiple performers can stack.", {}},
        {T::Earth, "Earth", S::Selectable, "Occultism",
         "Uses earth, mud, or stone; +1 circumstance to Occultism checks.", {}},
        {T::Emotion, "Emotion", S::Selectable, "",
         "On success or critical success, may reduce generated Excitement and/or Anticipation to zero.",
         {T::Alchemical, T::Magical}},
        {T::Fire, "Fire", S::Selectable, "Intimidation",
         "Uses fire, smoke, or pyrotechnics; +1 circumstance to Intimidation checks.", {}},
        {T::Injury, "Injury", S::Compulsory, "",
         "Required for PC tricks offering a save. Any critical failure risks injury: flat DC 15. "
         "Injury ends performing this show; another DC 15 recovery check may cost the next show only.", {}},
        {T::Magical, "Magical", S::Selectable, "",
         "May spend a spell slot; on success or critical success, add Excitement equal to its level.", {}},
        {T::Musical, "Musical", S::Selectable, "Performance",
         "Uses music or sound; +1 circumstance to Performance checks.", {}},
        {T::Plant, "Plant", S::Selectable, "Nature",
         "Uses plants or plant-affecting magic; +1 circumstance to Nature checks.", {}},
        {T::Prop, "Prop", S::Selectable, "Crafting",
         "Uses physical props or a stage setup; +1 circumstance to Crafting checks.", {}},
        {T::Team, "Team", S::Compulsory, "",
         "Applies when a PC accepts Costar assistance.", {}},
        {T::Time, "Time", S::Selectable, "",
         "Allows a fourth trick attempt with the third attempt's penalty; action-budget ruling pending.", {}},
        {T::Water, "Water", S::Selectable, "Athletics",
         "Uses water; +1 circumstance to Athletics checks.", {}},
    }};
    return definitions;
}

const TrickTraitDefinition& trick_trait_definition(TrickTrait trait) {
    for (const auto& definition : trick_trait_definitions()) {
        if (definition.id == TraitId{trait}) {
            return definition;
        }
    }
    throw std::invalid_argument("Unknown trick trait");
}

const TrickTraitDefinition* TraitCatalog::find(const TraitId& id) const {
    if (std::holds_alternative<TrickTrait>(id)) {
        for (const auto& definition : trick_trait_definitions()) {
            if (definition.id == id) {
                return &definition;
            }
        }
        return nullptr;
    }
    const auto found = custom_definitions_.find(id);
    return found == custom_definitions_.end() ? nullptr : &found->second;
}

std::vector<TrickTraitDefinition> TraitCatalog::definitions() const {
    const auto& defaults = trick_trait_definitions();
    std::vector<TrickTraitDefinition> result(defaults.begin(), defaults.end());
    for (const auto& entry : custom_definitions_) {
        result.push_back(entry.second);
    }
    return result;
}

TrickValidation TraitCatalog::add_custom(TrickTraitDefinition definition) {
    TrickValidation result;
    const auto blank = [](const std::string& value) {
        return value.find_first_not_of(" \t\r\n") == std::string::npos;
    };
    const auto* id = std::get_if<std::string>(&definition.id);
    if (!id || blank(*id)) {
        result.errors.push_back("A custom trait needs a nonempty custom ID; built-in traits cannot be replaced.");
    }
    if (find(definition.id)) {
        result.errors.push_back("This trait ID already exists.");
    }
    if (blank(definition.name) || blank(definition.rules_summary)) {
        result.errors.push_back("A custom trait needs a name and a rule description.");
    }
    if (definition.selection != TraitSelection::Selectable) {
        result.errors.push_back("Custom traits must be selectable; automatic triggers are not implemented.");
    }
    for (const auto& required : definition.requires_any) {
        const auto* prerequisite = find(required);
        if (required == definition.id || !prerequisite ||
            prerequisite->selection != TraitSelection::Selectable) {
            result.errors.push_back("Prerequisites must reference existing selectable traits other than this trait.");
        }
    }
    if (result.is_valid()) {
        // Copy the key before moving the definition: argument evaluation order is unspecified.
        const auto key = definition.id;
        custom_definitions_.emplace(key, std::move(definition));
    }
    return result;
}

SignatureTrickLimits signature_trick_limits(int level) {
    if (level < 1 || level > 20) {
        throw std::invalid_argument("PC trick progression requires a level from 1 to 20");
    }
    return {level >= 16 ? 3u : level >= 4 ? 2u : 1u,
            level >= 20 ? 4u : level >= 12 ? 3u : level >= 8 ? 2u : 1u};
}

std::set<TraitId> available_trick_traits(const Circus& circus) {
    std::set<TraitId> result;
    const auto include_selectable = [&result, &circus](const std::set<TraitId>& traits) {
        for (const auto& trait : traits) {
            const auto* definition = circus.trait_catalog.find(trait);
            if (definition && definition->selection == TraitSelection::Selectable) {
                result.insert(trait);
            }
        }
    };
    include_selectable(circus.unlocked_traits);
    for (const auto& [id, actor] : circus.actors) {
        (void)id;
        if (const auto* npc = std::get_if<NpcPerformer>(&actor.profile)) {
            include_selectable(npc->trick.traits);
        }
    }
    return result;
}

TrickValidation validate_signature_trick(
    const PlayerCharacter& pc, const Trick& trick, const std::set<TraitId>& access,
    const TraitCatalog& catalog) {
    TrickValidation result;
    if (pc.level < 1 || pc.level > 20) {
        result.errors.push_back("Character level must be between 1 and 20.");
        return result;
    }
    const auto limits = signature_trick_limits(pc.level);
    if (trick.available_checks.empty() || trick.available_checks.size() > limits.checks) {
        result.errors.push_back("Choose between 1 and " + std::to_string(limits.checks) + " checks.");
    }
    std::set<CheckId> seen_checks;
    for (const auto& id : trick.available_checks) {
        if (!seen_checks.insert(id).second) {
            result.errors.push_back("Duplicate check: " + id);
        }
        if (pc.checks.find(id) == pc.checks.end()) {
            result.errors.push_back("Unknown character check: " + id);
        }
    }

    std::size_t selected_count = 0;
    for (const auto& trait : trick.traits) {
        const auto* found = catalog.find(trait);
        if (!found) {
            result.errors.push_back("Unknown trick trait.");
            continue;
        }
        const auto& definition = *found;
        const std::string name(definition.name);
        if (definition.selection != TraitSelection::Selectable) {
            result.errors.push_back(name + " is derived automatically, not selected in the PC editor.");
            continue;
        }
        ++selected_count;
        if (access.count(trait) == 0) {
            result.errors.push_back(name + " has not been unlocked by the circus.");
        }
        if (!definition.requires_any.empty() &&
            std::none_of(definition.requires_any.begin(), definition.requires_any.end(),
                         [&trick](const TraitId& required) { return trick.traits.count(required) != 0; })) {
            std::string choices;
            for (const auto& required : definition.requires_any) {
                const auto* prerequisite = catalog.find(required);
                if (!choices.empty()) {
                    choices += " or ";
                }
                choices += prerequisite ? prerequisite->name : "an unknown trait";
            }
            result.errors.push_back(name + " requires " + choices + " on the same trick.");
        }
    }
    if (selected_count > limits.traits) {
        result.errors.push_back("This level allows at most " + std::to_string(limits.traits) + " selected traits.");
    }
    return result;
}

std::set<TraitId> effective_signature_traits(
    const PlayerCharacter& pc, const Trick& trick, bool accepts_costar) {
    auto result = trick.traits;
    result.insert(TrickTrait::Circus);
    for (const auto& id : trick.available_checks) {
        const auto check = pc.checks.find(id);
        if (check != pc.checks.end() && check->second.kind == CheckKind::SavingThrow) {
            result.insert(TrickTrait::Injury);
        }
    }
    if (accepts_costar) {
        result.insert(TrickTrait::Team);
    }
    return result;
}

} // namespace circus
