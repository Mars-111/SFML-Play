#include "Object.h"

#include <utility>
#include <iostream>
Object::Object(MySprite sprite, std::string spriteFile, int width, int height, Position position) :
        mySprite(std::move(sprite)), file(std::move(spriteFile)), width(width), height(height), position(position) {
    this->init();
}

Position Object::getPosition() {
    return position;
}

void Object::setPosition(Position newPosition) {
    this->position = newPosition;
    this->mySprite.setPosition(position.posX, position.posY);
}

int Object::getWidth() const {
    return width;
}

void Object::setWidth(int newWidth) {
    this->width = newWidth;
}

int Object::getHeight() const {
    return height;
}

void Object::setHeight(int newHeight) {
    this->height = newHeight;
}

Dir Object::getDir() {
    return dir;
}

void Object::setDir(Dir newDir) {
    this->dir = newDir;
}

std::string Object::getFile() const {
    return file;
}

void Object::setFile(std::string newFile) {
    this->file = std::move(newFile);
    init();
}

sf::Texture Object::getTexture() const {
    return texture;
}

void Object::init() {
    this->image.loadFromFile(this->file);
    this->texture.loadFromFile(this->file);
    this->mySprite.setPosition(position.posX, position.posY);
}

void Object::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    sf::Color color = sf::Color(200, 100, 200);

    target.draw(mySprite.getSprite(), states);
}
