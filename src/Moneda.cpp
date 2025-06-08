#include "Moneda.h"

Moneda::Moneda(const sf::Texture& textura, float x, float y, float tiempo) {
    sprite.setTexture(textura);
    sprite.setPosition(x, y);
    tiempoAparicion = tiempo;
    sprite.setScale(0.05f, 0.05f);
}

void Moneda::draw(sf::RenderWindow& ventana) {
    ventana.draw(sprite);
}

sf::FloatRect Moneda::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

float Moneda::getTiempoAparicion() const {
    return tiempoAparicion;
}
