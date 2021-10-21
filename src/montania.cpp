#include "montania.h"

Montania::Montania(): Casillero() {
    cargar_graficos();
}

int Montania::calcular_costo(string elemento_pj) {
    int nuevo_costo = 0;
    if(elemento_pj == ELEMENTO_AIRE) nuevo_costo = COSTO_MONTANIA*2;
    else if(elemento_pj == ELEMENTO_FUEGO || elemento_pj == ELEMENTO_AGUA) nuevo_costo = COSTO_MONTANIA;
    return nuevo_costo;
}

int Montania::obtener_costo_base() {
    return COSTO_MONTANIA;
}

string Montania::tipo_casillero() {
    return MONTANIA;
}
