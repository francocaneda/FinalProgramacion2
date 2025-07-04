#include "VistaJuego.h"
#include "VistaMuerte.h"
#include "Moneda.h"
#include <iostream>
#include <algorithm>
#include <cstdlib> // Para rand()

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

    if (!texturaPersonajeSecundario.loadFromFile("assets/personajeSecundario.png"))
        std::cerr << "Error cargando personajeSecundario.png\n"; // Mensaje de error actualizado

    if (!texturaRoca.loadFromFile("assets/roca.png"))
        std::cerr << "Error cargando roca.png\n";
    if (!texturaEnemigo.loadFromFile("assets/enemigo.png"))
        std::cerr << "Error cargando enemigo.png\n";
    if (!texturaMoneda.loadFromFile("assets/moneda.png"))
        std::cerr << "Error cargando moneda.png\n";

    if (!fuente.loadFromFile("assets/fonts/arial.ttf")) // Ruta corregida si usas assets/fonts/
        std::cerr << "Error cargando fuente arial.ttf\n";

    if (!bufferMoneda.loadFromFile("assets/moneda.ogg"))
        std::cerr << "Error cargando sonido moneda.ogg\n";
    sonidoMoneda.setBuffer(bufferMoneda);

    // Instanciamos ambos personajes
    personajePrincipal = new Personaje(texturaPersonaje, 100, 500);
    personajeSecundario = new PersonajeSecundario(texturaPersonajeSecundario, 100, 500);

    tiempoProximoSpawnRoca = 2.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 2.0f));
    tiempoProximoSpawnMoneda = 2.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 2.0f)); // Corregido a 2.0f/2.0f para coincidir con tu código
    relojGeneral.restart();

    puntos = 0;
    monedasConsecutivas = 0;

    textoPuntos.setFont(fuente);
    textoPuntos.setCharacterSize(30);
    textoPuntos.setFillColor(sf::Color::White);
    textoPuntos.setPosition(15.f, 15.f);
    textoPuntos.setString("Puntos: 0");

    // --- Inicialización del mensaje de muerte ---
    textoMensajeMuerte.setFont(fuente);
    textoMensajeMuerte.setCharacterSize(40);
    textoMensajeMuerte.setFillColor(sf::Color::Green);
    // Posicionar en el centro superior (esto puede requerir ajustar el X según la longitud del texto)
    textoMensajeMuerte.setPosition(1280 / 2.f, 50.f);
    // Centrar el origen del texto para que el posicionamiento sea por el centro del texto
    // El setOrigin debe hacerse DESPUÉS de setString si el tamaño del texto cambia,
    // o se puede hacer una vez y asumir que la longitud del texto es similar.
    // Lo haremos en verificarColisiones para re-centrar bien cada vez.
    mostrarMensajeMuerte = false; // Por defecto no se muestra
    // ----------------------------------------------
}

VistaJuego::~VistaJuego() {
    delete personajePrincipal;
    delete personajeSecundario;
    for (auto r : rocas) delete r;
    for (auto e : enemigos) delete e;
    for (auto m : monedas) delete m;
}

void VistaJuego::manejarEventos(sf::RenderWindow& ventana, Juego& juego) {
    sf::Event event;
    while (ventana.pollEvent(event)) {
        if (event.type == sf::Event::Closed) ventana.close();

        // Control del personaje principal (flecha ARRIBA para saltar)
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
            if (personajePrincipal->estaVivo()) { // Solo si está vivo
                personajePrincipal->saltar();
            }
        }
        // Control del personaje secundario (W para saltar)
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W) {
            if (personajeSecundario->estaVivo()) { // Solo si está vivo
                personajeSecundario->saltar();
            }
        }
    }
}

void VistaJuego::actualizar(Juego& juego) {
    float velocidadHorizontal = 0.35f;

    // Actualizar personaje principal (flechas IZQUIERDA/DERECHA)
    if (personajePrincipal->estaVivo()) {
        float nuevaPosXPrincipal = personajePrincipal->getPosX();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) nuevaPosXPrincipal -= velocidadHorizontal;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) nuevaPosXPrincipal += velocidadHorizontal;
        if (nuevaPosXPrincipal < 0) nuevaPosXPrincipal = 0;
        if (nuevaPosXPrincipal + personajePrincipal->getWidth() > 1280) nuevaPosXPrincipal = 1280 - personajePrincipal->getWidth();
        personajePrincipal->setPosX(nuevaPosXPrincipal);
        personajePrincipal->actualizar();
    }

    // Actualizar personaje secundario (A/D)
    if (personajeSecundario->estaVivo()) {
        float nuevaPosXSecundario = personajeSecundario->getPosX();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) nuevaPosXSecundario -= velocidadHorizontal;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) nuevaPosXSecundario += velocidadHorizontal;
        if (nuevaPosXSecundario < 0) nuevaPosXSecundario = 0;
        if (nuevaPosXSecundario + personajeSecundario->getWidth() > 1280) nuevaPosXSecundario = 1280 - personajeSecundario->getWidth();
        personajeSecundario->setPosX(nuevaPosXSecundario);
        personajeSecundario->actualizar();
    }

    // Spawns (mantener igual)
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

    // Colisiones
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

    // --- Lógica del mensaje de muerte ---
    if (mostrarMensajeMuerte && relojMensajeMuerte.getElapsedTime().asSeconds() > duracionMensajeMuerte) {
        mostrarMensajeMuerte = false; // Desactivar el mensaje después de la duración
    }
    // -------------------------------------
}

void VistaJuego::dibujar(sf::RenderWindow& ventana) {
    ventana.clear();
    ventana.draw(spriteFondo);

    // Dibujar personajes solo si están vivos
    if (personajePrincipal->estaVivo()) {
        personajePrincipal->draw(ventana);
    }
    if (personajeSecundario->estaVivo()) {
        personajeSecundario->draw(ventana);
    }

    for (auto r : rocas) r->draw(ventana);
    for (auto e : enemigos) e->draw(ventana);
    for (auto m : monedas) m->draw(ventana);
    ventana.draw(textoPuntos);

    // --- Dibujar el mensaje de muerte si está activo ---
    if (mostrarMensajeMuerte) {
        ventana.draw(textoMensajeMuerte);
    }
    // --------------------------------------------------
}

void VistaJuego::verificarColisiones(Juego& juego) {
    bool personajePrincipalMuerto = false;
    bool personajeSecundarioMuerto = false;

    // Colisiones de personaje principal
    if (personajePrincipal->estaVivo()) {
        sf::FloatRect boundsPersonajePrincipal = personajePrincipal->getGlobalBounds();
        for (auto r : rocas) {
            if (boundsPersonajePrincipal.intersects(r->getGlobalBounds())) {
                personajePrincipal->morir();
                personajePrincipalMuerto = true;
                // Mostrar mensaje de muerte para el personaje principal
                textoMensajeMuerte.setString("Isaac ha muerto!");
                textoMensajeMuerte.setOrigin(textoMensajeMuerte.getLocalBounds().width / 2.f, textoMensajeMuerte.getLocalBounds().height / 2.f); // Re-centrar
                mostrarMensajeMuerte = true;
                relojMensajeMuerte.restart(); // Iniciar el temporizador
                break; // Ya colisionó, no necesita verificar más rocas
            }
        }
        if (!personajePrincipalMuerto) { // Si no murió con roca, verificar enemigos
            for (auto e : enemigos) {
                if (boundsPersonajePrincipal.intersects(e->getGlobalBounds())) {
                    personajePrincipal->morir();
                    personajePrincipalMuerto = true;
                    // Mostrar mensaje de muerte para el personaje principal
                    textoMensajeMuerte.setString("Isaac ha muerto!");
                    textoMensajeMuerte.setOrigin(textoMensajeMuerte.getLocalBounds().width / 2.f, textoMensajeMuerte.getLocalBounds().height / 2.f); // Re-centrar
                    mostrarMensajeMuerte = true;
                    relojMensajeMuerte.restart();
                    break;
                }
            }
        }
    } else {
        personajePrincipalMuerto = true; // Ya estaba muerto
    }

    // Colisiones de personaje secundario
    if (personajeSecundario->estaVivo()) {
        sf::FloatRect boundsPersonajeSecundario = personajeSecundario->getGlobalBounds();
        for (auto r : rocas) {
            if (boundsPersonajeSecundario.intersects(r->getGlobalBounds())) {
                personajeSecundario->morir();
                personajeSecundarioMuerto = true;
                // Mostrar mensaje de muerte para el personaje secundario
                textoMensajeMuerte.setString("Diabolin ha muerto!");
                textoMensajeMuerte.setOrigin(textoMensajeMuerte.getLocalBounds().width / 2.f, textoMensajeMuerte.getLocalBounds().height / 2.f); // Re-centrar
                mostrarMensajeMuerte = true;
                relojMensajeMuerte.restart();
                break;
            }
        }
        if (!personajeSecundarioMuerto) { // Si no murió con roca, verificar enemigos
            for (auto e : enemigos) {
                if (boundsPersonajeSecundario.intersects(e->getGlobalBounds())) {
                    personajeSecundario->morir();
                    personajeSecundarioMuerto = true;
                    // Mostrar mensaje de muerte para el personaje secundario
                    textoMensajeMuerte.setString("Diabolin ha muerto!");
                    textoMensajeMuerte.setOrigin(textoMensajeMuerte.getLocalBounds().width / 2.f, textoMensajeMuerte.getLocalBounds().height / 2.f); // Re-centrar
                    mostrarMensajeMuerte = true;
                    relojMensajeMuerte.restart();
                    break;
                }
            }
        }
    } else {
        personajeSecundarioMuerto = true; // Ya estaba muerto
    }

    // Colisiones con monedas (para ambos personajes, si están vivos)
    // Uso un remove_if con lambda para eliminar monedas y sumar puntos
    monedas.erase(std::remove_if(monedas.begin(), monedas.end(), [this](Moneda* m) {
        bool colisionConPrincipal = false;
        if (personajePrincipal->estaVivo()) {
            colisionConPrincipal = personajePrincipal->getGlobalBounds().intersects(m->getGlobalBounds());
        }

        bool colisionConSecundario = false;
        if (personajeSecundario->estaVivo()) {
            colisionConSecundario = personajeSecundario->getGlobalBounds().intersects(m->getGlobalBounds());
        }

        if (colisionConPrincipal || colisionConSecundario) {
            monedasConsecutivas++;
            puntos += 10;
            if (monedasConsecutivas == 3) {
                puntos += 30;
                monedasConsecutivas = 0;
            }
            textoPuntos.setString("Puntos: " + std::to_string(puntos));
            sonidoMoneda.play();
            delete m;
            return true; // Eliminar la moneda
        }
        return false;
    }), monedas.end());

    // Verificar condición de fin de juego: ambos personajes muertos
    if (personajePrincipalMuerto && personajeSecundarioMuerto) {
        juego.setPuntajeFinal(puntos);
        juego.solicitarCambioVista(new VistaMuerte(puntos));
    }
}
