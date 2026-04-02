#include <SFML/Graphics.hpp>
#include "physicsManager.h"
#include "GameManager.h"

int main(){
    sf::RenderWindow window(sf::VideoMode({800, 850}), "Breakout Game");
    sf::RectangleShape paddle({150.f, 20.f});
    paddle.setOrigin({75.f, 10.f});
    paddle.setPosition({400.f, 790.f});

    sf::CircleShape ball(14.f);
    ball.setOrigin({ball.getRadius(), ball.getRadius()});
    ball.setPosition({400.f, 766.f});

    PhysicsManager PhysicsManager;
    PhysicsManager.setVelocity({0.1f, -0.1f});

    GameManager GameManager;
    
    float xOffset = 10.f; //border of the game area offset for the x-axis (left & right)
    float yOffset = 10.f; //border of the game area offset for the y-axis (top & bottom)
    float paddleYPos = 790.f; //height/y-position of the paddle
    float killY = 805.f; //y-position at which the ball will be considered as out of bounds and result in the loss of a life

    int lives = 3;

    while (window.isOpen()){
        while(auto event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }

        }
        window.clear(sf::Color(0,0,0)); //clear frame before rewrite

        //borders
        std::array leftLine = {sf::Vertex{sf::Vector2f(xOffset, yOffset)}, sf::Vertex{sf::Vector2f(xOffset, (window.getSize().y - yOffset))}};
        window.draw(leftLine.data(), leftLine.size(), sf::PrimitiveType::Lines); //left wall
        std::array topLine = {sf::Vertex{sf::Vector2f(xOffset, yOffset)}, sf::Vertex{sf::Vector2f((window.getSize().x - xOffset), yOffset)}};
        window.draw(topLine.data(), topLine.size(), sf::PrimitiveType::Lines); //top wall 
        std::array rightLine = {sf::Vertex{sf::Vector2f((window.getSize().x - xOffset), yOffset)}, sf::Vertex{sf::Vector2f((window.getSize().x - xOffset), (window.getSize().y - yOffset))}};
        window.draw(rightLine.data(), rightLine.size(), sf::PrimitiveType::Lines); //right wall

        
        //paddle 
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){ //move left
            paddle.setPosition({(paddle.getPosition().x - 0.1f > (xOffset + (paddle.getSize().x / 2)) ? paddle.getPosition().x - 0.1f : (xOffset + (paddle.getSize().x / 2))), paddleYPos});
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){ //move right
            paddle.setPosition({(paddle.getPosition().x + 0.1f < (window.getSize().x - (xOffset + (paddle.getSize().x / 2))) ? paddle.getPosition().x + 0.1f : (window.getSize().x - (xOffset + (paddle.getSize().x / 2)))), paddleYPos});
        }

        if(GameManager.haveDied()){ paddle.setFillColor(sf::Color::Red); } //life tracking and general game manager testing
        window.draw(paddle);
        
        //ball
        ball.setPosition(ball.getPosition() + PhysicsManager.getVelocity());
        if(ball.getPosition().x >= (window.getSize().x - (xOffset + ball.getRadius())) || ball.getPosition().x <= (xOffset + ball.getRadius())){ PhysicsManager.reflectX(); } //bounce off left or right wall
        if(ball.getPosition().y <= (yOffset + ball.getRadius())){ PhysicsManager.reflectY(); } //bounce off top wall/ceiling 
        if(ball.getPosition().y >= (paddleYPos-(paddle.getSize().y)) && 
           ((ball.getPosition().x > (paddle.getPosition().x - (paddle.getSize().x/2))) && 
            (ball.getPosition().x < (paddle.getPosition().x + (paddle.getSize().x/2))))){
            PhysicsManager.reflectY(); }
        if(ball.getPosition().y > killY){
            GameManager.loseLife();
            ball.setPosition({400.f, 766.f});
            PhysicsManager.setVelocity({0.1f,-0.1f});
        }
        window.draw(ball);

        window.display();//display all above shapes
    }
    return 0;
}