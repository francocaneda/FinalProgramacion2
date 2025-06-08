#include "Juego.h"
#include <iostream>

Juego::Juego() : ventana(sf::VideoMode(1280, 720), "SFML Juego"), vistaActual(nullptr), musicaEnReproduccion(false) {
    if (musicaFondo.openFromFile("assets/musicaFondo.ogg")) {
        musicaFondo.setLoop(true);
        musicaFondo.play();
        musicaEnReproduccion = true;
    } else {
        std::cerr << "Error al cargar musicaFondo.ogg\n";
    }
}

Juego::~Juego() {
    if (vistaActual)
        delete vistaActual;
}

void Juego::cambiarVista(Vista* nuevaVista) {
    if (vistaActual)
        delete vistaActual;
    vistaActual = nuevaVista;
}

void Juego::ejecutar() {
    while (ventana.isOpen()) {
        if (vistaActual) {
            vistaActual->manejarEventos(ventana, *this);
            vistaActual->actualizar(*this);
            ventana.clear();
            vistaActual->dibujar(ventana);
            ventana.display();
        }
    }
}

void Juego::pausarMusica() {
    if (musicaEnReproduccion) {
        musicaFondo.pause();
        musicaEnReproduccion = false;
    }
}

void Juego::reproducirMusica() {
    if (!musicaEnReproduccion) {
        musicaFondo.play();
        musicaEnReproduccion = true;
    }
}

bool Juego::musicaActiva() const {
    return musicaEnReproduccion;
}
