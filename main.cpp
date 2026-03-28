#include <SFML/Graphics.hpp>

int main(){
    sf::RenderWindow window(sf::VideoMode({800, 800}), "Breakout Game");
    sf::RectangleShape paddle({150.f, 20.f});
    paddle.setOrigin({75.f, 10.f});
    paddle.setPosition({400.f, 790.f});

    sf::CircleShape ball(14.f);
    ball.setOrigin({ball.getRadius(), ball.getRadius()});
    ball.setPosition({400.f, 766.f});

    sf::Vector2f velocity({0.1f,-0.1f}); //this would be up and right

    while (window.isOpen()){
        while(auto event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }

        }
        window.clear(sf::Color(0,0,0)); //clear frame before rewrite

        std::array leftLine = {sf::Vertex{sf::Vector2f(10.f, 10.f)}, sf::Vertex{sf::Vector2f(10.f, 790.f)}};
        window.draw(leftLine.data(), leftLine.size(), sf::PrimitiveType::Lines); //left wall

        std::array topLine = {sf::Vertex{sf::Vector2f(10.f, 10.f)}, sf::Vertex{sf::Vector2f(790.f, 10.f)}};
        window.draw(topLine.data(), topLine.size(), sf::PrimitiveType::Lines); //top wall 

        std::array rightLine = {sf::Vertex{sf::Vector2f(790.f, 10.f)}, sf::Vertex{sf::Vector2f(790.f, 790.f)}};
        window.draw(rightLine.data(), rightLine.size(), sf::PrimitiveType::Lines); //right wall

        window.draw(paddle);

        ball.setPosition(ball.getPosition() + velocity);
        if(ball.getPosition().x >= 776.f || ball.getPosition().x <= 24.f){
            velocity = {velocity.x*-1.f, velocity.y};
        }
        if(ball.getPosition().y >= 776.0 || ball.getPosition().y <= 24.f){
            velocity = {velocity.x, velocity.y*-1.f};
        }
        window.draw(ball);

        window.display();
    }
    return 0;
}