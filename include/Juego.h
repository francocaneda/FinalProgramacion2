#ifndef JUEGO_H
#define JUEGO_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> // <<-- Agregado para audio
#include "Vista.h"

class Juego {
public:
    Juego();
    ~Juego();

    void ejecutar();
    void cambiarVista(Vista* nuevaVista);

private:
    sf::RenderWindow ventana;
    Vista* vistaActual;

    sf::Music musicaFondo;  // <<-- Música de fondo
};

#endif
