#include "Juego.h"
#include "VistaMenu.h"

// --- INCLUSIONES PARA TESTS (DESCOMENTAR SI QUIERES EJECUTAR TESTS) ---
// Comentar estos includes si no se ejecutan los TEST
/*
#include "tau/tau.h" // Incluye TAU
#include "Personaje.h" // Incluye tus clases para testearlas
#include "PersonajeSecundario.h"
#include "Enemigo.h"
#include "Moneda.h"
#include "Roca.h"
#include <SFML/Graphics.hpp> // Necesario para sf::Texture en algunos tests
*/
// --- FIN INCLUSIONES PARA TESTS ---



// --- BLOQUE 1: INICIAR EL JUEGO (DESCOMENTAR ESTE BLOQUE para JUGAR) ---
// Si queres jugar, descomenta el siguiente bloque `int main()`.
// Asegurate de que el bloque `TAU_MAIN()` más abajo esté COMENTADO.

int main() {
    Juego juego;
    juego.cambiarVista(new VistaMenu());
    juego.ejecutar();

    return 0;
}






// --- BLOQUE 2: EJECUTAR TESTS (DESCOMENTAR ESTE BLOQUE para TESTEAR) ---

/*
TEST(Personaje, Inicializacion) {
    sf::Texture dummyTexture;
    dummyTexture.create(10, 10);
    Personaje p(dummyTexture, 100, 500);
    CHECK(p.estaVivo());
    CHECK_EQ(p.getPosX(), 100.0f);
    CHECK_EQ(p.getPosY(), 500.0f);
}

TEST(Personaje, SaltarEstadoInicial) {
    sf::Texture dummyTexture;
    dummyTexture.create(10, 10);
    Personaje p(dummyTexture, 100, 500);
    float initialPosY = p.getPosY();
    p.saltar();
    p.actualizar();
    CHECK(p.getPosY() < initialPosY);
}

TEST(Personaje, Morir) {
    sf::Texture dummyTexture;
    dummyTexture.create(10, 10);
    Personaje p(dummyTexture, 100, 500);
    p.morir();
    CHECK_FALSE(p.estaVivo());
}

TEST(Enemigo, Inicializacion) {
    sf::Texture dummyTexture;
    dummyTexture.create(10, 10);
    Enemigo e(dummyTexture, 800);
    CHECK_EQ(e.getPosX(), 800.0f);
    CHECK_EQ(e.getPosY(), 500.0f);
}

TEST(Enemigo, Movimiento) {
    sf::Texture dummyTexture;
    dummyTexture.create(10, 10);
    Enemigo e(dummyTexture, 800);
    float initialPosX = e.getPosX();
    e.actualizar();
    CHECK(e.getPosX() < initialPosX);
}

TEST(Moneda, Inicializacion) {
    sf::Texture dummyTexture;
    dummyTexture.create(10, 10);
    Moneda m(dummyTexture, 300, 400, 0.0f);
    CHECK_EQ(m.getGlobalBounds().left, 300.0f);
    CHECK_EQ(m.getGlobalBounds().top, 400.0f);
    CHECK_EQ(m.getTiempoAparicion(), 0.0f);
}

TEST(Moneda, Escala) {
    sf::Texture dummyTexture;
    dummyTexture.create(10, 10);
    Moneda m(dummyTexture, 0, 0, 0.0f);
    m.setScale(2.0f, 2.0f);
    CHECK_EQ(m.getGlobalBounds().width, 10.0f * 2.0f);
    CHECK_EQ(m.getGlobalBounds().height, 10.0f * 2.0f);
}

TEST(Roca, Inicializacion) {
    sf::Texture dummyTexture;
    dummyTexture.create(10, 10);
    Roca r(dummyTexture, 500);
    CHECK_EQ(r.getGlobalBounds().left, 500.0f);
    CHECK_EQ(r.getPosY(), 0.0f);
}

TEST(Roca, Caida) {
    sf::Texture dummyTexture;
    dummyTexture.create(10, 10);
    Roca r(dummyTexture, 500);
    float initialPosY = r.getPosY();
    r.actualizar(1.0f);
    CHECK(r.getPosY() > initialPosY);
}


TAU_MAIN()
*/

