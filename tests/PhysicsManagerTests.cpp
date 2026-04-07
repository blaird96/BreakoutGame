#include "TestHarness.h"

#include "../src/PhysicsManager.h"

TEST_CASE(physics_manager_stores_velocity) {
    PhysicsManager manager;
    manager.setVelocity({3.f, -4.f});
    CHECK_EQ(manager.getVelocity().x, 3.f);
    CHECK_EQ(manager.getVelocity().y, -4.f);
}

TEST_CASE(physics_manager_reflect_x_inverts_horizontal_velocity) {
    PhysicsManager manager;
    manager.setVelocity({5.f, 2.f});
    manager.reflectX();
    CHECK_EQ(manager.getVelocity().x, -5.f);
    CHECK_EQ(manager.getVelocity().y, 2.f);
}

TEST_CASE(physics_manager_reflect_y_inverts_vertical_velocity) {
    PhysicsManager manager;
    manager.setVelocity({5.f, -2.f});
    manager.reflectY();
    CHECK_EQ(manager.getVelocity().x, 5.f);
    CHECK_EQ(manager.getVelocity().y, 2.f);
}

TEST_CASE(physics_manager_reflect_x_then_y_inverts_both_axes) {
    PhysicsManager manager;
    manager.setVelocity({1.5f, -7.f});
    manager.reflectX();
    manager.reflectY();
    CHECK_EQ(manager.getVelocity().x, -1.5f);
    CHECK_EQ(manager.getVelocity().y, 7.f);
}
