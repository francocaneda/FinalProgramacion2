#include "PersonajeSecundario.h"
#include <iostream>

PersonajeSecundario::PersonajeSecundario(sf::Texture& texture, float x, float y) : vivo(true) {
    sprite.setTexture(texture);
    sprite.setPosition(x + 150, y); // A la derecha del personaje principal
    sprite.setScale(0.23f, 0.23f);


    if (!bufferSalto.loadFromFile("assets/salto.ogg")) {
        std::cerr << "Error cargando salto.ogg\n";
    } else {
        sonidoSalto.setBuffer(bufferSalto);
    }
}

void PersonajeSecundario::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void PersonajeSecundario::move(float offsetX) {
    sprite.move(offsetX, 0);
}

void PersonajeSecundario::setPosX(float x) {
    sf::Vector2f pos = sprite.getPosition();
    sprite.setPosition(x, pos.y);
}

void PersonajeSecundario::saltar() {
    if (enSuelo) {
        velocidadSalto = -1;
        enSuelo = false;
        sonidoSalto.play();
    }
}

void PersonajeSecundario::actualizar() {
    if (!enSuelo) {
        float posY = sprite.getPosition().y;

        if (velocidadSalto < 0) {
            sprite.move(0, velocidadSubidaConstante);
            if (posY <= alturaMaximaSalto) {
                velocidadSalto = 1;
            }
        } else {
            sprite.move(0, velocidadBajadaConstante);
            if (posY >= 500) {
                sprite.setPosition(sprite.getPosition().x, 500);
                velocidadSalto = 0;
                enSuelo = true;
            }
        }
    }
}

float PersonajeSecundario::getPosX() const {
    return sprite.getPosition().x;
}

float PersonajeSecundario::getWidth() const {
    return sprite.getGlobalBounds().width;
}

float PersonajeSecundario::getPosY() const {
    return sprite.getPosition().y;
}

sf::FloatRect PersonajeSecundario::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

bool PersonajeSecundario::estaVivo() const {
    return vivo;
}

void PersonajeSecundario::morir() {
    vivo = false;
}
