#pragma once

#include <string>
#include <functional>

class Driver
{
    std::string m_name;
    std::string m_country;

public:
    Driver(std::string const name, std::string const country);

    std::string getName() const;

    std::string getCountry() const;

    bool operator==(Driver const& other) const;

    virtual std::string displayName() const;

    virtual ~Driver() = default;
};

namespace std
{
    template <>
    struct hash<Driver>
    {
        std::size_t operator()(Driver const& driver) const
        {
            std::hash< std::string > const 
                hash;
            return hash( driver.getName() ) * 31 + hash( driver.getCountry() );
        }
    };
}

struct DriverComparator
{
    bool operator()(Driver const& lhs, Driver const& rhs) const
    {
        if (lhs.getName() != rhs.getName())
        {
            return lhs.getName() < rhs.getName();
        }

        return lhs.getCountry() < rhs.getCountry();
    }
};