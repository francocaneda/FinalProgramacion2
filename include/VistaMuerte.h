#ifndef VISTAMUERTE_H
#define VISTAMUERTE_H

#include "Vista.h"
#include "Juego.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class VistaMuerte : public Vista {
public:
    VistaMuerte();

    void manejarEventos(sf::RenderWindow& ventana, Juego& juego) override;
    void actualizar(Juego& juego) override;
    void dibujar(sf::RenderWindow& ventana) override;

private:
    sf::Font font;
    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;

    std::vector<sf::Text> opciones;
    int seleccionActual = 0;

    sf::SoundBuffer bufferCambio;
    sf::Sound sonidoCambio;

    bool cambioVistaSolicitado;

    void actualizarColores();  // <--- Declara esta función
};

#endif
