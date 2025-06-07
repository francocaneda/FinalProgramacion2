#ifndef JUEGO_H
#define JUEGO_H

#include <SFML/Graphics.hpp>
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
};

#endif
