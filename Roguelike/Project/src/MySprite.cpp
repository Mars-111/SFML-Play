#include "MySprite.h"

MySprite::MySprite(const sf::Texture &texture, sf::IntRect rectAlgorithm, unsigned short columns) {//: rect(rectAlgorithm), col(col) {
    //если 0 -> исключение
    this->refresh(texture, rectAlgorithm, columns);
}

void MySprite::refresh(const sf::Texture &texture, sf::IntRect rectAlgorithm, unsigned short columns) {
    this->rect = rectAlgorithm;
    this->col = columns;
    sprite.setTexture(texture);
    sprite.setTextureRect(rect);
}

const sf::Sprite & MySprite::getSprite() const {
    return this->sprite;
}

sf::Sprite MySprite::getCopySprite() {
    return this->sprite;
}

const sf::Sprite &MySprite::next() {
    currentSlide = currentSlide%col;

    this->sprite.setTextureRect(sf::IntRect(
            rect.left + (currentSlide * rect.width),
            rect.top,
            rect.width,
            rect.height
    ));

    currentSlide++;

    return sprite;
}

void MySprite::skip(unsigned int countSkip) {
    currentSlide = (currentSlide + countSkip)%col;
}

const sf::IntRect &MySprite::getRect() {
    return rect;
}

void MySprite::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

unsigned short MySprite::getCol() {
    return col;
}
