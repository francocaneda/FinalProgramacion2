#include "VistaMenu.h"
#include "VistaJuego.h"
#include "VistaOpciones.h"
#include <iostream>

VistaMenu::VistaMenu() {
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        std::cerr << "Error cargando la fuente arial.ttf\n";
    }

    if (!texturaFondo.loadFromFile("assets/fondoMenu.png")) {
        std::cerr << "Error cargando fondoMenu.png\n";
    }
    spriteFondo.setTexture(texturaFondo);

    // Ajustar tama�o a 1280x720
    sf::Vector2u textureSize = texturaFondo.getSize();
    float scaleX = 1280.0f / textureSize.x;
    float scaleY = 720.0f / textureSize.y;
    spriteFondo.setScale(scaleX, scaleY);

    std::vector<std::string> textos = { "Play", "Opciones", "Salir" };

    for (size_t i = 0; i < textos.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(textos[i]);
        text.setCharacterSize(40);
        text.setPosition(500, 250 + i * 60);
        opciones.push_back(text);
    }

    actualizarColores();
}

void VistaMenu::manejarEventos(sf::RenderWindow& ventana, Juego& juego) {
    sf::Event event;
    while (ventana.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            ventana.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                if (seleccionActual > 0) {
                    seleccionActual--;
                    actualizarColores();
                }
            }
            else if (event.key.code == sf::Keyboard::Down) {
                if (seleccionActual < static_cast<int>(opciones.size()) - 1) {
                    seleccionActual++;
                    actualizarColores();
                }
            }
            else if (event.key.code == sf::Keyboard::Enter) {
                if (seleccionActual == 0) { // Play
                    juego.cambiarVista(new VistaJuego());
                }
                else if (seleccionActual == 1) { // Opciones
                    juego.cambiarVista(new VistaOpciones());
                }
                else if (seleccionActual == 2) { // Salir
                    ventana.close();
                }
            }
        }
    }
}

void VistaMenu::actualizar(Juego& juego) {
    // Nada por ahora
}

void VistaMenu::dibujar(sf::RenderWindow& ventana) {
    ventana.clear();

    ventana.draw(spriteFondo);

    for (const auto& opcion : opciones) {
        ventana.draw(opcion);
    }
}

void VistaMenu::actualizarColores() {
    for (size_t i = 0; i < opciones.size(); ++i) {
        if (static_cast<int>(i) == seleccionActual) {
            opciones[i].setFillColor(sf::Color::Yellow);
        } else {
            opciones[i].setFillColor(sf::Color::White);
        }
    }
}
