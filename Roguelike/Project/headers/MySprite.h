#pragma once
#include <SFML/Graphics.hpp>

class MySprite {
private:
    sf::IntRect rect;
    sf::Sprite sprite;
    unsigned short col = 1;
    unsigned int currentSlide = 0;
public:
    MySprite(const sf::Texture& texture, sf::IntRect rectAlgorithm, unsigned short columns);
    void refresh(const sf::Texture& texture, sf::IntRect rectAlgorithm, unsigned short columns);
    const sf::Sprite & getSprite() const;
    sf::Sprite getCopySprite();
    const sf::Sprite& next();
    void skip(unsigned int countSkip);
    const sf::IntRect& getRect();
    void setPosition(float x, float y);
    unsigned short getCol();
};