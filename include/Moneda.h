#ifndef MONEDA_H
#define MONEDA_H

#include <SFML/Graphics.hpp>

class Moneda {
private:
    sf::Sprite sprite;
    float tiempoAparicion;

public:
    Moneda(const sf::Texture& textura, float x, float y, float tiempoAparicion);

    void draw(sf::RenderWindow& ventana);
    sf::FloatRect getGlobalBounds() const;
    float getTiempoAparicion() const;

    void setScale(float scaleX, float scaleY);
};

#endif // MONEDA_H
