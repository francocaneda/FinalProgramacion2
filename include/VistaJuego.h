#ifndef VISTAJUEGO_H
#define VISTAJUEGO_H

#include "Vista.h"
#include "Personaje.h"
#include "Roca.h"
#include "Enemigo.h"
#include <SFML/Graphics.hpp>
#include <vector>

class VistaJuego : public Vista {
public:
    VistaJuego();
    ~VistaJuego();

    void manejarEventos(sf::RenderWindow& ventana, Juego& juego) override;
    void actualizar(Juego& juego) override;
    void dibujar(sf::RenderWindow& ventana) override;

private:
    sf::Texture texturaPersonaje;
    Personaje* personaje;

    sf::Texture texturaRoca;
    std::vector<Roca*> rocas;
    sf::Clock relojRoca;

    sf::Texture texturaEnemigo;
    std::vector<Enemigo*> enemigos;
    sf::Clock relojEnemigo;
    float tiempoProximaAparicionEnemigo;

    void spawnRoca();
    void spawnEnemigo();
    bool chequearColision(Personaje* personaje, Roca* roca);
    bool chequearColision(Personaje* personaje, Enemigo* enemigo);
};

#endif
