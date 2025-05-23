#ifndef PILA_H
#define PILA_H
#include "nivel.h"


#define MAX_PILA 100

typedef struct{
    Coordenada datos[MAX_PILA];
    int ultimo;
} Pila;

// Prototipos
void inicializar_pila(Pila* pila);
int pila_vacia(Pila* pila);
int apilar(Pila* pila, Coordenada coord);
int desapilar(Pila* pila, Coordenada* coord);

#endif