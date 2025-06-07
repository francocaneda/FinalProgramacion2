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

    // Par�metros del salto que pod�s ajustar f�cilmente
    float alturaMaximaSalto = 200.f;            // Altura m�xima (Y m�nima)
    float velocidadSubidaConstante = -0.25f;      // M�s lento todav�a
    float velocidadBajadaConstante = 0.25f;       // Bajada lenta
};

#endif // PERSONAJE_H
