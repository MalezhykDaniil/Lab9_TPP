cmake_minimum_required(VERSION 3.21)

project(LeaderBoard LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(LeaderBoard
    include/Driver.h
    include/LeaderBoard.h
    include/SelfDrivingCar.h
    include/Race.h
    include/PointsSystem.h
    include/IPointsSystem.h
    include/AlternativePointsSystem.h
    source/SelfDrivingCar.cpp
    source/Driver.cpp
    source/Race.cpp
    source/LeaderBoard.cpp
    source/PointsSystem.cpp  
     
    source/AlternativePointsSystem.cpp  "include/IRaceResult.h")

target_include_directories(LeaderBoard PUBLIC include)
set_property(TARGET LeaderBoard PROPERTY CXX_STANDARD 20)

include(CTest)

if(BUILD_TESTING)
    find_package(GTest CONFIG REQUIRED)
    include(GoogleTest)

    add_subdirectory(tests)
endif()