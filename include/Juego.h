#ifndef JUEGO_H
#define JUEGO_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Vista.h"

class Juego {
public:
    Juego();
    ~Juego();

    void ejecutar();
    void cambiarVista(Vista* nuevaVista);

    // Métodos para controlar la música
    void pausarMusica();
    void reproducirMusica();
    bool musicaActiva() const;

private:
    sf::RenderWindow ventana;
    Vista* vistaActual;

    sf::Music musicaFondo;
    bool musicaEnReproduccion;
};

#endif
