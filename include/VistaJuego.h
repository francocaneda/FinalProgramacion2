#ifndef VISTAJUEGO_H
#define VISTAJUEGO_H

#include "Vista.h"
#include "Juego.h"
#include "Personaje.h" // Incluimos Personaje
#include "PersonajeSecundario.h" // Incluimos PersonajeSecundario
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

    sf::Texture texturaPersonaje; // Textura para el personaje principal
    sf::Texture texturaPersonajeSecundario; // Nueva textura para el personaje secundario (opcional, puedes usar la misma)
    sf::Texture texturaRoca;
    sf::Texture texturaEnemigo;
    sf::Texture texturaMoneda;

    Personaje* personajePrincipal; // Renombrado
    PersonajeSecundario* personajeSecundario; // Nuevo objeto

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

    // --- Nuevos atributos para el mensaje de muerte ---
    sf::Text textoMensajeMuerte;
    sf::Clock relojMensajeMuerte; // Controla cuánto tiempo se muestra el mensaje
    float duracionMensajeMuerte = 1.0f; // Duración del mensaje en segundos
    bool mostrarMensajeMuerte = false;  // Bandera para controlar si se dibuja el mensaje
    // ---------------------------------------------------

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
