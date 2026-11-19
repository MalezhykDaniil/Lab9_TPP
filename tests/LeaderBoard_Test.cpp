#include <gtest/gtest.h>
#include "LeaderBoard.h"
#include "PointsSystem.h"
#include "SelfDrivingCar.h"
#include "AlternativePointsSystem.h"

TEST(Leaderboard, SingleDriverGets25Points)
{
    auto driver = std::make_shared<Driver>("Alice", "USA");
	auto pointsSystem = std::make_shared<PointsSystem>();

    Race race("Race 1", { driver }, pointsSystem);
    Leaderboard leaderboard({ race });

    auto results = leaderboard.driverResults();

    EXPECT_EQ(results.at(*driver), 25);
}

TEST(Leaderboard, DistributesPointsByPosition)
{
    auto alice = std::make_shared<Driver>("Alice", "USA");
    auto bob = std::make_shared<Driver>("Bob", "UK");
    auto charlie = std::make_shared<Driver>("Charlie", "Germany");
    auto pointsSystem = std::make_shared<PointsSystem>();

    Race race("Race 1", { alice, bob, charlie }, pointsSystem);
    Leaderboard leaderboard({ race });

    auto results = leaderboard.driverResults();

    EXPECT_EQ(results.at(*alice), 25);
    EXPECT_EQ(results.at(*bob), 18);
    EXPECT_EQ(results.at(*charlie), 15);
}

TEST(Leaderboard, AccumulatesPointsAcrossRaces)
{
    auto alice = std::make_shared<Driver>("Alice", "USA");
    auto bob = std::make_shared<Driver>("Bob", "UK");
    auto pointsSystem = std::make_shared<PointsSystem>();

    Race race1("Race 1", { alice, bob }, pointsSystem);
    Race race2("Race 2", { alice, bob }, pointsSystem);

    Leaderboard leaderboard({ race1, race2 });

    auto results = leaderboard.driverResults();

    EXPECT_EQ(results.at(*alice), 50);
    EXPECT_EQ(results.at(*bob), 36);
}

TEST(Leaderboard, RanksDriversByPoints)
{
    auto alice = std::make_shared<Driver>("Alice", "USA");
    auto bob = std::make_shared<Driver>("Bob", "UK");
    auto charlie = std::make_shared<Driver>("Charlie", "Germany");
    auto pointsSystem = std::make_shared<PointsSystem>();

    Race race("Race 1", { alice, bob, charlie }, pointsSystem);
    Leaderboard leaderboard({ race });

    auto rankings = leaderboard.driverRankings();

    EXPECT_EQ(rankings[0].first.getName(), "Alice");
    EXPECT_EQ(rankings[0].second, 25);

    EXPECT_EQ(rankings[1].first.getName(), "Bob");
    EXPECT_EQ(rankings[1].second, 18);

    EXPECT_EQ(rankings[2].first.getName(), "Charlie");
    EXPECT_EQ(rankings[2].second, 15);
}

TEST(PointsSystem, PositionPoints)
{
    PointsSystem pointsSystem;

    EXPECT_EQ(pointsSystem.pointsForPosition(1), 25);
    EXPECT_EQ(pointsSystem.pointsForPosition(2), 18);
    EXPECT_EQ(pointsSystem.pointsForPosition(3), 15);
    EXPECT_EQ(pointsSystem.pointsForPosition(4), 0);
}

TEST(AlternativePointsSystem, PositionPoints)
{
    AlternativePointsSystem pointsSystem;

    EXPECT_EQ(pointsSystem.pointsForPosition(1), 30);
    EXPECT_EQ(pointsSystem.pointsForPosition(2), 20);
    EXPECT_EQ(pointsSystem.pointsForPosition(3), 10);
    EXPECT_EQ(pointsSystem.pointsForPosition(4), 0);
}

TEST(PointsSystem, InvalidPosition)
{
    PointsSystem pointsSystem;
    
    EXPECT_THROW(pointsSystem.pointsForPosition(-1), std::invalid_argument);
    EXPECT_THROW(pointsSystem.pointsForPosition(0), std::invalid_argument);
}

TEST(AlternativePointsSystem, InvalidPosition)
{
    AlternativePointsSystem pointsSystem;

    EXPECT_THROW(pointsSystem.pointsForPosition(-1), std::invalid_argument);
    EXPECT_THROW(pointsSystem.pointsForPosition(0), std::invalid_argument);
}

TEST(Race, SelfDrivingCars)
{
    auto selfDrivingCar = std::make_shared<SelfDrivingCar>("v1.0", "Company");
    auto pointsSystem = std::make_shared<PointsSystem>();

	Race race("Race 1", { selfDrivingCar }, pointsSystem);

	EXPECT_EQ(race.getDriverName(selfDrivingCar), "Self Driving Car - Company(v1.0)");
	EXPECT_EQ(race.position(selfDrivingCar), 1);
}

TEST(Race, Null)
{
    EXPECT_THROW(Race race("Race 1", {}, nullptr), std::invalid_argument);
}

TEST(Race, NullDriver)
{
    auto pointsSystem = std::make_shared<PointsSystem>();
    
    std::list<std::shared_ptr<Driver>> drivers = { nullptr };
    
    EXPECT_THROW(Race race("Race 1", drivers, pointsSystem), std::invalid_argument);
}

TEST(Race, DriverNotFound)
{
    auto alice = std::make_shared<Driver>("Alice", "USA");
    auto bob = std::make_shared<Driver>("Bob", "UK");
    auto pointsSystem = std::make_shared<PointsSystem>();
    
    Race race("Race 1", { alice }, pointsSystem);
    
    EXPECT_THROW(race.position(bob), std::invalid_argument);
    EXPECT_THROW(race.position(nullptr), std::invalid_argument);
    EXPECT_THROW(race.getPoints(bob), std::invalid_argument);
    EXPECT_THROW(race.getDriverName(bob), std::invalid_argument);
    EXPECT_THROW(race.getDriverName(nullptr), std::invalid_argument);
}

TEST(Race, EmptyDriverList)
{
    auto pointsSystem = std::make_shared<PointsSystem>();
    
    std::list<std::shared_ptr<Driver>> drivers;
    
    EXPECT_THROW(Race race("Race 1", drivers, pointsSystem), std::invalid_argument);
}

TEST(Race, AlternativePointSystem)
{
    auto alice = std::make_shared<Driver>("Alice", "USA");
    auto bob = std::make_shared<Driver>("Bob", "UK");
    auto charlie = std::make_shared<Driver>("Charlie", "Germany");
    auto alternativePointsSystem = std::make_shared<AlternativePointsSystem>();
    
    Race race("Race 1", { alice, bob, charlie }, alternativePointsSystem);
    Leaderboard leaderboard({ race });
    
    auto results = leaderboard.driverResults();
    
    EXPECT_EQ(results.at(*alice), 30);
    EXPECT_EQ(results.at(*bob), 20);
	EXPECT_EQ(results.at(*charlie), 10);
}

TEST(Race, DuplicateDrivers)
{
    auto alice = std::make_shared<Driver>("Alice", "USA");
    auto pointsSystem = std::make_shared<PointsSystem>();
    
    std::list<std::shared_ptr<Driver>> drivers = { alice, alice };
    
    EXPECT_THROW(Race race("Race 1", drivers, pointsSystem), std::invalid_argument);
}

TEST(Race, DuplicateDriverNames)
{
    auto alice1 = std::make_shared<Driver>("Alice", "USA");
    auto alice2 = std::make_shared<Driver>("Alice", "USA");
    auto pointsSystem = std::make_shared<PointsSystem>();

    std::list<std::shared_ptr<Driver>> drivers = { alice1, alice2 };

    EXPECT_THROW(Race race("Race 1", drivers, pointsSystem), std::invalid_argument);
}

TEST(Race, DuplicateDriverNamesDifferentCountries)
{
    auto aliceUSA = std::make_shared<Driver>("Alice", "USA");
    auto aliceUK = std::make_shared<Driver>("Alice", "UK");
    auto pointsSystem = std::make_shared<PointsSystem>();
    
    std::list<std::shared_ptr<Driver>> drivers = { aliceUSA, aliceUK };
    
    EXPECT_NO_THROW(Race race("Race 1", drivers, pointsSystem));
}

TEST(Race, SamePoints)
{
    auto alice = std::make_shared<Driver>("Alice", "USA");
    auto bob = std::make_shared<Driver>("Bob", "UK");
    auto pointsSystem = std::make_shared<PointsSystem>();
    
    Race race("Race 1", { alice, bob }, pointsSystem);
	Race race2("Race 2", { bob, alice }, pointsSystem);
    Leaderboard leaderboard({ race, race2 });
    
    auto rankings = leaderboard.driverRankings();
    
    EXPECT_EQ(rankings.size(), 2);
    EXPECT_EQ(rankings[0].second, rankings[1].second);
    EXPECT_EQ(rankings[0].first.getName(), "Alice");
    EXPECT_EQ(rankings[1].first.getName(), "Bob");
}

TEST(Leaderboard, SameNamesDifferentCountries)
{
    auto aliceUSA = std::make_shared<Driver>("Alice", "USA");
    auto aliceUK = std::make_shared<Driver>("Alice", "UK");
    auto pointsSystem = std::make_shared<PointsSystem>();

    Race race("Race 1", { aliceUSA, aliceUK }, pointsSystem);
    Leaderboard leaderboard({ race });

    auto results = leaderboard.driverResults();
    auto rankings = leaderboard.driverRankings();

    EXPECT_EQ(results.size(), 2);
    EXPECT_EQ(results.at(*aliceUSA), 25);
    EXPECT_EQ(results.at(*aliceUK), 18);

    EXPECT_EQ(rankings.size(), 2);
    EXPECT_EQ(rankings[0].first.getCountry(), "USA");
    EXPECT_EQ(rankings[1].first.getCountry(), "UK");
}

TEST(Leaderboard, EmptyRaces)
{
    Leaderboard leaderboard({});

    EXPECT_TRUE(leaderboard.driverResults().empty());
    EXPECT_TRUE(leaderboard.driverRankings().empty());
}

TEST(Leaderboard, CopyConstructor)
{
    auto alice = std::make_shared<Driver>("Alice", "USA");
    auto pointsSystem = std::make_shared<PointsSystem>();

    Race race("Race 1", { alice }, pointsSystem);
    Leaderboard original({ race });

    Leaderboard copy(original);

    EXPECT_EQ(copy.driverResults().at(*alice), 25);
    EXPECT_EQ(copy.driverRankings().size(), 1);
}

TEST(Race, CopyConstructor)
{
    auto alice = std::make_shared<Driver>("Alice", "USA");
    auto pointsSystem = std::make_shared<PointsSystem>();

    Race original("Race 1", { alice }, pointsSystem);
    Race copy(original);

    EXPECT_EQ(copy.position(alice), 1);
    EXPECT_EQ(copy.getPoints(alice), 25);
    EXPECT_EQ(copy.getDriverName(alice), "Alice");
}

TEST(Leaderboard, WorksAfterOriginalRaceDestroyed)
{
    auto alice = std::make_shared<Driver>("Alice", "USA");
    auto pointsSystem = std::make_shared<PointsSystem>();

    std::unique_ptr<Leaderboard> leaderboard;

    {
        Race race("Race 1", { alice }, pointsSystem);
        leaderboard = std::make_unique<Leaderboard>(
            std::list<Race>{ race }
        );
    }

    EXPECT_EQ(leaderboard->driverResults().at(*alice), 25);
    EXPECT_EQ(leaderboard->driverRankings().size(), 1);
}

TEST(Race, DriverLifeTime)
{
    auto alice = std::make_shared<Driver>("Alice", "USA");
    auto pointsSystem = std::make_shared<PointsSystem>();
    Race race("Race 1", { alice }, pointsSystem);

	std::weak_ptr<Driver> weakAlice = alice;

    alice.reset();

	EXPECT_FALSE(weakAlice.expired());

    auto lockedAlice = weakAlice.lock();

    ASSERT_NE(lockedAlice, nullptr);
    EXPECT_EQ(race.position(lockedAlice), 1);
    EXPECT_EQ(race.getPoints(lockedAlice), 25);
}

TEST(Race, PointsSystemLifeTime)
{
    auto alice = std::make_shared<Driver>("Alice", "USA");

    std::weak_ptr<IPointsSystem const> weakPointsSystem;

    std::unique_ptr<Race> original;
    std::unique_ptr<Race> copy;

    {
        auto pointsSystem = std::make_shared<PointsSystem>();
        weakPointsSystem = pointsSystem;

        original = std::make_unique<Race>(
            "Race 1",
            std::list<std::shared_ptr<Driver>>{ alice },
            pointsSystem
        );

        copy = std::make_unique<Race>(*original);
    }

    EXPECT_FALSE(weakPointsSystem.expired());

    EXPECT_EQ(original->getPoints(alice), 25);
    EXPECT_EQ(copy->getPoints(alice), 25);
}