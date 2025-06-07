#ifndef CONTROLADORVISTA_HPP_INCLUDED
#define CONTROLADORVISTA_HPP_INCLUDED
#pragma once
#include <memory>
#include <stack>
#include "Vista.h"

namespace finalProg
{
    typedef std::unique_ptr<Vista> vistaRef;

    class controladorVista
    {
        public:
		controladorVista() { }
		~controladorVista() { }

		void agregarVista(vistaRef nuevaVista, bool estaReemplazando = true);
		void sacarVista();
		void procesarCambiosVista();

		vistaRef &getVistaActiva();

	private:
		std::stack<vistaRef> _vistas;
		vistaRef _nuevaVista;

		bool _estaSacando;
		bool _estaAgregando;
		bool _estaReemplazando;
    };
}

#endif // CONTROLADORVISTA_HPP_INCLUDED
