#include "lago.h"

Lago::Lago(): Casillero() {
    cargar_graficos();
}

int Lago::calcular_costo(string elemento_pj) {
    int nuevo_costo = 0;
    if(elemento_pj == ELEMENTO_FUEGO) nuevo_costo = COSTO_LAGO*2;
    else if(elemento_pj == ELEMENTO_TIERRA || elemento_pj == ELEMENTO_AIRE) nuevo_costo = COSTO_LAGO;
    return nuevo_costo;
}

int Lago::obtener_costo_base() {
    return COSTO_LAGO;
}

string Lago::tipo_casillero() {
    return LAGO;
}
