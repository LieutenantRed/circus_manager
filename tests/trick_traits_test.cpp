#include "domain/circus.h"

#include <cstdlib>
#include <iostream>
#include <set>
#include <stdexcept>

namespace {

void require(bool condition, const char* message) {
    if (!condition) {
        std::cerr << message << '\n';
        std::exit(EXIT_FAILURE);
    }
}

} // namespace

void run_trick_trait_tests() {
    using namespace circus;
    using T = TrickTrait;

    std::set<TraitId> catalog_ids;
    for (const auto& definition : trick_trait_definitions()) {
        require(catalog_ids.insert(definition.id).second, "Trait IDs must be unique");
        require(!definition.name.empty() && !definition.rules_summary.empty(),
                "Every trait must have a readable definition");
    }
    require(catalog_ids.size() == 20, "Catalog includes 19 special traits and Circus");

    for (int level = 1; level <= 20; ++level) {
        const auto limits = signature_trick_limits(level);
        const std::size_t checks = level < 4 ? 1 : level < 16 ? 2 : 3;
        const std::size_t traits = level < 8 ? 1 : level < 12 ? 2 : level < 20 ? 3 : 4;
        require(limits.checks == checks && limits.traits == traits,
                "Every level must follow Table 2, including progression boundaries");
    }
    for (int level : {0, 21}) {
        bool rejected = false;
        try {
            (void)signature_trick_limits(level);
        } catch (const std::invalid_argument&) {
            rejected = true;
        }
        require(rejected, "Unsupported character levels must not silently receive limits");
    }

    Circus circus;
    auto access = available_trick_traits(circus);
    require(access == std::set<TraitId>{T::Agile, T::Animal, T::Fire, T::Water},
            "Starting trait access matches the starting troupe");
    PlayerCharacter pc;
    pc.checks.emplace("athletics", Check{"Athletics", CheckKind::Skill, 7});
    pc.checks.emplace("fortitude", Check{"Fortitude", CheckKind::SavingThrow, 8});
    pc.checks.emplace("acrobatics", Check{"Acrobatics", CheckKind::Skill, 6});
    Trick draft{"Water escape", "", {"athletics"}, {T::Water}};
    require(validate_signature_trick(pc, draft, access, circus.trait_catalog).is_valid(), "A basic level-1 trick is valid");
    draft.traits.insert(T::Agile);
    require(!validate_signature_trick(pc, draft, access, circus.trait_catalog).is_valid(), "Level 1 cannot select two traits");
    pc.level = 8;
    require(validate_signature_trick(pc, draft, access, circus.trait_catalog).is_valid(), "Level 8 unlocks the second trait slot");
    draft.traits = {T::Agile};
    draft.available_checks.push_back("fortitude");
    pc.level = 3;
    require(!validate_signature_trick(pc, draft, access, circus.trait_catalog).is_valid(), "Level 3 cannot choose a second check");
    pc.level = 4;
    require(validate_signature_trick(pc, draft, access, circus.trait_catalog).is_valid(), "Level 4 may choose two checks");
    auto effective = effective_signature_traits(pc, draft, true);
    require(effective == std::set<TraitId>{T::Agile, T::Circus, T::Injury, T::Team},
            "Compulsory traits require no unlock or optional slot");
    require(draft.traits == std::set<TraitId>{T::Agile}, "Derived traits must not modify the saved definition");
    require(effective_signature_traits(pc, draft).count(T::Team) == 0,
            "Team is only active when Costar is accepted");
    draft.available_checks = {"athletics"};
    require(effective_signature_traits(pc, draft).count(T::Injury) == 0,
            "A save on the character sheet alone does not make every trick injurious");
    for (const auto trait : {T::Circus, T::Injury, T::Team}) {
        draft.traits = {trait};
        require(!validate_signature_trick(pc, draft, access, circus.trait_catalog).is_valid(),
                "Automatic/compulsory traits are not manually selectable by PCs");
    }

    pc.level = 8;
    draft.traits = {T::Emotion, T::Magical};
    require(!validate_signature_trick(pc, draft, access, circus.trait_catalog).is_valid(), "Locked traits must be rejected");
    pc.signature_trick = draft;
    circus.actors.emplace("pc", Actor{"PC", pc});
    require(available_trick_traits(circus).count(T::Magical) == 0,
            "Another PC's trick cannot unlock circus traits");
    NpcPerformer npc;
    npc.trick.traits = {T::Emotion, T::Magical, T::Alchemical, T::Time, T::Injury};
    circus.actors.emplace("npc", Actor{"Visiting magician", npc});
    access = available_trick_traits(circus);
    require(access.count(T::Time) == 1 && access.count(T::Injury) == 0,
            "NPC traits unlock selectable options without PC trait-count limits");
    require(validate_signature_trick(pc, draft, access, circus.trait_catalog).is_valid(), "Emotion works with Magical once unlocked");
    draft.traits = {T::Emotion};
    require(!validate_signature_trick(pc, draft, access, circus.trait_catalog).is_valid(), "Emotion requires a supporting trait");
    draft.traits.insert(T::Alchemical);
    require(validate_signature_trick(pc, draft, access, circus.trait_catalog).is_valid(), "Alchemical also satisfies Emotion");

    // Hiring code will retain gained access when recording a recruitment.
    circus.unlocked_traits = access;
    circus.actors.erase("npc");
    require(available_trick_traits(circus).count(T::Magical) == 1,
            "Recorded unlocks survive removing an NPC from the current roster");

    draft.traits = {T::Fire};
    draft.available_checks = {"missing"};
    require(!validate_signature_trick(pc, draft, access, circus.trait_catalog).is_valid(), "Tricks cannot reference another actor's checks");
    draft.available_checks = {"athletics", "athletics"};
    require(!validate_signature_trick(pc, draft, access, circus.trait_catalog).is_valid(), "Check choices must be distinct");
    draft.available_checks.clear();
    require(!validate_signature_trick(pc, draft, access, circus.trait_catalog).is_valid(), "A trick needs at least one check");
    draft.available_checks = {"athletics", "fortitude", "acrobatics"};
    pc.level = 15;
    require(!validate_signature_trick(pc, draft, access, circus.trait_catalog).is_valid(), "Three checks require level 16");
    pc.level = 16;
    require(validate_signature_trick(pc, draft, access, circus.trait_catalog).is_valid(), "Level 16 allows three checks");
    draft.traits = {T::Agile, T::Animal, T::Fire, T::Water};
    pc.level = 19;
    require(!validate_signature_trick(pc, draft, access, circus.trait_catalog).is_valid(), "Four traits require level 20");
    pc.level = 20;
    require(validate_signature_trick(pc, draft, access, circus.trait_catalog).is_valid(), "Level 20 allows four traits");
    draft.traits.insert(static_cast<T>(999));
    require(!validate_signature_trick(pc, draft, access, circus.trait_catalog).is_valid(), "Unknown serialized traits must be rejected");

    const TraitId illusions = std::string("custom:illusions");
    TrickTraitDefinition custom{illusions, "Illusions", TraitSelection::Selectable,
                                "", "A GM-defined spectacle using illusions.", {T::Magical}};
    require(circus.trait_catalog.add_custom(custom).is_valid(), "A GM can register a custom trait");
    custom.name = "Changed outside the catalog";
    require(circus.trait_catalog.find(illusions)->name == "Illusions",
            "Custom metadata must own its strings, independent of the editor draft");
    require(circus.trait_catalog.definitions().size() == 21, "Catalog lists defaults and custom traits");
    require(!circus.trait_catalog.add_custom(custom).is_valid(), "Duplicate IDs cannot overwrite existing definitions");
    require(available_trick_traits(circus).count(illusions) == 0,
            "Defining a trait alone does not unlock it for PCs");
    pc.level = 8;
    draft.available_checks = {"athletics"};
    draft.traits = {illusions, T::Magical};
    access = available_trick_traits(circus);
    require(!validate_signature_trick(pc, draft, access, circus.trait_catalog).is_valid(),
            "Custom traits still require access");
    npc.trick.traits.insert(illusions);
    circus.actors.emplace("custom-npc", Actor{"Illusionist", npc});
    access = available_trick_traits(circus);
    require(validate_signature_trick(pc, draft, access, circus.trait_catalog).is_valid(),
            "An NPC can unlock a custom trait with a built-in prerequisite");
    pc.level = 1;
    require(!validate_signature_trick(pc, draft, access, circus.trait_catalog).is_valid(),
            "Custom traits consume normal PC trait slots");
    pc.level = 8;
    draft.traits = {illusions};
    const auto prerequisite_error = validate_signature_trick(pc, draft, access, circus.trait_catalog);
    require(!prerequisite_error.is_valid() &&
                prerequisite_error.errors.front().find("requires Magical") != std::string::npos,
            "Prerequisite errors must describe the custom rule, not hard-code Emotion");
    const TraitId spectacle = std::string("custom:spectacle");
    require(circus.trait_catalog.add_custom({spectacle, "Spectacle", TraitSelection::Selectable,
                "", "Builds on an illusion performance.", {illusions}}).is_valid(),
            "Custom traits can refer to other custom prerequisites");
    circus.unlocked_traits.insert(spectacle);
    pc.level = 12;
    draft.traits = {illusions, spectacle, T::Magical};
    require(validate_signature_trick(pc, draft, available_trick_traits(circus), circus.trait_catalog).is_valid(),
            "Explicit GM access and custom prerequisite chains work together");
    Circus another_circus;
    require(another_circus.trait_catalog.find(illusions) == nullptr,
            "Campaign custom traits must not leak into other circuses");
    const auto saved_catalog_copy = circus.trait_catalog;
    require(saved_catalog_copy.find(spectacle)->requires_any.front() == illusions,
            "Copying a catalog retains custom IDs and definitions");

    const auto catalog_size = circus.trait_catalog.definitions().size();
    custom.id = T::Fire;
    require(!circus.trait_catalog.add_custom(custom).is_valid(), "Built-in rules cannot be overwritten");
    custom.id = std::string("custom:invalid");
    custom.requires_any = {std::string("custom:missing")};
    require(!circus.trait_catalog.add_custom(custom).is_valid(), "Unknown prerequisites must be rejected");
    custom.requires_any = {custom.id};
    require(!circus.trait_catalog.add_custom(custom).is_valid(), "A trait cannot require itself");
    custom.requires_any = {T::Team};
    require(!circus.trait_catalog.add_custom(custom).is_valid(), "Contextual tags cannot serve as design prerequisites");
    custom.requires_any.clear();
    custom.selection = TraitSelection::Automatic;
    require(!circus.trait_catalog.add_custom(custom).is_valid(), "Unsupported custom automatic triggers must be rejected");
    custom.selection = TraitSelection::Selectable;
    custom.id = std::string(" ");
    require(!circus.trait_catalog.add_custom(custom).is_valid(), "Empty custom identifiers must be rejected");
    custom.id = std::string("custom:invalid");
    custom.name.clear();
    require(!circus.trait_catalog.add_custom(custom).is_valid(), "A custom trait needs a display name");
    custom.name = "Invalid";
    custom.rules_summary.clear();
    require(!circus.trait_catalog.add_custom(custom).is_valid(), "A custom trait needs its rule description");
    require(circus.trait_catalog.definitions().size() == catalog_size,
            "Failed additions must leave the catalog unchanged");
}
