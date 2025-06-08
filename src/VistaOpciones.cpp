#include "VistaOpciones.h"
#include "VistaMenu.h"
#include <iostream>

VistaOpciones::VistaOpciones()
    : seleccionActual(0), musicaActiva(true) {

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

    opciones = {
        "Musica: ON",
        "Instrucciones",
        "Volver al menu"
    };

    for (size_t i = 0; i < opciones.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(opciones[i]);
        text.setCharacterSize(35);
        text.setPosition(250, 250 + i * 60);
        textos.push_back(text);
    }

    if (!bufferCambio.loadFromFile("assets/sonidoCambio.ogg")) {
        std::cerr << "Error cargando sonidoCambio.ogg\n";
    }
    sonidoCambio.setBuffer(bufferCambio);

    actualizarColores();
}

void VistaOpciones::manejarEventos(sf::RenderWindow& ventana, Juego& juego) {
    sf::Event event;
    while (ventana.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            ventana.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                if (seleccionActual > 0) {
                    seleccionActual--;
                    sonidoCambio.play();
                    actualizarColores();
                }
            } else if (event.key.code == sf::Keyboard::Down) {
                if (seleccionActual < static_cast<int>(textos.size()) - 1) {
                    seleccionActual++;
                    sonidoCambio.play();
                    actualizarColores();
                }
            } else if (event.key.code == sf::Keyboard::Enter) {
                sonidoCambio.play();

                if (seleccionActual == 0) {
                    musicaActiva = !musicaActiva;
                    actualizarTextos();
                    if (musicaActiva)
                        juego.reproducirMusica();
                    else
                        juego.pausarMusica();

                } else if (seleccionActual == 1) {
                    std::cout << "Instrucciones:\n";
                    std::cout << "- Flechas izquierda/derecha para moverse\n";
                    std::cout << "- Barra espaciadora para saltar\n";
                    std::cout << "- Evita los obst�culos\n";

                } else if (seleccionActual == 2) {
                    juego.cambiarVista(new VistaMenu());
                }
            }
        }
    }
}

void VistaOpciones::actualizar(Juego& juego) {
    // No necesita actualizaci�n por ahora
}

void VistaOpciones::dibujar(sf::RenderWindow& ventana) {
    ventana.clear();
    ventana.draw(spriteFondo);
    for (const auto& texto : textos) {
        ventana.draw(texto);
    }
}

void VistaOpciones::actualizarTextos() {
    textos[0].setString("Musica: " + std::string(musicaActiva ? "ON" : "OFF"));
}

void VistaOpciones::actualizarColores() {
    for (size_t i = 0; i < textos.size(); ++i) {
        textos[i].setFillColor(i == (size_t)seleccionActual ? sf::Color::Yellow : sf::Color::White);
    }
}
