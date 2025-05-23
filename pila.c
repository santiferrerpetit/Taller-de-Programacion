#include "pila.h"

void inicializar_pila(Pila* pila) {
    pila->ultimo = -1;
}

int pila_vacia(Pila* pila) {
    return pila->ultimo == -1;
}

int apilar(Pila* pila, Coordenada coord) {
    if (pila->ultimo >= MAX_PILA - 1)
        return 0;  // Pila llena
    pila->ultimo++;
    pila->datos[pila->ultimo] = coord;
    return 1;
}

int desapilar(Pila* pila, Coordenada* coord) {
    if (pila_vacia(pila))
        return 0;
    *coord = pila->datos[pila->ultimo];
    pila->ultimo--;
    return 1;
}