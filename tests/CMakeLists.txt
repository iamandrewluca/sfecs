project(sfecs_tests)

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(sfecs_tests
        WorldTest.cpp
        EntityTest.cpp)

target_link_libraries(sfecs_tests ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} )
target_link_libraries(sfecs_tests SFECS -lpthread -lm)