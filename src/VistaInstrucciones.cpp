#include "VistaInstrucciones.h"
#include "VistaOpciones.h"
#include <iostream>

VistaInstrucciones::VistaInstrucciones() : seleccionActual(0) {
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        std::cerr << "Error cargando fuente arial.ttf\n";
    }

    if (!texturaFondo.loadFromFile("assets/fondoMenu.png")) {
        std::cerr << "Error cargando fondoMenu.png\n";
    }

    spriteFondo.setTexture(texturaFondo);
    sf::Vector2u textureSize = texturaFondo.getSize();
    float scaleX = 1280.0f / textureSize.x;
    float scaleY = 720.0f / textureSize.y;
    spriteFondo.setScale(scaleX, scaleY);

    textoInstrucciones.setFont(font);
    textoInstrucciones.setString(
        "INSTRUCCIONES:\n\n"
        "- Usa las FLECHAS izquierda/derecha para moverte.\n"
        "- Usa ESPACIO para saltar.\n"
        "- Evita las bombas que caen y los enemigos.\n"
        "- Recoge la mayor cantidad de monedas.\n"
        "- 1 moneda = 10 puntos.\n"
        "- 3 monedas consecutivas = bonus 30 pts."
    );
    textoInstrucciones.setCharacterSize(30);
    textoInstrucciones.setFillColor(sf::Color::White);
    textoInstrucciones.setPosition(100, 200);

    textoVolver.setFont(font);
    textoVolver.setString("Volver a Opciones");
    textoVolver.setCharacterSize(30);
    textoVolver.setPosition(100, 550);

    if (!bufferCambio.loadFromFile("assets/sonidoCambio.ogg")) {
        std::cerr << "Error cargando sonidoCambio.ogg\n";
    }
    sonidoCambio.setBuffer(bufferCambio);

    actualizarColores();
}

void VistaInstrucciones::manejarEventos(sf::RenderWindow& ventana, Juego& juego) {
    sf::Event event;
    while (ventana.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            ventana.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Escape) {
                sonidoCambio.play();
                juego.solicitarCambioVista(new VistaOpciones());
            }
        }
    }
}

void VistaInstrucciones::actualizar(Juego& juego) {
    // Nada por actualizar
}

void VistaInstrucciones::dibujar(sf::RenderWindow& ventana) {
    ventana.clear();
    ventana.draw(spriteFondo);
    ventana.draw(textoInstrucciones);
    ventana.draw(textoVolver);
}

void VistaInstrucciones::actualizarColores() {
    textoVolver.setFillColor(sf::Color::Yellow);
}

