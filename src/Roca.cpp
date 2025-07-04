#include "Roca.h"

Roca::Roca(sf::Texture& texture, float x) {
    sprite.setTexture(texture);
    sprite.setPosition(x, 0.0f); // comienza arriba
    sprite.setScale(0.15f, 0.15f);
}

void Roca::actualizar(float deltaTime) {
    sprite.move(0, velocidad * deltaTime);
}

void Roca::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Roca::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

float Roca::getPosY() const {
    return sprite.getPosition().y;
}
