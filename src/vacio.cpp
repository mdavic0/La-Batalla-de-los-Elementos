#include "vacio.h"

Vacio::Vacio(): Casillero() {
    cargar_graficos();
}

int Vacio::calcular_costo(string elemento_pj) {
    return COSTO_VACIO;
}

int Vacio::obtener_costo_base() {
    return COSTO_VACIO;
}

string Vacio::tipo_casillero() {
    return VACIO;
}
