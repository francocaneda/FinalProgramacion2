#include "Juego.h"

Juego::Juego() : ventana(sf::VideoMode(1280, 720), "SFML Juego"), vistaActual(nullptr) {}

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
