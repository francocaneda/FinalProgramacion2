#include "VistaOpciones.h"
#include "VistaMenu.h"
#include <iostream>

VistaOpciones::VistaOpciones() {
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        std::cerr << "Error cargando la fuente arial.ttf\n";
    }

    if (!texturaFondo.loadFromFile("assets/fondoOpciones.png")) {
        std::cerr << "Error cargando fondoOpciones.png\n";
    }

    if (!bufferCambio.loadFromFile("assets/sonidoCambio.ogg")) {
        std::cerr << "Error cargando sonidoCambio.ogg\n";
    } else {
        sonidoCambio.setBuffer(bufferCambio);
    }

    spriteFondo.setTexture(texturaFondo);

    sf::Vector2u textureSize = texturaFondo.getSize();
    float scaleX = 1280.0f / textureSize.x;
    float scaleY = 720.0f / textureSize.y;
    spriteFondo.setScale(scaleX, scaleY);

    std::vector<std::string> textos = {
        "Musica: ON",
        "Mostrar controles",
        "Ver creditos",
        "Volver al menu"
    };

    for (size_t i = 0; i < textos.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(textos[i]);
        text.setCharacterSize(35);
        text.setPosition(250, 250 + i * 60);
        opciones.push_back(text);
    }

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
                if (seleccionActual == 0) {
                    // Alternar música ON/OFF
                    musicaActiva = !musicaActiva;
                    actualizarTextos();
                } else if (seleccionActual == 1) {
                    // Alternar mostrar controles
                    mostrarControles = !mostrarControles;
                    std::cout << "Mostrar controles: " << (mostrarControles ? "SI" : "NO") << std::endl;
                } else if (seleccionActual == 2) {
                    // Mostrar créditos
                    std::cout << "Juego creado por TuNombre - 2025" << std::endl;
                } else if (seleccionActual == 3) {
                    // Volver al menú
                    juego.cambiarVista(new VistaMenu());
                }
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
    for (const auto& opcion : opciones) {
        ventana.draw(opcion);
    }
}

void VistaOpciones::actualizarTextos() {
    opciones[0].setString("Musica: " + std::string(musicaActiva ? "ON" : "OFF"));
}

void VistaOpciones::actualizarColores() {
    for (size_t i = 0; i < opciones.size(); ++i) {
        if (static_cast<int>(i) == seleccionActual) {
            opciones[i].setFillColor(sf::Color::Yellow);
        } else {
            opciones[i].setFillColor(sf::Color::White);
        }
    }
}
