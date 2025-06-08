#include "Moneda.h"

Moneda::Moneda(const sf::Texture& textura, float x, float y, float tiempoAparicion)
    : tiempoAparicion(tiempoAparicion)
{
    sprite.setTexture(textura);
    sprite.setPosition(x, y);
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

void Moneda::setScale(float scaleX, float scaleY) {
    sprite.setScale(scaleX, scaleY);
}
