#include "jugador.h"

Jugador::Jugador() {
    cantidad_personajes = 0;
}

Jugador::Jugador(int id) {
    this->id = id;
    cantidad_personajes = 0;
}

Jugador::~Jugador() {

}

void Jugador::agregar_personaje(Personaje* nuevo) {
    personajes_elegidos[cantidad_personajes++] = nuevo;
}

bool Jugador::eligio_max_personajes() {
    return cantidad_personajes == MAX_PERSONAJES;
}

bool Jugador::jugador_perdio() {
    for(int i = 0; i < cantidad_personajes; i++) {
        if (personajes_elegidos[i]->esta_vivo()) return false;
    }
    return true;
}

string Jugador::personajes() {
    string personajes;

    for(int i = 0; i < cantidad_personajes; i++){
        personajes += '\t' + to_string(i + 1) + ')' + personajes_elegidos[i]->nombre_personaje() + '\n';
    }
    return personajes;
}

string Jugador::detalles_personajes() {
    string detalles_personajes;
    for(int i = 0; i < MAX_PERSONAJES; i++){
        detalles_personajes += personajes_elegidos[i]->detalles_personaje() + '\n';
    }

    return detalles_personajes;
}


int Jugador::obtener_cantidad_personajes() {
    return MAX_PERSONAJES;
}

int Jugador::obtener_id() {
    return id;
}

Personaje* Jugador::obtener_personaje(int pos) {
    return personajes_elegidos[pos];
}