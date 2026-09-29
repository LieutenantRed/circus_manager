#pragma once

#include <array>
#include <cstddef>
#include <map>
#include <set>
#include <string>
#include <variant>
#include <vector>

namespace circus {

struct Circus;
struct PlayerCharacter;
struct Trick;

enum class TrickTrait {
    Circus, Aerial, Air, Alchemical, Agile, Animal, Audience, Beast, Dance,
    Earth, Emotion, Fire, Injury, Magical, Musical, Plant, Prop, Team, Time, Water,
};

enum class TraitSelection { Automatic, Selectable, Compulsory };

// Built-in identity is distinct from custom IDs, which must survive display-name edits.
using TraitId = std::variant<TrickTrait, std::string>;

struct TrickTraitDefinition {
    TraitId id;
    std::string name;
    TraitSelection selection;
    // Nonempty skill names identify a +1 circumstance bonus with that skill.
    std::string bonus_skill;
    std::string rules_summary;
    // At least one of these traits must also be present; empty means no prerequisite.
    std::vector<TraitId> requires_any;
};

struct SignatureTrickLimits {
    std::size_t checks;
    std::size_t traits; // Selectable traits only, excluding automatic/compulsory traits.
};

struct TrickValidation {
    std::vector<std::string> errors;
    [[nodiscard]] bool is_valid() const { return errors.empty(); }
};

// The PDF definitions are immutable defaults; custom definitions belong to a campaign.
class TraitCatalog {
public:
    [[nodiscard]] const TrickTraitDefinition* find(const TraitId& id) const;
    [[nodiscard]] std::vector<TrickTraitDefinition> definitions() const;
    // Adds a selectable custom trait; failure leaves the catalog unchanged.
    [[nodiscard]] TrickValidation add_custom(TrickTraitDefinition definition);

private:
    std::map<TraitId, TrickTraitDefinition> custom_definitions_;
};

[[nodiscard]] const std::array<TrickTraitDefinition, 20>& trick_trait_definitions();
// Throws std::invalid_argument for an unknown enum value.
[[nodiscard]] const TrickTraitDefinition& trick_trait_definition(TrickTrait trait);
// Base progression, levels 1-20. External feat benefits are not implemented.
[[nodiscard]] SignatureTrickLimits signature_trick_limits(int level);
[[nodiscard]] std::set<TraitId> available_trick_traits(const Circus& circus);
// Validates a draft, without changing the PC or authorizing a downtime redesign.
[[nodiscard]] TrickValidation validate_signature_trick(
    const PlayerCharacter& pc, const Trick& trick, const std::set<TraitId>& access,
    const TraitCatalog& catalog);
// Call with a valid draft/definition; Costar is contextual, not saved on the trick.
[[nodiscard]] std::set<TraitId> effective_signature_traits(
    const PlayerCharacter& pc, const Trick& trick, bool accepts_costar = false);

} // namespace circus
