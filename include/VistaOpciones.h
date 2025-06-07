#ifndef VISTAOPCIONES_H
#define VISTAOPCIONES_H

#include "Vista.h"
#include "Juego.h"
#include <SFML/Graphics.hpp>

class VistaOpciones : public Vista {
public:
    VistaOpciones();

    void manejarEventos(sf::RenderWindow& ventana, Juego& juego) override;
    void actualizar(Juego& juego) override;
    void dibujar(sf::RenderWindow& ventana) override;

private:
    sf::Font font;
    sf::Text texto;
};

#endif

