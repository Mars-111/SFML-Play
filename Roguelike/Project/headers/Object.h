#pragma once
#include "SFML/Graphics.hpp"
#include "MySprite.h"
enum Dir {
    RIGHT = 0, LEFT = 1,
    UP = 2, DOWN = 3
};

struct Position {
    int posX = 0;
    int posY = 0;
};

class Object : public sf::Drawable, public sf::Transformable {
public:
    Position getPosition();
    void setPosition(Position NewPosition);
    int getWidth() const;
    void setWidth(int newWidth);
    int getHeight() const;
    void setHeight(int newHeight);
    Dir getDir();
    void setDir(Dir newDir);
    std::string getFile() const;
    void setFile(std::string newFile);
    sf::Texture getTexture() const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    Object(MySprite sprite, std::string spriteFile, int width, int height, Position position = {0,0});
    MySprite mySprite;
    Dir dir = RIGHT;
protected:
    Position position;
    int width, height;
    //int currentSpriteFrame = 0;
private:
    void init();
    std::string file;
    sf::Image image;
    sf::Texture texture;
    //sf::Sprite sprite;
};