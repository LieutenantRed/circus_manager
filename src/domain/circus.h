#pragma once

#include "trick_traits.h"

#include <cstdint>
#include <map>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace circus {

// Stable IDs are assigned by the application, not derived from display names.
using ActorId = std::string;
using ShowId = std::string;
using CheckId = std::string;

// Store money exactly in the smallest currency unit, never as floating point.
struct Money {
    std::int64_t copper = 0;
};

enum class CheckKind { Skill, SavingThrow, Attack };

struct Check {
    std::string name;
    CheckKind kind = CheckKind::Skill;
    // Unset until entered; do not silently treat missing character data as +0.
    std::optional<int> modifier;
};

struct Trick {
    std::string name;
    std::string description;
    std::vector<CheckId> available_checks;
    // PC definitions store selected traits; NPC definitions may list compulsory traits.
    std::set<TraitId> traits;
};

struct PlayerCharacter {
    int level = 1;
    std::map<CheckId, Check> checks;
    // A backstage-only character need not have designed a signature trick.
    std::optional<Trick> signature_trick;
};

struct NpcPerformer {
    int trick_level = 1;
    std::optional<int> trick_dc; // Must be supplied before this NPC can perform.
    std::map<CheckId, Check> checks;
    Trick trick;
    std::string requirements;
};

struct Actor {
    std::string name;
    std::variant<PlayerCharacter, NpcPerformer> profile;
};

enum class PermanentUpgrade {
    Acoustics,
    SafetyNet,
    PaddedFloors,
    Bleachers,
    AssignedSeats,
    UpholsteredSeats,
    Spotlights,
    BigTent,
    HugeTent,
    MassiveTent,
    WatermarkedTickets,
};

struct OwnedUpgrade {
    std::string purchased_on; // Campaign date label, not the computer clock.
    Money price_paid;
};

enum class ShowOutcome { Failure, Success, CriticalSuccess };

// Only completed shows belong in history. Live show state will be separate.
struct CompletedShow {
    std::string name;
    std::string performed_on;
    ShowOutcome outcome = ShowOutcome::Failure;
    Money payout;
};

struct Circus {
    std::string name;
    std::map<ActorId, Actor> actors;
    // Each permanent upgrade can be owned only once.
    std::map<PermanentUpgrade, OwnedUpgrade> permanent_upgrades;
    std::map<ShowId, CompletedShow> show_history;
    Money balance;
    TraitCatalog trait_catalog;
    // Starting access from p. 64. Retain additional unlocks here when hiring NPCs.
    std::set<TraitId> unlocked_traits{
        TrickTrait::Agile, TrickTrait::Animal, TrickTrait::Fire, TrickTrait::Water};
    // Prestige is deliberately absent: derive it from the records above.
};

struct StartingPrestige {};

// Typed references let the UI identify the source of each contribution.
using PrestigeSource = std::variant<StartingPrestige, PermanentUpgrade, ShowId>;

struct PrestigeContribution {
    PrestigeSource source;
    std::string label;
    std::string date;
    int points = 0;
};

struct PrestigeBreakdown {
    std::vector<PrestigeContribution> contributions;

    [[nodiscard]] std::int64_t total() const;
};

// Both the displayed value and its explanation should use this result.
[[nodiscard]] PrestigeBreakdown calculate_prestige(const Circus& circus);

} // namespace circus
