#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <SFML/Graphics.hpp>

class Personaje {
public:
    Personaje(sf::Texture& texture, float x, float y);
    void draw(sf::RenderWindow& window);
    void move(float offsetX);
    void setPosX(float x);             // <-- nuevo método para setear X
    void saltar();
    void actualizar();

    float getPosX() const;
    float getWidth() const;
    float getPosY() const;
    sf::FloatRect getGlobalBounds() const;

private:
    sf::Sprite sprite;

    bool enSuelo = true;
    float velocidadSalto = 0.0f;

    // Parámetros del salto ajustados para 1280x720
    float alturaMaximaSalto = 200.f;
    float velocidadSubidaConstante = -0.35f;
    float velocidadBajadaConstante = 0.35f;
};

#endif // PERSONAJE_H
