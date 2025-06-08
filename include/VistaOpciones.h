#ifndef VISTAOPCIONES_H
#define VISTAOPCIONES_H

#include "Vista.h"
#include "Juego.h"
#include <SFML/Graphics.hpp>
#include <vector>

class VistaOpciones : public Vista {
public:
    VistaOpciones();

    void manejarEventos(sf::RenderWindow& ventana, Juego& juego) override;
    void actualizar(Juego& juego) override;
    void dibujar(sf::RenderWindow& ventana) override;

private:
    sf::Font font;
    std::vector<std::string> opciones;
    std::vector<sf::Text> textos;
    int seleccionActual;

    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;

    bool musicaActiva;

    sf::SoundBuffer bufferCambio;
    sf::Sound sonidoCambio;

    void actualizarTextos();
    void actualizarColores();
};

#endif
