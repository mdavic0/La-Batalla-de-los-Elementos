#include "volcan.h"

Volcan::Volcan(): Casillero() {
    cargar_graficos();
}

int Volcan::calcular_costo(string elemento_pj) {
    int nuevo_costo = 0;
    if(elemento_pj == ELEMENTO_AGUA) nuevo_costo = COSTO_VOLCAN*2;
    else if(elemento_pj == ELEMENTO_TIERRA || elemento_pj == ELEMENTO_AIRE) nuevo_costo = COSTO_VOLCAN;
    return nuevo_costo;
}

int Volcan::obtener_costo_base() {
    return COSTO_VOLCAN;
}

string Volcan::tipo_casillero() {
    return VOLCAN;
}
