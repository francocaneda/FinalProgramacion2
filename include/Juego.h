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
    void solicitarCambioVista(Vista* nuevaVista);

    // M�todos para controlar la m�sica
    void pausarMusica();
    void reproducirMusica();
    bool musicaActiva() const;
    void setPuntajeFinal(int puntos) { puntajeFinal = puntos; }
    int getPuntajeFinal() const { return puntajeFinal; }

private:
    sf::RenderWindow ventana;
    Vista* vistaActual;
    Vista* vistaNuevaSolicitada;

    sf::Music musicaFondo;
    bool musicaEnReproduccion;
    int puntajeFinal;
};

#endif
