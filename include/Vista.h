#ifndef VISTA_H
#define VISTA_H

#include <SFML/Graphics.hpp>
class Juego; // Forward declaration para evitar inclusión circular

class Vista {
public:
    virtual ~Vista() = default;

    virtual void manejarEventos(sf::RenderWindow& ventana, Juego& juego) = 0;
    virtual void actualizar(Juego& juego) = 0;
    virtual void dibujar(sf::RenderWindow& ventana) = 0;
};

#endif // VISTA_H
