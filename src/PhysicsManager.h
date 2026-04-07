#pragma once

#include <SFML/Graphics.hpp>

class PhysicsManager {
    private:
        sf::Vector2f velocity;
    
    public:
        PhysicsManager(){}
        sf::Vector2f getVelocity(){ return velocity; }
        void setVelocity(sf::Vector2f vel){ velocity = vel; }
        void reflectY() { velocity = {velocity.x, velocity.y*-1}; }
        void reflectX() { velocity = {velocity.x*-1, velocity.y}; }
};
