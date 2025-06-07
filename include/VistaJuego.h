#ifndef VISTAJUEGO_H
#define VISTAJUEGO_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Juego.h"
#include "Personaje.h"
#include "Roca.h"
#include "Enemigo.h"
#include "Vista.h"   // importante incluir Vista.h para heredar

class VistaJuego : public Vista {   // <---- HERENCIA aquí
public:
    VistaJuego();
    ~VistaJuego();

    void manejarEventos(sf::RenderWindow& ventana, Juego& juego) override;
    void actualizar(Juego& juego) override;
    void dibujar(sf::RenderWindow& ventana) override;

private:
    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;

    sf::Texture texturaPersonaje;
    sf::Texture texturaRoca;
    sf::Texture texturaEnemigo;

    Personaje* personaje;
    std::vector<Roca*> rocas;
    std::vector<Enemigo*> enemigos;

    sf::Clock clockRocas;
    sf::Clock clockEnemigos;

    float tiempoProximoSpawnRoca;

    void verificarColisiones(Juego& juego);
};

#endif // VISTAJUEGO_H
