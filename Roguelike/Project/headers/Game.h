#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <array>
#include "Object.h"

const int SIZE = 1000;						// Размер игрового поля в плашках
const int ARRAY_SIZE = SIZE * SIZE;		// Размер массива
const int CELL_SIZE = 1;				// Размер плашки в пикселях
const int FIELD_SIZE = SIZE*CELL_SIZE;				// Размер игрового поля в пикселях

enum class Direction { Left = 0, Right = 1, Up = 2, Down = 3 };

class Game : public sf::Drawable, public sf::Transformable
{
protected:
    std::array<std::unique_ptr<Object>, ARRAY_SIZE> elements;
    bool end;

public:
    Game();
    void Init();
    bool Check();
    void Move(Direction direction);
public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};