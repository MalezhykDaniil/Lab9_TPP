#pragma once

#include <map>
#include <vector>

#include "IRaceResult.h"

class Leaderboard
{
    std::vector<std::shared_ptr<IRaceResult const>> m_races;

public:
    explicit Leaderboard(std::vector<std::shared_ptr<IRaceResult const>> races);

    std::map<Driver, int, DriverComparator> driverResults() const;

    std::vector<std::pair<Driver, int>> driverRankings() const;
};
