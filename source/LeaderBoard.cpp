#include "../include/LeaderBoard.h"

#include <algorithm>
#include <vector>
#include <stdexcept>

Leaderboard::Leaderboard(std::vector<std::shared_ptr<IRaceResult const>> races)
    : m_races(std::move(races))
{
    for (const auto& race : m_races)
    {
        if (race == nullptr)
        {
            throw std::invalid_argument("Race cannot be null");
        }
    }
}

std::map<Driver, int, DriverComparator> Leaderboard::driverResults() const
{
    std::map<Driver, int, DriverComparator> results;
    for (const std::shared_ptr<IRaceResult const>& race : m_races)
    {
        for (const std::shared_ptr<Driver>& driver : race->getResults())
        {
            int points = race->getPoints(driver);
            
            auto result = results.try_emplace(*driver, points);
            auto& it = result.first;
            bool inserted = result.second;
            
            if (!inserted)
            {
                it->second += points;
            }
        }
    }
    return results;
}

std::vector<std::pair<Driver, int>> Leaderboard::driverRankings() const
{
    std::map<Driver, int, DriverComparator> results = driverResults();

    std::vector<std::pair<Driver, int>> resultsList(results.begin(), results.end());

    std::sort(resultsList.begin(), resultsList.end(),
        [](const std::pair<Driver, int>& a, const std::pair<Driver, int>& b)
        {
            if (a.second != b.second)
                return a.second > b.second;
            DriverComparator comp;
            return comp(a.first, b.first);
        });

    return resultsList;
}
