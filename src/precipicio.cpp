#include "precipicio.h"

Precipicio::Precipicio(): Casillero() {
    cargar_graficos();
}

int Precipicio::calcular_costo(string elemento_pj) {
    int nuevo_costo = 0;
    if(elemento_pj == ELEMENTO_TIERRA) nuevo_costo = COSTO_PRECIPICIO*2;
    else if(elemento_pj == ELEMENTO_FUEGO || elemento_pj == ELEMENTO_AGUA) nuevo_costo = COSTO_PRECIPICIO;
    return nuevo_costo;
}


int Precipicio::obtener_costo_base() {
    return COSTO_PRECIPICIO;
}

string Precipicio::tipo_casillero() {
    return PRECIPICIO;
}
