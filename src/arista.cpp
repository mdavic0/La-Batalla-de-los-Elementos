#include "arista.h"

Arista::Arista() {
    this->origen = 0;
    this->destino = 0;
    this->costo = 0;
}

Arista::Arista(Vertice* origen, Vertice* destino, int costo) {
    this->origen = origen;
    this->destino = destino;
    this->costo = costo;
}

Arista::Arista(Vertice* origen, Vertice* destino) {
    this->origen = origen;
    this->destino = destino;
    this->costo = destino->obtener_casillero()->obtener_costo_base(); // esta wea del costo base hay que implementarlo en casillero cumpa
}

void Arista::insertar_costo(int costo) {
    this->costo = costo;
}

int Arista::obtener_costo() {
    return costo;
}

Vertice* Arista::obtener_destino() {
    return destino;
}

Vertice* Arista::obtener_origen() {
    return origen;
}

Arista::~Arista() {

}

