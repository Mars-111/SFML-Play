#include "Game.h"

Game::Game()
{
    Init();
}

void Game::Init()
{

}

bool Game::Check()
{

}

void Game::Move(Direction direction)
{

}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    sf::Color color = sf::Color(200, 100, 200);

    target.draw(s, states);

    // Подготавливаем рамку для отрисовки всех плашек
    shape.setSize(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(color);
    shape.setFillColor(sf::Color::Transparent);

    // Подготавливаем текстовую заготовку для отрисовки номеров плашек
    sf::Text text("", font, 52);

    for (unsigned int i = 0; i < ARRAY_SIZE; i++)
    {
        shape.setOutlineColor(color);
        text.setFillColor(color);
        text.setString(std::to_string(elements[i]));
        if (solved)
        {
            // Решенную головоломку выделяем другим цветом
            shape.setOutlineColor(sf::Color::Cyan);
            text.setFillColor(sf::Color::Cyan);
        }
        else if (elements[i] == i + 1)
        {
            // Номера плашек на своих местах выделяем цветом
            text.setFillColor(sf::Color::Green);
        }

        // Рисуем все плашки, кроме пустой
        if (elements[i] > 0)
        {
            // Вычисление позиции плашки для отрисовки
            sf::Vector2f position(i % SIZE * CELL_SIZE + 10.f, i / SIZE * CELL_SIZE + 10.f);
            shape.setPosition(position);
            // Позицию текста подбирал вручную
            text.setPosition(position.x + 30.f + (elements[i] < 10 ? 15.f : 0.f), position.y + 25.f);
            // Отрисовываем рамку плашки
            target.draw(shape, states);
            // Отрисовываем номер плашки
            target.draw(text, states);
        }
    }
}