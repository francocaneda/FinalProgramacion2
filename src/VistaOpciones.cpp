#include "VistaOpciones.h"
#include "VistaMenu.h"
#include <iostream>

VistaOpciones::VistaOpciones() {
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        std::cerr << "Error cargando la fuente arial.ttf\n";
    }

    if (!texturaFondo.loadFromFile("assets/fondoMenu.png")) {
        std::cerr << "Error cargando fondoMenu.png\n";
    }
    spriteFondo.setTexture(texturaFondo);

    sf::Vector2u textureSize = texturaFondo.getSize();
    float scaleX = 1280.0f / textureSize.x;
    float scaleY = 720.0f / textureSize.y;
    spriteFondo.setScale(scaleX, scaleY);

    texto.setFont(font);
    texto.setString("OPCIONES\nPresiona ESC para volver al menu");
    texto.setCharacterSize(30);
    texto.setFillColor(sf::Color::White);
    texto.setPosition(200, 300);
}

void VistaOpciones::manejarEventos(sf::RenderWindow& ventana, Juego& juego) {
    sf::Event event;
    while (ventana.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            ventana.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                juego.cambiarVista(new VistaMenu());
            }
        }
    }
}

void VistaOpciones::actualizar(Juego& juego) {
    // Nada por ahora
}

void VistaOpciones::dibujar(sf::RenderWindow& ventana) {
    ventana.clear();
    ventana.draw(spriteFondo);
    ventana.draw(texto);
}
