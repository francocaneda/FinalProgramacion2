#ifndef ROCA_H
#define ROCA_H

#include <SFML/Graphics.hpp>

class Roca {
public:
    Roca(sf::Texture& texture, float x);

    void actualizar(float deltaTime);
    void draw(sf::RenderWindow& window);

    sf::FloatRect getGlobalBounds() const;
    float getPosY() const;

private:
    sf::Sprite sprite;
    float velocidad = 0.8f; // caída lenta
};

#endif
