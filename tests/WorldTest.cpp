//
// Created by Andrei Luca on 2/18/16.
//

#include <gtest/gtest.h>
#include <SFECS/World.hpp>

TEST(WorldTest , Constructor) {

    sfecs::World* world{new sfecs::World()};

    EXPECT_NE(world, nullptr) << "World was not created";
}