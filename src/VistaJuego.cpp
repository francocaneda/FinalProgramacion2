#include "VistaJuego.h"
#include "VistaMuerte.h"
#include "Juego.h"
#include <cstdlib> // para rand()
#include <ctime>   // para time()

VistaJuego::VistaJuego() {
    srand(static_cast<unsigned int>(time(nullptr)));

    if (!texturaPersonaje.loadFromFile("./assets/paloma.png")) {
        // Manejar error
    }
    personaje = new Personaje(texturaPersonaje, 100, 500);

    if (!texturaRoca.loadFromFile("./assets/roca.png")) {
        // Manejar error
    }

    if (!texturaEnemigo.loadFromFile("./assets/enemigo.png")) {
        // Manejar error
    }

    tiempoProximaAparicionEnemigo = 2.0f + static_cast<float>(rand()) / RAND_MAX * 3.0f;
}

VistaJuego::~VistaJuego() {
    delete personaje;

    for (auto roca : rocas) {
        delete roca;
    }
    rocas.clear();

    for (auto enemigo : enemigos) {
        delete enemigo;
    }
    enemigos.clear();
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
    // Movimiento lateral personaje
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (personaje->getPosX() > 0) {
            personaje->move(-0.2f);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (personaje->getPosX() + personaje->getWidth() < 1280) {
            personaje->move(0.2f);
        }
    }

    personaje->actualizar();

    // SPAWN ROCA
    if (relojRoca.getElapsedTime().asSeconds() >= 2.5f) {
        spawnRoca();
        relojRoca.restart();
    }

    // ACTUALIZAR ROCAS
    for (size_t i = 0; i < rocas.size(); ++i) {
        rocas[i]->actualizar(0.13f); // velocidad lenta de caída

        if (chequearColision(personaje, rocas[i])) {
            juego.cambiarVista(new VistaMuerte());
            return;
        }

        if (rocas[i]->getPosY() > 720) {
            delete rocas[i];
            rocas.erase(rocas.begin() + i);
            --i;
        }
    }

    // SPAWN ENEMIGO
    if (relojEnemigo.getElapsedTime().asSeconds() >= tiempoProximaAparicionEnemigo) {
        spawnEnemigo();
        relojEnemigo.restart();
        tiempoProximaAparicionEnemigo = 2.0f + static_cast<float>(rand()) / RAND_MAX * 3.0f;
    }

    // ACTUALIZAR ENEMIGOS
    for (size_t i = 0; i < enemigos.size(); ++i) {
        enemigos[i]->actualizar(0.25f); // velocidad horizontal

        if (chequearColision(personaje, enemigos[i])) {
            juego.cambiarVista(new VistaMuerte());
            return;
        }

        if (enemigos[i]->getPosX() < -enemigos[i]->getGlobalBounds().width) {
            delete enemigos[i];
            enemigos.erase(enemigos.begin() + i);
            --i;
        }
    }
}

void VistaJuego::dibujar(sf::RenderWindow& ventana) {
    ventana.clear(sf::Color::Black);

    personaje->draw(ventana);

    for (auto roca : rocas) {
        roca->draw(ventana);
    }

    for (auto enemigo : enemigos) {
        enemigo->draw(ventana);
    }
}

void VistaJuego::spawnRoca() {
    float x = static_cast<float>(rand() % 1200 + 40); // evitar bordes
    Roca* roca = new Roca(texturaRoca, x);
    rocas.push_back(roca);
}

void VistaJuego::spawnEnemigo() {
    Enemigo* enemigo = new Enemigo(texturaEnemigo, 1280); // spawnea derecha
    enemigos.push_back(enemigo);
}

bool VistaJuego::chequearColision(Personaje* personaje, Roca* roca) {
    return personaje->getGlobalBounds().intersects(roca->getGlobalBounds());
}

bool VistaJuego::chequearColision(Personaje* personaje, Enemigo* enemigo) {
    return personaje->getGlobalBounds().intersects(enemigo->getGlobalBounds());
}
