#pragma once

#include "Driver.h"
#include "IPointsSystem.h"

#include <string>
#include <list>
#include <memory>

class Race
{
    std::shared_ptr<IPointsSystem const> m_pointsSystem;

    std::string m_name;
    std::list<std::shared_ptr<Driver>> m_results;

public: 
    Race(std::string const& name, std::list<std::shared_ptr<Driver>> const& drivers, std::shared_ptr<IPointsSystem const> pointsSystem);

    int position(const std::shared_ptr<Driver>& driver) const;

    int getPoints(const std::shared_ptr<Driver>& driver) const;

    std::list<std::shared_ptr<Driver>> const& getResults() const;

    std::string getDriverName(const std::shared_ptr<Driver>& driver) const;

    std::string toString() const;
};
