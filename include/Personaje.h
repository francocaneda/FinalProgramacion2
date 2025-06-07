#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <SFML/Graphics.hpp>

class Personaje {
public:
    Personaje(sf::Texture& texture, float x, float y);
    void draw(sf::RenderWindow& window);
    void move(float offsetX);
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

    // Parámetros del salto que podés ajustar fácilmente
    float alturaMaximaSalto = 200.f;            // Altura máxima (Y mínima)
    float velocidadSubidaConstante = -0.25f;      // Más lento todavía
    float velocidadBajadaConstante = 0.25f;       // Bajada lenta
};

#endif // PERSONAJE_H
