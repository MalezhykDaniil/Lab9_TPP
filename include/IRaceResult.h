#pragma once

#include <list>
#include <memory>
#include <string>

#include "Driver.h"

class IRaceResult
{
public:
    virtual ~IRaceResult() = default;

    virtual std::list<std::shared_ptr<Driver>> const& getResults() const = 0;
    
    virtual int getPoints(const std::shared_ptr<Driver>& driver) const = 0;
    
    virtual std::string getDriverName(const std::shared_ptr<Driver>& driver) const = 0;
};