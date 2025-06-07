#ifndef VISTASPLASH_H_INCLUDED
#define VISTASPLASH_H_INCLUDED
#pragma once
#include <SFML/Graphics.hpp>
#include "Vista.h"
#include "Juego.h"

namespace finalProg
{
    class VistaSplash : public Vista
    {
    public:

        VistaSplash(datosJuegoRef data);

        void init();
        void controlInput();
        void update(float dt);
        void draw(float dt);

    private:
        datosJuegoRef _data;
        sf::Clock _reloj;
        sf::Sprite _background;
    };
}


#endif // VISTASPLASH_H_INCLUDED
