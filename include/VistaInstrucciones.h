#ifndef VISTAINSTRUCCIONES_H
#define VISTAINSTRUCCIONES_H

#include "Vista.h"
#include "Juego.h"
#include <SFML/Graphics.hpp>

class VistaInstrucciones : public Vista {
public:
    VistaInstrucciones();

    void manejarEventos(sf::RenderWindow& ventana, Juego& juego) override;
    void actualizar(Juego& juego) override;
    void dibujar(sf::RenderWindow& ventana) override;

private:
    sf::Font font;
    sf::Text textoInstrucciones;
    sf::Text textoVolver;

    int seleccionActual;

    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;

    sf::SoundBuffer bufferCambio;
    sf::Sound sonidoCambio;

    void actualizarColores();
};

#endif

