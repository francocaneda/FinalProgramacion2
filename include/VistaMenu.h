#ifndef VISTAMENU_H
#define VISTAMENU_H

#include "Vista.h"
#include "Juego.h"
#include <SFML/Graphics.hpp>
#include <vector>

class VistaMenu : public Vista {
public:
    VistaMenu();

    void manejarEventos(sf::RenderWindow& ventana, Juego& juego) override;
    void actualizar(Juego& juego) override;
    void dibujar(sf::RenderWindow& ventana) override;

private:
    sf::Font font;
    std::vector<sf::Text> opciones;
    int seleccionActual = 0;

    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;

    void actualizarColores();
};

#endif
