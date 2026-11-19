#pragma once

#include <list>
#include <map>
#include <vector>

#include "Race.h"

class Leaderboard
{
    std::list<Race> m_races;

public:
    Leaderboard(std::list<Race> const& races);

    std::map<Driver, int, DriverComparator> driverResults() const;

    std::vector<std::pair<Driver, int>> driverRankings() const;
};
