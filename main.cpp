#include "Juego.h"
#include "VistaMenu.h"

int main() {
    Juego juego;
    juego.cambiarVista(new VistaMenu());
    juego.ejecutar();

    return 0;
}
