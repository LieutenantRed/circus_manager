#include "domain/circus.h"

#include <cstdlib>
#include <iostream>
#include <string>

namespace {

void require(bool condition, const char* message) {
    if (!condition) {
        std::cerr << message << '\n';
        std::exit(EXIT_FAILURE);
    }
}

} // namespace

void run_trick_trait_tests();

int main() {
    using namespace circus;

    Circus circus;
    require(calculate_prestige(circus).total() == 1, "A new circus starts at prestige 1");

    circus.permanent_upgrades.emplace(PermanentUpgrade::Spotlights, OwnedUpgrade{});
    circus.permanent_upgrades.emplace(PermanentUpgrade::Spotlights, OwnedUpgrade{});
    circus.permanent_upgrades.emplace(PermanentUpgrade::WatermarkedTickets, OwnedUpgrade{});
    circus.permanent_upgrades.emplace(PermanentUpgrade::HugeTent, OwnedUpgrade{});
    require(calculate_prestige(circus).total() == 2,
            "Only Spotlights add prestige, once; payout modifiers do not");

    circus.show_history.emplace("show-1", CompletedShow{"First show", "Day 7", ShowOutcome::Failure, {}});
    circus.show_history.emplace("show-2", CompletedShow{"Second show", "Day 14", ShowOutcome::Success, {}});
    circus.show_history.emplace("show-3", CompletedShow{"Third show", "Day 21", ShowOutcome::CriticalSuccess, {}});
    const auto breakdown = calculate_prestige(circus);
    require(breakdown.total() == 9, "Prestige includes +1/+2/+4 from completed shows");
    require(breakdown.contributions.size() == 5, "Every award has an explanation row");
    require(std::holds_alternative<StartingPrestige>(breakdown.contributions.front().source),
            "Starting prestige is also explained");
    for (const auto& row : breakdown.contributions) {
        if (const auto* id = std::get_if<ShowId>(&row.source)) {
            const auto& show = circus.show_history.at(*id);
            require(row.label == show.name && row.date == show.performed_on,
                    "Show contributions retain their source and display context");
        }
    }

    circus.show_history.at("show-1").outcome = ShowOutcome::Success;
    require(calculate_prestige(circus).total() == 10,
            "Correcting a source recalculates prestige without a stale stored total");
    require(breakdown.total() == 9, "An existing breakdown is a consistent snapshot");
    require(calculate_prestige(circus).total() == 10,
            "Repeated calculations never award points again");

    run_trick_trait_tests();
    std::cout << "Circus and trick trait tests passed\n";
}
