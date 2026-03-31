#include <SFML/Graphics.hpp>

int main(){
    sf::RenderWindow window(sf::VideoMode({800, 850}), "Breakout Game");
    sf::RectangleShape paddle({150.f, 20.f});
    paddle.setOrigin({75.f, 10.f});
    paddle.setPosition({400.f, 790.f});

    sf::CircleShape ball(14.f);
    ball.setOrigin({ball.getRadius(), ball.getRadius()});
    ball.setPosition({400.f, 766.f});

    sf::Vector2f velocity({0.1f,-0.1f}); //this would be up and right

    int lives = 3;

    while (window.isOpen()){
        while(auto event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }

        }
        window.clear(sf::Color(0,0,0)); //clear frame before rewrite

        //borders
        std::array leftLine = {sf::Vertex{sf::Vector2f(10.f, 10.f)}, sf::Vertex{sf::Vector2f(10.f, 790.f)}};
        window.draw(leftLine.data(), leftLine.size(), sf::PrimitiveType::Lines); //left wall
        std::array topLine = {sf::Vertex{sf::Vector2f(10.f, 10.f)}, sf::Vertex{sf::Vector2f(790.f, 10.f)}};
        window.draw(topLine.data(), topLine.size(), sf::PrimitiveType::Lines); //top wall 
        std::array rightLine = {sf::Vertex{sf::Vector2f(790.f, 10.f)}, sf::Vertex{sf::Vector2f(790.f, 790.f)}};
        window.draw(rightLine.data(), rightLine.size(), sf::PrimitiveType::Lines); //right wall

        //paddle 
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
            paddle.setPosition({(paddle.getPosition().x - 0.1f > 85.f ? paddle.getPosition().x - 0.1f : 85.f), 790.f});
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
            paddle.setPosition({(paddle.getPosition().x + 0.1f < 715.f ? paddle.getPosition().x + 0.1f : 715.f), 790.f});
        }
    

        window.draw(paddle);
        
        //ball
        ball.setPosition(ball.getPosition() + velocity);
        if(ball.getPosition().x >= 776.f || ball.getPosition().x <= 24.f){ velocity = {velocity.x*-1.f, velocity.y};}
        if(ball.getPosition().y <= 24.f){ velocity = {velocity.x, velocity.y*-1.f}; }
        if(ball.getPosition().y >= 780.0 && 
           (ball.getPosition().x > (paddle.getPosition().x - 75.f) && 
           (ball.getPosition().x < paddle.getPosition().x + 75.f))){
            velocity = {velocity.x, velocity.y*-1.f};
        }
        if(ball.getPosition().y > 805.f){
            lives--;
            ball.setPosition({400.f, 766.f});
            velocity = {0.1f,-0.1f};
        }
        window.draw(ball);

        window.display();//draw all above shapes
    }
    return 0;
}