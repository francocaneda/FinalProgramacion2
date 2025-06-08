#include "VistaJuego.h"
#include "VistaMuerte.h"
#include "Moneda.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>  // Para rand()

VistaJuego::VistaJuego() {
    if (!texturaFondo.loadFromFile("assets/fondoJuego.png")) {
        std::cerr << "Error cargando fondoJuego.png\n";
    }

    spriteFondo.setTexture(texturaFondo);
    sf::Vector2u textureSize = texturaFondo.getSize();
    float scaleX = 1280.0f / textureSize.x;
    float scaleY = 720.0f / textureSize.y;
    spriteFondo.setScale(scaleX, scaleY);

    if (!texturaPersonaje.loadFromFile("assets/paloma.png")) {
        std::cerr << "Error cargando paloma.png\n";
    }

    if (!texturaRoca.loadFromFile("assets/roca.png")) {
        std::cerr << "Error cargando roca.png\n";
    }

    if (!texturaEnemigo.loadFromFile("assets/enemigo.png")) {
        std::cerr << "Error cargando enemigo.png\n";
    }

    if (!texturaMoneda.loadFromFile("assets/moneda.png")) {
        std::cerr << "Error cargando moneda.png\n";
    }

    personaje = new Personaje(texturaPersonaje, 100, 500);

    tiempoProximoSpawnRoca = 2.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 2.0f));
    tiempoProximoSpawnMoneda = 2.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 5.0f));

    relojGeneral.restart();
}

VistaJuego::~VistaJuego() {
    delete personaje;
    for (auto roca : rocas) delete roca;
    for (auto enemigo : enemigos) delete enemigo;
    for (auto moneda : monedas) delete moneda;
}

void VistaJuego::manejarEventos(sf::RenderWindow& ventana, Juego& juego) {
    sf::Event event;
    while (ventana.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            ventana.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) {
                personaje->saltar();
            }
        }
    }
}

void VistaJuego::actualizar(Juego& juego) {
    float velocidadHorizontal = 0.35f;
    float nuevaPosX = personaje->getPosX();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        nuevaPosX -= velocidadHorizontal;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        nuevaPosX += velocidadHorizontal;
    }

    if (nuevaPosX < 0) nuevaPosX = 0;
    if (nuevaPosX + personaje->getWidth() > 1280) nuevaPosX = 1280 - personaje->getWidth();

    personaje->setPosX(nuevaPosX);
    personaje->actualizar();

    // Spawn de rocas
    if (clockRocas.getElapsedTime().asSeconds() > tiempoProximoSpawnRoca) {
        float x = rand() % (1280 - 100);
        rocas.push_back(new Roca(texturaRoca, x));
        clockRocas.restart();
        tiempoProximoSpawnRoca = 2.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 2.0f));
    }

    // Spawn de enemigos
    if (clockEnemigos.getElapsedTime().asSeconds() > 2.5f) {
        enemigos.push_back(new Enemigo(texturaEnemigo, 1280));
        clockEnemigos.restart();
    }

    // Spawn de monedas con posiciones aleatorias en X: 50-1200, Y: 250-500
    if (clockMonedas.getElapsedTime().asSeconds() > tiempoProximoSpawnMoneda) {
        float x = 50 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (1100 - 50)));
        float y = 250 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (500 - 250)));
        float tiempoActual = relojGeneral.getElapsedTime().asSeconds();
        monedas.push_back(new Moneda(texturaMoneda, x, y, tiempoActual));
        clockMonedas.restart();
        tiempoProximoSpawnMoneda = 2.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 3.0f));
    }

    // Actualizar rocas
    for (auto roca : rocas) {
        roca->actualizar(0.13f);
    }

    // Actualizar enemigos
    for (auto enemigo : enemigos) {
        enemigo->actualizar();
    }

    // Verificar colisiones
    verificarColisiones(juego);

    // Limpiar rocas fuera de pantalla
    rocas.erase(std::remove_if(rocas.begin(), rocas.end(),
        [](Roca* roca) {
            if (roca->getPosY() > 720) {
                delete roca;
                return true;
            }
            return false;
        }), rocas.end());

    // Limpiar enemigos fuera de pantalla
    enemigos.erase(std::remove_if(enemigos.begin(), enemigos.end(),
        [](Enemigo* enemigo) {
            if (enemigo->getPosX() < -100) {
                delete enemigo;
                return true;
            }
            return false;
        }), enemigos.end());

    // Limpiar monedas que pasaron 2.5 segundos
    float tiempoActual = relojGeneral.getElapsedTime().asSeconds();
    monedas.erase(std::remove_if(monedas.begin(), monedas.end(),
        [tiempoActual](Moneda* moneda) {
            if (tiempoActual - moneda->getTiempoAparicion() > 2.5f) {
                delete moneda;
                return true;
            }
            return false;
        }), monedas.end());
}

void VistaJuego::dibujar(sf::RenderWindow& ventana) {
    ventana.clear();
    ventana.draw(spriteFondo);

    personaje->draw(ventana);

    for (auto roca : rocas) {
        roca->draw(ventana);
    }

    for (auto enemigo : enemigos) {
        enemigo->draw(ventana);
    }

    for (auto moneda : monedas) {
        moneda->draw(ventana);
    }
}

void VistaJuego::verificarColisiones(Juego& juego) {
    sf::FloatRect boundsPersonaje = personaje->getGlobalBounds();

    // Colisión con rocas
    for (auto roca : rocas) {
        if (boundsPersonaje.intersects(roca->getGlobalBounds())) {
            juego.cambiarVista(new VistaMuerte());
            return;
        }
    }

    // Colisión con enemigos
    for (auto enemigo : enemigos) {
        if (boundsPersonaje.intersects(enemigo->getGlobalBounds())) {
            juego.cambiarVista(new VistaMuerte());
            return;
        }
    }

    // Colisión con monedas
    monedas.erase(std::remove_if(monedas.begin(), monedas.end(),
        [boundsPersonaje](Moneda* moneda) {
            if (boundsPersonaje.intersects(moneda->getGlobalBounds())) {
                delete moneda;
                return true;
            }
            return false;
        }), monedas.end());
}
