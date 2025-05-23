#include "estrategia.h"
#include "simulador.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

static int posiciones_validas(Coordenada *validas, TipoCasilla **casillas, int alto, int ancho) {
    int cant_posiciones_validas = 0;
    
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            if (casillas[i][j] == VACIO) {
                validas[cant_posiciones_validas].x = i;
                validas[cant_posiciones_validas++].y = j;
            }
        }
    }

    return cant_posiciones_validas;
}

static void colocar_torre(Mapa *mapa, int x, int y, int nro_torre) {
    // actualizar torre
    mapa->torres[nro_torre].x = x;
    mapa->torres[nro_torre].y = y;

    // actualizar mapa
    mapa->casillas[x][y] = TORRE;
}

static int determinar_posicion_torre(int *casilla_elegida, int cant_validas) {
    int nueva_posicion = rand() % cant_validas;
    while(casilla_elegida[nueva_posicion])
        nueva_posicion = rand() % cant_validas;

    return nueva_posicion;
}


void disponer(Nivel* nivel, Mapa* mapa) {
    int cantidad_casillas = mapa->alto * mapa->ancho;
    Coordenada posiciones_validas_torre[cantidad_casillas];
    int casilla_elegida[cantidad_casillas];
    for(int i = 0; i < cantidad_casillas; casilla_elegida[i++] = 0);

    int cant_validas = posiciones_validas(posiciones_validas_torre, mapa->casillas, mapa->alto, mapa->ancho);

    for (int colocadas = 0; colocadas < mapa->cant_torres; colocadas++) {
        int nueva_torre = determinar_posicion_torre(casilla_elegida, cant_validas);
        casilla_elegida[nueva_torre] = 1;
        int nueva_torre_x = posiciones_validas_torre[nueva_torre].x;
        int nueva_torre_y = posiciones_validas_torre[nueva_torre].y;
        colocar_torre(mapa, nueva_torre_x, nueva_torre_y, colocadas);
    }
}

/*
void backtracking(Nivel* nivel, Mapa* mapa) {
    int cantidad_de_casillas= mapa->alto*mapa->ancho;
    Coordenada pos_val[cantidad_de_casillas];
    int cant_pos_validas=posiciones_validas(pos_val, mapa->casillas, mapa->alto, mapa->ancho);
    DisposicionTorres estrategia_actual = disponer;
    
    Pila *pila = pila_crear();

    for(int i = 0; i<mapa->cant_torres; i++)
        pila_apilar(pila, pos_val[i]);
    
    for(int i = (mapa->cant_torres - 1); i<cant_pos_validas; i++){
        //la condicion tiene que ser el simular_nivel
        if(simular_nivel(nivel, mapa, disponer_con_backtracking )){
            for(int j=0;j<mapa->cant_torres;j++){
                Coordenada coord =pila_tope(pila) ;
                int x= coord.x ;
                int y= coord.y ;
                colocar_torre(mapa, x, y, j);
                pila_desapilar(pila);
            }
        }

    }

    return;
}

void disponer_con_backtracking(Pila* pila, Nivel* nivel, Mapa* mapa) {
    for(int j=0;j<mapa->cant_torres;j++){
        Coordenada coord =pila_tope(pila) ;
            int x= coord.x ;
            int y= coord.y ;
            colocar_torre(mapa, x, y, j);
            pila_desapilar(pila);
    };
}
*/

void disposicion_inicial_backtracking(Nivel* nivel, Mapa* mapa){
    int cantidad_de_casillas= mapa->alto*mapa->ancho;
    Coordenada pos_val[cantidad_de_casillas];
    int cant_pos_validas=posiciones_validas(pos_val, mapa->casillas, mapa->alto, mapa->ancho);

    Pila *pila = pila_crear();

    //Establezco primeras torres y las dejo en la pila
    for(int i = 0; (i<mapa->cant_torres); i++){
        pila_apilar(pila, pos_val[i]);
        int pos_x = pos_val[i].x;
        int pos_y = pos_val[i].y;
        colocar_torre(mapa, pos_x, pos_y, i);
        
    }
}

void pruebas_backtracking(Nivel* nivel, Mapa* mapa, Pila* pila, int i){
    int cantidad_de_casillas= mapa->alto*mapa->ancho;
    Coordenada pos_val[cantidad_de_casillas];
    int cant_pos_validas=posiciones_validas(pos_val, mapa->casillas, mapa->alto, mapa->ancho);

    if((simular_nivel(nivel, mapa, disposicion_inicial_backtracking))){
    }
    else{
        int pos_x = pos_val[i + mapa->cant_torres].x;
        int pos_y = pos_val[i + mapa->cant_torres].y;
        pila_desapilar(pila);
        colocar_torre(mapa,pos_x,pos_y, i + mapa->cant_torres);
        pila_apilar(pila, pos_val[i + mapa->cant_torres]);
        i++;
        pruebas_backtracking(nivel, mapa, pila, i);
        }
}

void disponer_custom(Nivel* nivel, Mapa* mapa) {
    /* A cargo de la/el estudiante */
    return;
}
