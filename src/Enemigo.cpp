#include "Enemigo.h"
#include <cstdlib>  // para rand()

Enemigo::Enemigo(sf::Texture& texture, float x) {
    sprite.setTexture(texture);
    sprite.setPosition(x, 500); // altura del suelo, mismo que el personaje
    sprite.setScale(0.18f, 0.18f);

    // Asignar velocidad aleatoria entre 0.15f y 0.35f
    velocidad = 0.15f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.20f)));
}

void Enemigo::actualizar() {
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
