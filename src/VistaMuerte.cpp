#include "VistaMuerte.h"
#include "VistaMenu.h"
#include <iostream>

VistaMuerte::VistaMuerte() : cambioVistaSolicitado(false) {
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        std::cerr << "Error cargando la fuente arial.ttf\n";
    }

    if (!texturaFondo.loadFromFile("assets/fondoMuerte.png")) {
        std::cerr << "Error cargando fondoMuerte.png\n";
    }

    spriteFondo.setTexture(texturaFondo);

    sf::Vector2u textureSize = texturaFondo.getSize();
    float scaleX = 1280.0f / textureSize.x;
    float scaleY = 720.0f / textureSize.y;
    spriteFondo.setScale(scaleX, scaleY);

    texto.setFont(font);
    texto.setString("GAME OVER\nPresiona ENTER para volver al menu");
    texto.setCharacterSize(30);
    texto.setFillColor(sf::Color::Red);
    texto.setPosition(200, 300);
}

void VistaMuerte::manejarEventos(sf::RenderWindow& ventana, Juego& juego) {
    sf::Event event;
    while (ventana.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            ventana.close();
        }

        if (!cambioVistaSolicitado && event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter) {
                cambioVistaSolicitado = true;
                juego.cambiarVista(new VistaMenu());
            }
        }
    }
}

void VistaMuerte::actualizar(Juego& juego) {
    // Nada por ahora
}

void VistaMuerte::dibujar(sf::RenderWindow& ventana) {
    ventana.clear();
    ventana.draw(spriteFondo);
    ventana.draw(texto);
}
