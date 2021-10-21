#include "camino.h"

Camino::Camino(): Casillero() {
    cargar_graficos();
}

int Camino::calcular_costo(string elemento_pj) {
    return COSTO_CAMINO;
}

int Camino::obtener_costo_base() {
    return COSTO_CAMINO;
}

string Camino::tipo_casillero() {
    return CAMINO;
}
