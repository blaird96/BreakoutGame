#pragma once

#include <SFML/Graphics.hpp>

class PhysicsManager {
    private:
        sf::Vector2f velocity;
    
    public:
        PhysicsManager(){}
        /**
         * Returns current velocity of the ball
         */
        sf::Vector2f getVelocity(){ return velocity; }
        /**
         * Sets the current velocity of the ball
         */
        void setVelocity(sf::Vector2f vel){ velocity = vel; }
        /**
         * Inverses (*-1) the y value, which represents the ball bouncing off of a horizontal plane (roof/paddle)
         */
        void reflectY() { velocity = {velocity.x, velocity.y*-1}; }
        /**
         * Inverses (*-1) the x value, which represents the ball bouncing off of a vertical plane (left/right wall)
         */
        void reflectX() { velocity = {velocity.x*-1, velocity.y}; }
};
