#include "Player.h"

#include <utility>


Player::Player(MySprite sprite, std::string spriteFile, int width, int height, Position position) :
        Object(std::move(sprite), std::move(spriteFile), width, height, position) {

}

void Player::move(Position newPosition) {
    this->setPosition(Position{newPosition.posX + this->position.posX, newPosition.posY + this->position.posY});
}

void Player::move(sf::Vector2i vector2i) {
    this->setPosition(Position{vector2i.x, vector2i.y});
}
