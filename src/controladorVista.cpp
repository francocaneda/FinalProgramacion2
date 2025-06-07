#include "controladorVista.h"

namespace finalProg
{
    void controladorVista::agregarVista(vistaRef nuevaVista, bool estaReemplazando)
    {
        this->_estaAgregando = true;
        this->_estaReemplazando = estaReemplazando;
        this->_nuevaVista = std::move(nuevaVista);
    }

    void controladorVista::sacarVista()
    {
        this->_estaSacando = true;
    }

    void controladorVista::procesarCambiosVista()
    {
        if(this->_estaSacando && !this->_vistas.empty())
        {
            this->_vistas.pop();

            if(!this->_vistas.empty())
            {
                this->_vistas.top()->resumir();
            }
            this->_estaSacando = false;
        }
        if (this->_estaAgregando)
        {
            if(!this->_vistas.empty())
            {
                if(this->_estaReemplazando)
                {
                    this->_vistas.pop();
                }
                else
                {
                    this->_vistas.top()->pausa();
                }
            }
            this->_vistas.push(std::move(this->_nuevaVista));
            this->_vistas.top()->init();
            this->_estaAgregando = false;
        }
    }

    vistaRef &controladorVista::getVistaActiva()
    {
        return this->_vistas.top();
    }
}
