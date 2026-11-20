#pragma once

#include "Driver.h"
#include "IPointsSystem.h"
#include "IRaceResult.h"

#include <string>
#include <list>
#include <memory>

class Race : public IRaceResult
{
    std::shared_ptr<IPointsSystem const> m_pointsSystem;

    std::string m_name;
    std::list<std::shared_ptr<Driver>> m_results;

public: 
    Race(std::string const& name, std::list<std::shared_ptr<Driver>> const& drivers, std::shared_ptr<IPointsSystem const> pointsSystem);

    int position(const std::shared_ptr<Driver>& driver) const;

    int getPoints(const std::shared_ptr<Driver>& driver) const override;

    std::list<std::shared_ptr<Driver>> const& getResults() const override;

    std::string getDriverName(const std::shared_ptr<Driver>& driver) const override;

    std::string toString() const;
};
