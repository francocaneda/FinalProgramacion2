#include "VistaMuerte.h"
#include "VistaMenu.h"
#include "VistaJuego.h"
#include <iostream>

VistaMuerte::VistaMuerte(int puntajeFinal)
    : seleccionActual(0), puntaje(puntajeFinal)  // Guardamos el puntaje
{
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

    // Opciones
    std::vector<std::string> textos = {
        "Volver al Menu",
        "Volver a Jugar",
        "Salir"
    };

    for (size_t i = 0; i < textos.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(textos[i]);
        text.setCharacterSize(35);
        text.setFillColor(sf::Color::White);
        text.setPosition(130, 420 + i * 60);
        opciones.push_back(text);
    }

    // Texto para mostrar el puntaje
    textoPuntaje.setFont(font);
    textoPuntaje.setCharacterSize(30);
    textoPuntaje.setFillColor(sf::Color::White);
    textoPuntaje.setPosition(930.f, 490.f);
    textoPuntaje.setString("Puntaje final: " + std::to_string(puntaje));

    actualizarColores();

    if (!bufferCambio.loadFromFile("assets/sonidoCambio.ogg")) {
        std::cerr << "Error cargando sonidoCambio.ogg\n";
    } else {
        sonidoCambio.setBuffer(bufferCambio);
    }
}

void VistaMuerte::manejarEventos(sf::RenderWindow& ventana, Juego& juego) {
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
                    sonidoCambio.play();
                }
            } else if (event.key.code == sf::Keyboard::Down) {
                if (seleccionActual < static_cast<int>(opciones.size()) - 1) {
                    seleccionActual++;
                    actualizarColores();
                    sonidoCambio.play();
                }
            } else if (event.key.code == sf::Keyboard::Enter) {
                sonidoCambio.play();

                if (seleccionActual == 0) {
                    juego.solicitarCambioVista(new VistaMenu());
                } else if (seleccionActual == 1) {
                    juego.solicitarCambioVista(new VistaJuego());
                } else if (seleccionActual == 2) {
                    ventana.close();
                }
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

    // Dibuja el texto del puntaje
    ventana.draw(textoPuntaje);

    for (const auto& opcion : opciones) {
        ventana.draw(opcion);
    }
}

void VistaMuerte::actualizarColores() {
    for (size_t i = 0; i < opciones.size(); ++i) {
        opciones[i].setFillColor(i == (size_t)seleccionActual ? sf::Color::Yellow : sf::Color::White);
    }
}
