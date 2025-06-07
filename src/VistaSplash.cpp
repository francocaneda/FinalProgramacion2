#pragma once
#include <sstream>
#include "VistaSplash.h"
#include "VistaMenu.h"
#include <iostream>

namespace finalProg
{
    VistaSplash::VistaSplash(datosJuegoRef data) : _data(data)
    {
    }

    void VistaSplash::init()
    {
        this->_data->recursos.cargarTextura("Vista Splash Background", "./assets/fondo.png");
        this->_background.setTexture(this->_data->recursos.getTextura("Vista Splash Background"));
    }

    void VistaSplash::controlInput()
    {
        sf::Event ev;

        while(this->_data->ventana.pollEvent(ev))
        {
            if(sf::Event::Closed == ev.type)
            {
                this->_data->ventana.close();
            }
        }
    }

    void VistaSplash::update(float dt)
    {
        if(this->_reloj.getElapsedTime().asSeconds() > VISTA_SPLASH_TIME)
        {
            _data->controlVista.agregarVista(vistaRef (new VistaMenu(this->_data)), true);
        }
    }

    void VistaSplash::draw(float dt)
    {
        this->_data->ventana.clear();
        this->_data->ventana.draw(this->_background);
        this->_data->ventana.display();
    }
}
