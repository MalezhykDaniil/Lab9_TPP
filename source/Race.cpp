#include "../include/Race.h"

#include <stdexcept>
#include <algorithm>
#include <memory>
#include <unordered_set>

Race::Race(std::string const& name, std::list<std::shared_ptr<Driver>> const& drivers, std::shared_ptr<IPointsSystem const> pointsSystem) : m_name(name), m_results(drivers), m_pointsSystem(pointsSystem)
{
    if (m_pointsSystem == nullptr) {
        throw std::invalid_argument("Points system cannot be null");
    }

    if (m_results.empty()) {
        throw std::invalid_argument("Race must have at least one driver");
	}

    std::unordered_set<Driver> uniqueDrivers;

    
    for (const std::shared_ptr<Driver>& driver : m_results)
    {
        if (driver == nullptr) {
            throw std::invalid_argument("Driver cannot be null");
		}

        auto result = uniqueDrivers.insert(*driver);

        if (!result.second) {
            throw std::invalid_argument("Duplicate drivers are not allowed");
        }

    }

}

int Race::position(const std::shared_ptr<Driver>& driver) const
{
    int count = 1;

    if (driver == nullptr) {
        throw std::invalid_argument("Driver cannot be null");
	}

    auto found = std::find_if(m_results.begin(), m_results.end(), [&](const std::shared_ptr<Driver>& current) {
        return *current == *driver;
    });
	if (found == m_results.end()) {
        throw std::invalid_argument("Driver not found in race");
	}
    
    for (auto it = m_results.begin(); it != found; ++it)
    {
        ++count;
    }
    return count;
}

int Race::getPoints(const std::shared_ptr<Driver>& driver) const
{
    return m_pointsSystem->pointsForPosition(position(driver));
}

std::list<std::shared_ptr<Driver>> const& Race::getResults() const
{
    return m_results;
}

std::string Race::getDriverName(const std::shared_ptr<Driver>& driver) const
{
    if (driver == nullptr) {
        throw std::invalid_argument("Driver cannot be null");
    }

    auto found = std::find_if(m_results.begin(), m_results.end(), [&](const std::shared_ptr<Driver>& current) {
        return *current == *driver;
    });

    if (found == m_results.end()) {
        throw std::invalid_argument("Driver not found in race");
    }

    return (*found)->displayName();
}

std::string Race::toString() const
{
    return m_name;
}
