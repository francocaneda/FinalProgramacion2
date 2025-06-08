#include "Personaje.h"
#include <iostream>

Personaje::Personaje(sf::Texture& texture, float x, float y) {
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    sprite.setScale(0.25f, 0.25f);

    // Cargar sonido de salto
    if (!bufferSalto.loadFromFile("assets/salto.ogg")) {
        std::cerr << "Error cargando salto.ogg\n";
    } else {
        sonidoSalto.setBuffer(bufferSalto);
    }
}

void Personaje::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Personaje::move(float offsetX) {
    sprite.move(offsetX, 0);
}

void Personaje::setPosX(float x) {
    sf::Vector2f pos = sprite.getPosition();
    sprite.setPosition(x, pos.y);
}

void Personaje::saltar() {
    if (enSuelo) {
        velocidadSalto = -1;  // Indicamos que comienza la subida
        enSuelo = false;

        // Reproducir sonido de salto
        sonidoSalto.play();
    }
}

void Personaje::actualizar() {
    if (!enSuelo) {
        float posY = sprite.getPosition().y;

        if (velocidadSalto < 0) {
            // Subiendo
            sprite.move(0, velocidadSubidaConstante);

            // Si llegamos a altura máxima → comenzar bajada
            if (posY <= alturaMaximaSalto) {
                velocidadSalto = 1; // comenzar la bajada
            }

        } else {
            // Bajando
            sprite.move(0, velocidadBajadaConstante);

            // Suelo
            if (posY >= 500) {
                sprite.setPosition(sprite.getPosition().x, 500);
                velocidadSalto = 0;
                enSuelo = true;
            }
        }
    }
}

float Personaje::getPosX() const {
    return sprite.getPosition().x;
}

float Personaje::getWidth() const {
    return sprite.getGlobalBounds().width;
}

float Personaje::getPosY() const {
    return sprite.getPosition().y;
}

sf::FloatRect Personaje::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}
