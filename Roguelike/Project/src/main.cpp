// main.cpp
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>
int main()
{
    // Создаем окно размером 600 на 600 и частотой обновления 60 кадров в секунду
    sf::RenderWindow window(sf::VideoMode(400, 400), "game");
    window.setFramerateLimit(120);


    // Создаем объект игры
    sf::Texture texture;
    texture.loadFromFile("player-sprites/run.png");
    MySprite tmpMySprite(texture, sf::IntRect(0,0,32,32), 6);
    Player player(tmpMySprite, "player-sprites/run.png", 100, 100, {50, 50});


    sf::Event event;

    sf::Clock clock;

    while (window.isOpen())
    {
        if (texture.up == player.getTexture()) std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!=\n";
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                // Получаем нажатую клавишу - выполняем соответствующее действие
                if (event.key.code == sf::Keyboard::Escape) window.close();

                if (event.key.code == sf::Keyboard::Right) {
                    player.mySprite.refresh(
                            player.getTexture(),
                            sf::IntRect(0,0,32,32),
                            player.mySprite.getCol());
                    player.move(Position{10,0});
                    player.dir = Dir::RIGHT;
                }
                if (event.key.code == sf::Keyboard::Left) {
                    player.mySprite.refresh(
                            player.getTexture(),
                            sf::IntRect(32, 0, -32, 32),
                            player.mySprite.getCol());
                    player.move(Position{-10,0});
                    player.dir = Dir::LEFT;
                }
                if (event.key.code == sf::Keyboard::Up) {
                    player.move(Position{0,-10});
                    player.dir = Dir::UP;
                }
                if (event.key.code == sf::Keyboard::Down) {
                    player.move(Position{0,10});
                    player.dir = Dir::DOWN;
                }

            }
        }

        if (clock.getElapsedTime().asMilliseconds() > 300) {
            player.mySprite.next();
            std::cout<<"player.mySprite.next();\n";
            clock.restart();
        }
        window.clear();
        window.draw(player.mySprite.getSprite());
        window.display();
    }

    return 0;
}