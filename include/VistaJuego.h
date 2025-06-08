#ifndef VISTAJUEGO_H
#define VISTAJUEGO_H

#include "Vista.h"
#include "Juego.h"
#include "Personaje.h"
#include "Roca.h"
#include "Enemigo.h"
#include "Moneda.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class VistaJuego : public Vista {
private:
    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;

    sf::Texture texturaPersonaje;
    sf::Texture texturaRoca;
    sf::Texture texturaEnemigo;
    sf::Texture texturaMoneda;

    Personaje* personaje;
    std::vector<Roca*> rocas;
    std::vector<Enemigo*> enemigos;
    std::vector<Moneda*> monedas;

    sf::Clock clockRocas;
    sf::Clock clockEnemigos;
    sf::Clock clockMonedas;
    sf::Clock relojGeneral;

    float tiempoProximoSpawnRoca;
    float tiempoProximoSpawnMoneda;
    int puntos = 0;
    int monedasConsecutivas;
    sf::Font fuente;
    sf::Text textoPuntos;

public:
    VistaJuego();
    virtual ~VistaJuego();

    virtual void manejarEventos(sf::RenderWindow& ventana, Juego& juego);
    virtual void actualizar(Juego& juego);
    virtual void dibujar(sf::RenderWindow& ventana);

private:
    void verificarColisiones(Juego& juego);
    sf::SoundBuffer bufferMoneda;
    sf::Sound sonidoMoneda;
};

#endif // VISTAJUEGO_H
