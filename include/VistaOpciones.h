#ifndef VISTAOPCIONES_H
#define VISTAOPCIONES_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Vista.h"
#include "Juego.h"

class VistaOpciones : public Vista {
public:
    VistaOpciones();

    void manejarEventos(sf::RenderWindow& ventana, Juego& juego) override;
    void actualizar(Juego& juego) override;
    void dibujar(sf::RenderWindow& ventana) override;

private:
    sf::Font font;
    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;

    std::vector<sf::Text> opciones;
    int seleccionActual = 0;

    // Estados de las opciones
    bool musicaActiva = true;
    bool mostrarControles = false;
    bool mostrarCreditos = false;

    void actualizarTextos();
    void actualizarColores();
};

#endif // VISTAOPCIONES_H
