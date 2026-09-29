#include "circus.h"

namespace circus {
namespace {

int show_prestige(ShowOutcome outcome) {
    switch (outcome) {
    case ShowOutcome::Failure:
        return 1;
    case ShowOutcome::Success:
        return 2;
    case ShowOutcome::CriticalSuccess:
        return 4;
    }
    return 0;
}

} // namespace

std::int64_t PrestigeBreakdown::total() const {
    std::int64_t result = 0;
    for (const auto& contribution : contributions) {
        result += contribution.points;
    }
    return result;
}

PrestigeBreakdown calculate_prestige(const Circus& circus) {
    PrestigeBreakdown result;
    result.contributions.push_back({StartingPrestige{}, "Starting prestige", "", 1});

    const auto spotlights = circus.permanent_upgrades.find(PermanentUpgrade::Spotlights);
    if (spotlights != circus.permanent_upgrades.end()) {
        result.contributions.push_back({PermanentUpgrade::Spotlights, "Spotlights",
                                       spotlights->second.purchased_on, 1});
    }

    for (const auto& [id, show] : circus.show_history) {
        result.contributions.push_back({id, show.name, show.performed_on,
                                       show_prestige(show.outcome)});
    }

    // Watermarked Tickets and Scalpers affect payout calculations, not prestige.
    return result;
}

} // namespace circus
