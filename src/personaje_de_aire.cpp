#include "personaje_de_aire.h"

Personaje_de_aire::Personaje_de_aire(string nombre, int escudo, int vidas): Personaje(nombre, escudo, vidas) {
    srand(time(nullptr));
    cargar_graficos();
}

Personaje_de_aire::Personaje_de_aire(string nombre): Personaje(nombre) {
    srand(time(nullptr));
    cargar_graficos();
}

Personaje_de_aire::Personaje_de_aire(string nombre, int escudo, int vidas, int energia, int fila, int columna, int id_jugador, bool se_defiende): Personaje(nombre, escudo, vidas, energia, fila, columna, id_jugador, se_defiende) {
    cargar_graficos();
}

Personaje_de_aire::Personaje_de_aire(string nombre, int escudo, int vidas, int energia, int fila, int columna, int id_jugador): Personaje(nombre, escudo, vidas, energia, fila, columna, id_jugador) {
    cargar_graficos();
    asignar_coordenadas_pj(fila, columna);
}

string Personaje_de_aire::alimentar() {
    return ALIMENTO_P_AIRE;
}

string Personaje_de_aire::de_que_elemento_soy() {
    return ELEMENTO_AIRE;
}

void Personaje_de_aire::defender() {
    if (energia >= MIN_ENERGIA_DEFENSA_AIRE) {
        energia -= MIN_ENERGIA_DEFENSA_AIRE;
        se_defiende = true;
        cambiar_turno(); //aca se le suman +5 de energia;
    } else {
        se_defiende = false;
    }
}

void Personaje_de_aire::recibe_ataque(string elemento_enemigo, int danio_recibido) {
    if (elemento_enemigo == ELEMENTO_AIRE) danio_recibido = ATAQUE_BASE_AIRE;
    else if (elemento_enemigo == ELEMENTO_TIERRA) danio_recibido = ATAQUE_DEBIL_TIERRA;
    else if (elemento_enemigo == ELEMENTO_FUEGO) danio_recibido = ATAQUE_FUERTE_FUEGO;
    else danio_recibido = ATAQUE_BASE_AGUA;

    aplicar_escudo(danio_recibido);
    vidas -= danio_recibido;
    if(vidas < 0) vidas = 0;
}

int Personaje_de_aire::obtener_energia_minima_defensa() {
    return MIN_ENERGIA_DEFENSA_AIRE;
}

int Personaje_de_aire::obtener_energia_minima_ataque() {
    return MIN_ENERGIA_ATAQUE_AIRE;
}

bool Personaje_de_aire::alcanzo_max_alimento() {
    return false;
}
