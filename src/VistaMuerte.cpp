#include "VistaMuerte.h"
#include "VistaMenu.h"

VistaMuerte::VistaMuerte() : cambioVistaSolicitado(false) {
    font.loadFromFile("assets/fonts/arial.ttf");
    texto.setFont(font);
    texto.setString("GAME OVER\nPresiona ENTER para volver al menú");
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
    ventana.clear(sf::Color::Black);
    ventana.draw(texto);
}
