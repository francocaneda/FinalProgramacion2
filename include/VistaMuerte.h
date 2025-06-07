#ifndef VISTAMUERTE_H
#define VISTAMUERTE_H

#include "Vista.h"
#include "Juego.h"
#include <SFML/Graphics.hpp>

class VistaMuerte : public Vista {
public:
    VistaMuerte();
    void manejarEventos(sf::RenderWindow& ventana, Juego& juego) override;
    void actualizar(Juego& juego) override;
    void dibujar(sf::RenderWindow& ventana) override;

private:
    sf::Font font;
    sf::Text texto;
    bool cambioVistaSolicitado;  // Nuevo flag
};

#endif
