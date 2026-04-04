#include <SFML/Graphics.hpp>
#include "PhysicsManager.h"
#include "GameManager.h"

/**CLARIFICATIONS FOR DEVELOPERS:
 * In SFML, the coordinate system for a window of dimensions {width, height} has the following corner coordinates:
 * -Top-Left: (0,0)
 * -Top-Right: (width, 0)
 * -Bottom-Left: (0, height)
 * -Bottom-Right: (width, height)
 * 
 * In order to compensate for the fact that the y-value increases as you go down in the window, a negative y-value
 * in the velocity will mean that the ball is going up, and a positive mean that it is going down. 
 */

int main(){
    sf::RenderWindow window(sf::VideoMode({800, 850}), "Breakout Game");
    window.setFramerateLimit(950); //To smooth the speed of the game/ball to be more consistient (not entierly working rn, looking into it)

    sf::RectangleShape paddle({150.f, 20.f});
    paddle.setOrigin({75.f, 10.f});
    paddle.setPosition({400.f, 790.f});

    sf::CircleShape ball(14.f);
    ball.setOrigin({ball.getRadius(), ball.getRadius()});
    ball.setPosition({400.f, 766.f});

    PhysicsManager PhysicsManager;
    PhysicsManager.setVelocity({0.1f, -0.1f});

    GameManager GameManager;
    
    const float X_OFFSET = 10.f; //border of the game area offset for the x-axis (left & right)
    const float Y_OFFSET = 10.f; //border of the game area offset for the y-axis (top & bottom)
    const float PADDLE_Y_POS = 790.f; //height/y-position of the paddle

    while (window.isOpen()){
        while(auto event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }
        window.clear(sf::Color(0,0,0)); //clear frame before rewrite

        //borders
        std::array leftLine = {sf::Vertex{sf::Vector2f(X_OFFSET, Y_OFFSET)}, sf::Vertex{sf::Vector2f(X_OFFSET, (window.getSize().y - Y_OFFSET))}};
        window.draw(leftLine.data(), leftLine.size(), sf::PrimitiveType::Lines); //left wall
        std::array topLine = {sf::Vertex{sf::Vector2f(X_OFFSET, Y_OFFSET)}, sf::Vertex{sf::Vector2f((window.getSize().x - X_OFFSET), Y_OFFSET)}};
        window.draw(topLine.data(), topLine.size(), sf::PrimitiveType::Lines); //top wall 
        std::array rightLine = {sf::Vertex{sf::Vector2f((window.getSize().x - X_OFFSET), Y_OFFSET)}, sf::Vertex{sf::Vector2f((window.getSize().x - X_OFFSET), (window.getSize().y - Y_OFFSET))}};
        window.draw(rightLine.data(), rightLine.size(), sf::PrimitiveType::Lines); //right wall

        //paddle 
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){ //move left
            paddle.setPosition({(paddle.getPosition().x - 0.1f > (X_OFFSET + (paddle.getSize().x / 2)) ? paddle.getPosition().x - 0.1f : (X_OFFSET + (paddle.getSize().x / 2))), PADDLE_Y_POS});
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){ //move right
            paddle.setPosition({(paddle.getPosition().x + 0.1f < (window.getSize().x - (X_OFFSET + (paddle.getSize().x / 2))) ? paddle.getPosition().x + 0.1f : (window.getSize().x - (X_OFFSET + (paddle.getSize().x / 2)))), PADDLE_Y_POS});
        }

        if(GameManager.haveDied()){ paddle.setFillColor(sf::Color::Red); } //life tracking and general game manager testing
        window.draw(paddle);
        
        //ball
        ball.setPosition(ball.getPosition() + PhysicsManager.getVelocity());
        if(ball.getPosition().x >= (window.getSize().x - (X_OFFSET + ball.getRadius())) || ball.getPosition().x <= (X_OFFSET + ball.getRadius())){ PhysicsManager.reflectX(); } //bounce off left or right wall
        if(ball.getPosition().y <= (Y_OFFSET + ball.getRadius())){ PhysicsManager.reflectY(); } //bounce off top wall/ceiling 
        if(ball.getPosition().y >= (PADDLE_Y_POS-(paddle.getSize().y/2)-(ball.getRadius())) && 
           ((ball.getPosition().x > (paddle.getPosition().x - (paddle.getSize().x/2) - ball.getRadius()/2)) && 
            (ball.getPosition().x < (paddle.getPosition().x + (paddle.getSize().x/2) + ball.getRadius()/2))) &&
           (PhysicsManager.getVelocity().y > 0)){
            PhysicsManager.reflectY(); 
        }
        if(ball.getPosition().y > (PADDLE_Y_POS-(paddle.getSize().y/2)-(ball.getRadius())+10)){
            GameManager.loseLife();
            ball.setPosition({400.f, 766.f});
            PhysicsManager.setVelocity({0.1f,-0.1f});
        }
        window.draw(ball);

        window.display();//display all above shapes
    }
    return 0;
}