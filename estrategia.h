#ifndef ESTRATEGIA_H
#define ESTRATEGIA_H

#include "mapa.h"
#include "nivel.h"

#include "pila.h"


typedef void (*DisposicionTorres)(Nivel*, Mapa*);

void disponer(Nivel* nivel, Mapa* mapa);
void backtracking(Nivel* nivel, Mapa* mapa);
void disponer_con_backtracking(Pila* pila, Nivel* nivel, Mapa* mapa);

void disponer_custom(Nivel* nivel, Mapa* mapa);




#endif
