#include "Juego.h"
#include <iostream>

Juego::Juego()
    : ventana(sf::VideoMode(1280, 720), "SFML Juego"),
      vistaActual(nullptr),
      vistaNuevaSolicitada(nullptr),
      musicaEnReproduccion(false) {

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
    if (vistaNuevaSolicitada)
        delete vistaNuevaSolicitada;
}

void Juego::cambiarVista(Vista* nuevaVista) {
    // Cambio inmediato, eliminar la vista actual
    if (vistaActual)
        delete vistaActual;
    vistaActual = nuevaVista;
}

void Juego::solicitarCambioVista(Vista* nuevaVista) {
    // Cambio diferido: almacena la vista para cambiar luego
    if (vistaNuevaSolicitada)
        delete vistaNuevaSolicitada;
    vistaNuevaSolicitada = nuevaVista;
}

void Juego::ejecutar() {
    while (ventana.isOpen()) {
        if (vistaActual) {
            vistaActual->manejarEventos(ventana, *this);
            vistaActual->actualizar(*this);

            // Realiza el cambio diferido aquí para evitar superposiciones
            if (vistaNuevaSolicitada) {
                delete vistaActual;
                vistaActual = vistaNuevaSolicitada;
                vistaNuevaSolicitada = nullptr;
            }

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
