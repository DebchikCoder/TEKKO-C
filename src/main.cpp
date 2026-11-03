#include <iostream>
#include <SFML/Graphics.hpp>

int main(int, char**)
{
    //creating window
    sf::RenderWindow window(sf::VideoMode({1280, 960}), "TEKKO");

    //creating circle
    sf::CircleShape circle(50.0f);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition({375.f, 275.f});

    //main loop
    while(window.isOpen())
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.draw(circle);
        window.display();
        
    }

    return 0;
}
