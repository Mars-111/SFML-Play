#pragma once
#include "Object.h"

class Player : public Object {

public:
    Player(MySprite sprite, std::string spriteFile, int width, int height, Position position = {0,0});

    void move(Position newPosition); //idk
    void move(sf::Vector2i vector2i);
};