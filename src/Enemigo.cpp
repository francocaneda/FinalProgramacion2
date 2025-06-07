#include "Enemigo.h"

Enemigo::Enemigo(sf::Texture& texture, float x) {
    sprite.setTexture(texture);
    sprite.setPosition(x, 500); // altura del suelo, mismo que el personaje
    sprite.setScale(0.18f, 0.18f); // ajustar tamaño según png
}

void Enemigo::actualizar(float velocidad) {
    sprite.move(-velocidad, 0);
}

void Enemigo::draw(sf::RenderWindow& ventana) {
    ventana.draw(sprite);
}

float Enemigo::getPosX() const {
    return sprite.getPosition().x;
}

float Enemigo::getPosY() const {
    return sprite.getPosition().y;
}

sf::FloatRect Enemigo::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

