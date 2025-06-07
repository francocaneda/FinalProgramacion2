#include "VistaJuego.h"
#include "VistaMuerte.h"
#include <iostream>
#include <algorithm>  // para std::remove_if

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
        std::cerr << "Error cargando personaje.png\n";
    }

    if (!texturaRoca.loadFromFile("assets/roca.png")) {
        std::cerr << "Error cargando roca.png\n";
    }

    if (!texturaEnemigo.loadFromFile("assets/enemigo.png")) {
        std::cerr << "Error cargando enemigo.png\n";
    }

    personaje = new Personaje(texturaPersonaje, 100, 500);
    tiempoProximoSpawnRoca = 2.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(2.0f))); // primer spawn aleatorio entre 2 y 4 seg
}

VistaJuego::~VistaJuego() {
    delete personaje;
    for (auto roca : rocas) delete roca;
    for (auto enemigo : enemigos) delete enemigo;
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
    // Movimiento horizontal lento con límites
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

    // Actualizar salto y demás
    personaje->actualizar();

    // Spawn de rocas con tiempo variable entre 2 y 4 segundos
    if (clockRocas.getElapsedTime().asSeconds() > tiempoProximoSpawnRoca) {
        float x = rand() % (1280 - 100);
        rocas.push_back(new Roca(texturaRoca, x));
        clockRocas.restart();

        // Setear próximo spawn aleatorio entre 2 y 4 segundos
        tiempoProximoSpawnRoca = 2.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(2.0f)));
    }

    // Spawn de enemigos cada 2.5 seg
    if (clockEnemigos.getElapsedTime().asSeconds() > 2.5f) {
        enemigos.push_back(new Enemigo(texturaEnemigo, 1280));
        clockEnemigos.restart();
    }

    // Actualizar rocas
    for (size_t i = 0; i < rocas.size(); ++i) {
        rocas[i]->actualizar(0.13f);
    }

    // Actualizar enemigos
    for (size_t i = 0; i < enemigos.size(); ++i) {
        enemigos[i]->actualizar(0.25f);
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
}
