#include "Juego.h"
#include <iostream>

Juego::Juego() : ventana(sf::VideoMode(1280, 720), "SFML Juego"), vistaActual(nullptr) {
    if (!musicaFondo.openFromFile("assets/musicaFondo.ogg")) {
        std::cerr << "Error cargando musicaFondo.ogg\n";
    } else {
        musicaFondo.setLoop(true);
        musicaFondo.play();
    }
}

Juego::~Juego() {
    if (vistaActual)
        delete vistaActual;
    // La musicaFondo se detiene autom�ticamente al destruirse el objeto.
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
    // La m�sica se detendr� al salir porque se destruye musicaFondo
}
