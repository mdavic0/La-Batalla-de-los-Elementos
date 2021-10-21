#include "personaje_de_fuego.h"

Personaje_de_fuego::Personaje_de_fuego(string nombre, int escudo, int vidas): Personaje(nombre, escudo, vidas) {
    srand(time(nullptr));
    cargar_graficos();
}

Personaje_de_fuego::Personaje_de_fuego(string nombre): Personaje(nombre) {
    srand(time(nullptr));
    cargar_graficos();
}

Personaje_de_fuego::Personaje_de_fuego(string nombre, int escudo, int vidas, int energia, int fila, int columna, int id_jugador, bool se_defiende): Personaje(nombre, escudo, vidas, energia, fila, columna, id_jugador, se_defiende) {
    cargar_graficos();
}

Personaje_de_fuego::Personaje_de_fuego(string nombre, int escudo, int vidas, int energia, int fila, int columna, int id_jugador): Personaje(nombre, escudo, vidas, energia, fila, columna, id_jugador) {
    cargar_graficos();
    asignar_coordenadas_pj(fila, columna);
}

string Personaje_de_fuego::alimentar() {
    int vida_anterior = vidas;
    int energia_anterior = energia;
    if(vidas >= VALOR_MIN_VIDA && vidas <= VALOR_MAX_VIDA) vidas += VIDA_RECUPERADA_P_FUEGO;
    if(vidas > VALOR_MAX_VIDA) vidas = VALOR_MAX_VIDA;
    if(energia >= VALOR_MIN_ENERGIA && energia <= VALOR_MAX_ENERGIA) energia += ENERGIA_RECUPERADA_P_FUEGO;
    if(energia > VALOR_MAX_ENERGIA) energia = VALOR_MAX_ENERGIA;
    return "El personaje " + nombre + " fue alimentado con " + ALIMENTO_P_FUEGO + " y recupero " + to_string(vidas - vida_anterior) + " punto(s) de vida" + "y " + to_string(energia - energia_anterior) + " punto(s) de energia";
}

string Personaje_de_fuego::de_que_elemento_soy() {
    return ELEMENTO_FUEGO;
}

void Personaje_de_fuego::defender() {
    if (energia >= MIN_ENERGIA_DEFENSA_FUEGO) {
        energia -= MIN_ENERGIA_DEFENSA_FUEGO;
        if (energia <= 0){
            energia = 0;
            restar_vida();
        }
        vidas += CURACION_PERSONAJE_FUEGO;
        if(vidas > 100) vidas = 100;
        se_defiende = true;
    } else {
        se_defiende = false;
    }
}

void Personaje_de_fuego::recibe_ataque(string elemento_enemigo, int danio_recibido) {
    if (elemento_enemigo == ELEMENTO_FUEGO) danio_recibido = ATAQUE_BASE_FUEGO;
    else if (elemento_enemigo == ELEMENTO_AIRE) danio_recibido = ATAQUE_DEBIL_AIRE;
    else if (elemento_enemigo == ELEMENTO_AGUA) danio_recibido = ATAQUE_FUERTE_AGUA;

    aplicar_escudo(danio_recibido);
    vidas -= danio_recibido;
    if (vidas < 0) vidas = 0;
}

void Personaje_de_fuego::restar_vida() {
    if (energia == 0) vidas -= 5;
    if (vidas < 0) vidas = 0;
}

int Personaje_de_fuego::obtener_energia_minima_defensa() {
    return MIN_ENERGIA_DEFENSA_FUEGO;
}

int Personaje_de_fuego::obtener_energia_minima_ataque() {
    return MIN_ENERGIA_ATAQUE_FUEGO;
}

bool Personaje_de_fuego::alcanzo_max_alimento() {
    return false;
}
