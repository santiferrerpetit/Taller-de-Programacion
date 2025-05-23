#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

Pila* pila_crear() {
    Pila* p = malloc(sizeof(Pila));
    p->ultimo = 0;
    return p;
}

int pila_es_vacia(Pila* p) {
    return (p->ultimo == 0);
}

Coordenada pila_tope(Pila* p) {
    return p->datos[p->ultimo - 1];
}

void pila_apilar(Pila* p, Coordenada dato) {
    if (p->ultimo < MAX_PILA) {
        p->datos[p->ultimo] = dato;
        p->ultimo++;
    }
}

void pila_desapilar(Pila* p) {
    if (!pila_es_vacia(p)) {
        p->ultimo--;
    }
}

void pila_imprimir(Pila* p) {
    for (int i = p->ultimo - 1; i >= 0; i--) {
        printf("(%d, %d)\n", p->datos[i].fila, p->datos[i].columna);
    }
}

void pila_destruir(Pila* p) {
    free(p);
}
