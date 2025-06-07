#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <SFML/Graphics.hpp>

class Enemigo {
public:
    Enemigo(sf::Texture& texture, float x);

    void actualizar();  // ahora sin parámetro
    void draw(sf::RenderWindow& ventana);

    float getPosX() const;
    float getPosY() const;
    sf::FloatRect getGlobalBounds() const;

private:
    sf::Sprite sprite;
    float velocidad;  // velocidad propia de cada enemigo
};

#endif
