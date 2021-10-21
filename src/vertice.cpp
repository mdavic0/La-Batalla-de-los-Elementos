#include "vertice.h"

Vertice::Vertice(Casillero* casillero, int primera, int segunda) {
    vertices_ady = new Arista*[MAX_CANT_ARISTAS_SIN_DIAGONALES];
    vertices_ady_y_diagonales = new Arista*[MAX_CANT_ARISTAS_CON_DIAGONALES];
    cant_aristas = 0;
    cant_aristas_contando_diagonales = 0;
    this->casillero = casillero;
    this->coordenadas = Coordenada(primera, segunda);
}

Vertice::Vertice() {
    vertices_ady = 0;
    vertices_ady_y_diagonales = 0;
    cant_aristas = 0;
    cant_aristas_contando_diagonales = 0;
    this->casillero = 0;
    this->coordenadas = Coordenada(0, 0);
}

void Vertice::agregar_arista(Arista* nueva, bool contando_diagonales) {
    if(!contando_diagonales) {
        vertices_ady[cant_aristas] = nueva;
        cant_aristas++;
    }
    else {
        vertices_ady_y_diagonales[cant_aristas_contando_diagonales] = nueva;
        cant_aristas_contando_diagonales++;
    }
}

bool Vertice::hay_arista(Vertice* destino, bool contando_diagonales) {
    if(contando_diagonales) {
        for(int i = 0; i < cant_aristas_contando_diagonales; i++) {
            if(vertices_ady_y_diagonales[i]->obtener_destino() == destino) return true;
        }
        return false;
    }
    for(int i = 0; i < cant_aristas; i++) {
        if(vertices_ady[i]->obtener_destino() == destino) return true;
    }
    return false;
}

Coordenada Vertice::obtener_coordenadas() {
    return coordenadas;
}

int Vertice::obtener_cantidad_aristas(bool contando_diagonales) {
    if(contando_diagonales) return cant_aristas_contando_diagonales;
    return cant_aristas;
}

Arista* Vertice::obtener_arista(int pos, bool contando_diagonales) {
    if(contando_diagonales) return vertices_ady_y_diagonales[pos];
    return vertices_ady[pos];
}

Casillero* Vertice::obtener_casillero() {
    return casillero;
}

Vertice::~Vertice() {
    delete casillero;
    for(int i = 0; i < cant_aristas; i++) delete vertices_ady[i];
    delete vertices_ady;
    for(int i = 0; i < cant_aristas_contando_diagonales; i++) delete vertices_ady_y_diagonales[i];
    delete vertices_ady_y_diagonales;
}