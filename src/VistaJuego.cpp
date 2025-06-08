#include "VistaJuego.h"
#include "VistaMuerte.h"
#include "Moneda.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>

VistaJuego::VistaJuego() {
    if (!texturaFondo.loadFromFile("assets/fondoJuego.png"))
        std::cerr << "Error cargando fondoJuego.png\n";

    spriteFondo.setTexture(texturaFondo);
    sf::Vector2u textureSize = texturaFondo.getSize();
    float scaleX = 1280.0f / textureSize.x;
    float scaleY = 720.0f / textureSize.y;
    spriteFondo.setScale(scaleX, scaleY);

    if (!texturaPersonaje.loadFromFile("assets/paloma.png"))
        std::cerr << "Error cargando paloma.png\n";
    if (!texturaRoca.loadFromFile("assets/roca.png"))
        std::cerr << "Error cargando roca.png\n";
    if (!texturaEnemigo.loadFromFile("assets/enemigo.png"))
        std::cerr << "Error cargando enemigo.png\n";
    if (!texturaMoneda.loadFromFile("assets/moneda.png"))
        std::cerr << "Error cargando moneda.png\n";

    if (!fuente.loadFromFile("assets/fonts/arial.ttf"))
        std::cerr << "Error cargando fuente arial.ttf\n";

    if (!bufferMoneda.loadFromFile("assets/moneda.ogg"))
        std::cerr << "Error cargando sonido moneda.ogg\n";
    sonidoMoneda.setBuffer(bufferMoneda);

    personaje = new Personaje(texturaPersonaje, 100, 500);

    tiempoProximoSpawnRoca = 2.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 2.0f));
    tiempoProximoSpawnMoneda = 2.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 3.0f));
    relojGeneral.restart();

    puntos = 0;
    monedasConsecutivas = 0;

    textoPuntos.setFont(fuente);
    textoPuntos.setCharacterSize(30);
    textoPuntos.setFillColor(sf::Color::White);
    textoPuntos.setPosition(15.f, 15.f);
    textoPuntos.setString("Puntos: 0");
}

VistaJuego::~VistaJuego() {
    delete personaje;
    for (auto r : rocas) delete r;
    for (auto e : enemigos) delete e;
    for (auto m : monedas) delete m;
}

void VistaJuego::manejarEventos(sf::RenderWindow& ventana, Juego& juego) {
    sf::Event event;
    while (ventana.pollEvent(event)) {
        if (event.type == sf::Event::Closed) ventana.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            personaje->saltar();
    }
}

void VistaJuego::actualizar(Juego& juego) {
    float velocidadHorizontal = 0.35f;
    float nuevaPosX = personaje->getPosX();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) nuevaPosX -= velocidadHorizontal;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) nuevaPosX += velocidadHorizontal;
    if (nuevaPosX < 0) nuevaPosX = 0;
    if (nuevaPosX + personaje->getWidth() > 1280) nuevaPosX = 1280 - personaje->getWidth();

    personaje->setPosX(nuevaPosX);
    personaje->actualizar();

    // Spawns
    if (clockRocas.getElapsedTime().asSeconds() > tiempoProximoSpawnRoca) {
        float x = rand() % (1280 - 100);
        rocas.push_back(new Roca(texturaRoca, x));
        clockRocas.restart();
        tiempoProximoSpawnRoca = 2.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 2.0f));
    }

    if (clockEnemigos.getElapsedTime().asSeconds() > 2.5f) {
        enemigos.push_back(new Enemigo(texturaEnemigo, 1280));
        clockEnemigos.restart();
    }

    if (clockMonedas.getElapsedTime().asSeconds() > tiempoProximoSpawnMoneda) {
        float x = 50 + rand() % (1100 - 50);
        float y = 250 + rand() % (500 - 250);
        float tiempoActual = relojGeneral.getElapsedTime().asSeconds();
        Moneda* moneda = new Moneda(texturaMoneda, x, y, tiempoActual);
        moneda->setScale(0.05f, 0.05f);
        monedas.push_back(moneda);
        clockMonedas.restart();
        tiempoProximoSpawnMoneda = 2.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 3.0f));
    }

    for (auto r : rocas) r->actualizar(0.13f);
    for (auto e : enemigos) e->actualizar();

    verificarColisiones(juego);

    rocas.erase(std::remove_if(rocas.begin(), rocas.end(), [](Roca* r) {
        if (r->getPosY() > 720) { delete r; return true; }
        return false;
    }), rocas.end());

    enemigos.erase(std::remove_if(enemigos.begin(), enemigos.end(), [](Enemigo* e) {
        if (e->getPosX() < -100) { delete e; return true; }
        return false;
    }), enemigos.end());

    float tiempoActual = relojGeneral.getElapsedTime().asSeconds();
    monedas.erase(std::remove_if(monedas.begin(), monedas.end(), [this, tiempoActual](Moneda* m) {
        if (tiempoActual - m->getTiempoAparicion() > 2.5f) {
            delete m;
            monedasConsecutivas = 0;  // Reinicia si no la agarró
            return true;
        }
        return false;
    }), monedas.end());
}

void VistaJuego::dibujar(sf::RenderWindow& ventana) {
    ventana.clear();
    ventana.draw(spriteFondo);
    personaje->draw(ventana);
    for (auto r : rocas) r->draw(ventana);
    for (auto e : enemigos) e->draw(ventana);
    for (auto m : monedas) m->draw(ventana);
    ventana.draw(textoPuntos);
}

void VistaJuego::verificarColisiones(Juego& juego) {
    sf::FloatRect boundsPersonaje = personaje->getGlobalBounds();

    for (auto r : rocas) {
        if (boundsPersonaje.intersects(r->getGlobalBounds())) {
            juego.setPuntajeFinal(puntos);
            juego.solicitarCambioVista(new VistaMuerte(puntos));
            return;
        }
    }

    for (auto e : enemigos) {
        if (boundsPersonaje.intersects(e->getGlobalBounds())) {
            juego.setPuntajeFinal(puntos);
            juego.solicitarCambioVista(new VistaMuerte(puntos));
            return;
        }
    }

    monedas.erase(std::remove_if(monedas.begin(), monedas.end(), [this, &boundsPersonaje](Moneda* m) {
        if (boundsPersonaje.intersects(m->getGlobalBounds())) {
            monedasConsecutivas++;
            puntos += 10;
            if (monedasConsecutivas == 3) {
                puntos += 30;
                monedasConsecutivas = 0;
            }
            textoPuntos.setString("Puntos: " + std::to_string(puntos));
            sonidoMoneda.play();
            delete m;
            return true;
        }
        return false;
    }), monedas.end());
}
