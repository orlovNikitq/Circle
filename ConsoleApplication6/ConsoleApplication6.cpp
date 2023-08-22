#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#define random rand()%256
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Circle");

    std::vector<sf::CircleShape> circles;
    srand(time(NULL));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Equal)
                {
                    sf::CircleShape circle(30.f);
                    circle.setFillColor(sf::Color(random, random, random));
                    circle.setPosition(rand() % 700, rand() % 500);
                    circles.push_back(circle);
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos(sf::Mouse::getPosition(window));
                    for (int i = 0; i < circles.size(); ++i)
                    {
                        if (circles[i].getGlobalBounds().contains(mousePos))
                        {
                            circles.erase(circles.begin() + i);
                            float xOffset = 0.f;
                            for (int j = 0; j < circles.size(); ++j)
                            {
                                circles[j].setPosition(xOffset, circles[j].getPosition().y);
                                xOffset += circles[j].getGlobalBounds().width + 10.f;
                            }
                            break;
                        }
                    }
                }
            }
        }

        window.clear();

        for (auto& i : circles)
        {
            window.draw(i);
        }

        window.display();
    }

}
