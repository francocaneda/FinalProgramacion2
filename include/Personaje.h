#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Personaje {
public:
    Personaje(sf::Texture& texture, float x, float y);
    void draw(sf::RenderWindow& window);
    void move(float offsetX);
    void setPosX(float x);
    void saltar();
    void actualizar();

    float getPosX() const;
    float getWidth() const;
    float getPosY() const;
    sf::FloatRect getGlobalBounds() const;

    bool estaVivo() const; // Método para verificar si el personaje está vivo
    void morir();          // Método para marcar al personaje como muerto

private:
    sf::Sprite sprite;

    bool enSuelo = true;
    float velocidadSalto = 0.0f;
    bool vivo; // Atributo para el estado de vida

    sf::SoundBuffer bufferSalto;
    sf::Sound sonidoSalto;


    float alturaMaximaSalto = 200.f;
    float velocidadSubidaConstante = -0.35f;
    float velocidadBajadaConstante = 0.35f;
};

#endif // PERSONAJE_H
