#ifndef VISTAOPCIONES_H
#define VISTAOPCIONES_H

#include "Vista.h"
#include "Juego.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class VistaOpciones : public Vista {
public:
    VistaOpciones();

    void manejarEventos(sf::RenderWindow& ventana, Juego& juego) override;
    void actualizar(Juego& juego) override;
    void dibujar(sf::RenderWindow& ventana) override;

private:
    sf::Font font;
    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;

    std::vector<sf::Text> opciones;
    int seleccionActual = 0;

    bool musicaActiva = true;
    bool mostrarControles = false;

    sf::SoundBuffer bufferCambio;
    sf::Sound sonidoCambio;

    void actualizarTextos();
    void actualizarColores();
};

#endif
