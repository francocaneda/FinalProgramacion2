#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <SFML/Graphics.hpp>

class Enemigo {
public:
    Enemigo(sf::Texture& texture, float x);

    void actualizar(float velocidad);
    void draw(sf::RenderWindow& ventana);

    float getPosX() const;
    float getPosY() const;
    sf::FloatRect getGlobalBounds() const;

private:
    sf::Sprite sprite;
};

#endif

