add_executable(LeaderBoard_Test
    LeaderBoard_Test.cpp
)

set_property(TARGET LeaderBoard_Test PROPERTY CXX_STANDARD 20)

target_link_libraries(LeaderBoard_Test
    PRIVATE LeaderBoard
    PRIVATE GTest::gtest_main
)

gtest_discover_tests(LeaderBoard_Test)