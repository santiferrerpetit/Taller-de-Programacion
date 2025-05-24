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

static void quitar_torre(Mapa *mapa, int x, int y, int nro_torre) {
    // actualizar torre
    mapa->torres[nro_torre].x = x;
    mapa->torres[nro_torre].y = y;

    // actualizar mapa
    mapa->casillas[x][y] = VACIO;
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
*/

int quedan_opciones_validas(Pila* pila, Nivel* nivel, Mapa* mapa, int i){
    int cantidad_de_casillas= mapa->alto*mapa->ancho;
    Coordenada pos_val[cantidad_de_casillas];
    int cant_pos_validas=posiciones_validas(pos_val, mapa->casillas, mapa->alto, mapa->ancho);
    return cant_pos_validas <= mapa->cant_torres;
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

//Para llamarla, i siempre tendra que ser 0
int pruebas_backtracking(Nivel* nivel, Mapa* mapa, Pila* pila, int i){
    int bandera = 0;
    int cantidad_de_casillas= mapa->alto*mapa->ancho;
    Coordenada pos_val[cantidad_de_casillas];
    int cant_pos_validas=posiciones_validas(pos_val, mapa->casillas, mapa->alto, mapa->ancho);
    while(bandera != 1){
    //Si el i es el inicial, osea 0 arranco con la disposicion inicial.Si no voy con las pruebas recursivas.El i =-1 es la cancelacion.
        if(quedan_opciones_validas){
        //Verifca que queden opciones validas
            if(i == 0)
            //Verifica que no sea la inicial o la ultima simulacion.
                if(simular_nivel(nivel, mapa, disposicion_inicial_backtracking)){
                    printf("Se encontro la disposicion correcta");
                    bandera = 1;
                    return 1;
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
            else{
                int pos_x = pos_val[i + mapa->cant_torres].x;
                int pos_y = pos_val[i + mapa->cant_torres].y;
                pila_desapilar(pila);
                colocar_torre(mapa,pos_x,pos_y, i + mapa->cant_torres);
                pila_apilar(pila, pos_val[i + mapa->cant_torres]);
                i++;
                pruebas_backtracking(nivel, mapa, pila, i);
                }
                return 1;
                //Hasta aca, la disposicion solo backtrackea una opcion.
        }
        //Con el else lo que hago es que si las opciones se me acabaron, desapilo una, dejo la ultima opcion como valida, apilo la primera opcion, y vuelvo a probar.
            else
                return 0;
    }
}

//Hasta ahora, pruebo una sola linea.Hay que hacer una funcion para que use la funcion de probar una sola linea usando abarcando la posibilidad de tener que desapilar una vez mas.
//La idea de la funcion bajar_nivel es que funcione independientemente de en que nivel esta.
//Bajo un nivel en la pila
void bajar_nivel(Nivel* nivel, Mapa* mapa, Pila* pila){
    if(!pruebas_backtracking(nivel, mapa, pila, 0)){
        if(pila_es_vacia(pila)){
            printf("No hay alternativa. No hay forma de ganar");
        }
        else
            pila_desapilar(pila);
    }
}

//Pruebo una opcion en la casilla de abajo
void probar1(Nivel* nivel,Mapa* mapa,Pila* pila,int intento){
    int cantidad_de_casillas= mapa->alto*mapa->ancho;
    Coordenada pos_val[cantidad_de_casillas];
    int cant_pos_validas=posiciones_validas(pos_val, mapa->casillas, mapa->alto, mapa->ancho);
    pila_apilar(pila, pos_val[intento]);
}

//Hago un while que si no funciona la disposicion, baje un nivel, pruebe una apilacion nueva y vuelva a empezar.
void disponer_con_backtracking_2(Nivel* nivel, Mapa* mapa, Pila* pila){
    int cantidad_de_casillas= mapa->alto*mapa->ancho;
    Coordenada pos_val[cantidad_de_casillas];
    int cant_pos_validas=posiciones_validas(pos_val, mapa->casillas, mapa->alto, mapa->ancho);
    int contador = 0;
    int intento = 0;
    
    while(!pruebas_backtracking(nivel, mapa, pila, contador) && intento <= cant_pos_validas){
        bajar_nivel(nivel,mapa,pila);
        probar1(nivel, mapa, pila, intento);
        intento++;
        disponer_con_backtracking_2(nivel, mapa, pila);
    }

}





//Verifica que la posicion sea valida
int es_posicion_valida_para_torre(Mapa* mapa,int pos1,int pos2){
    return (mapa->casillas[pos1][pos2] == VACIO);
}

// Pseudocódigo
int encontrar_disposicion_torres(Mapa* mapa, Nivel* nivel, int indiceTorre) {
    // Caso base: Si ya hemos intentado colocar todas las torres necesarias
    int cantidad_de_casillas= mapa->alto*mapa->ancho;
    Coordenada pos_val[cantidad_de_casillas];
    int cant_pos_validas=posiciones_validas(pos_val, mapa->casillas, mapa->alto, mapa->ancho);

    Pila *pila = pila_crear();

    //Establezco primeras torres y las dejo en la pila
    for(int i = 0; (i<mapa->cant_torres); i++ , indiceTorre++){
        pila_apilar(pila, pos_val[i]);
        int pos_x = pos_val[i].x;
        int pos_y = pos_val[i].y;
    }
    //
    if (indiceTorre == mapa->cant_torres) {
        // Todas las torres han sido colocadas. Ahora simulamos el nivel para ver si esta disposición es ganadora.
        return simular_nivel(nivel, mapa, disponer_con_backtracking); // Asume que simular_nivel devuelve true si se gana
    }
    //
    // Iterar sobre todas las posibles posiciones para la indiceTorre
    pruebas_backtracking(nivel, mapa, pila, 0);
    //
    //Hay que hacer esto
    // (Necesitarás una forma de obtener las posiciones válidas y disponibles)
    Coordenada pos_val_totales[cantidad_de_casillas];
    int cant_pos_validas_totales=posiciones_validas(pos_val, mapa->casillas, mapa->alto, mapa->ancho); // Asume que esto es un array de todas las posiciones válidas

    for (int i = 0; i < cant_pos_validas_totales; i++) {
        Coordenada pos_candidata = pos_val_totales[i];

        // 1. Verificar si la posición candidata es válida para colocar una torre AHORA (ej. no hay camino, no hay otra torre)
        //Hay que terminarlo pero no se si es del todo util o ya lo hace nuestra colocar torre
        if (es_posicion_valida_para_torre(mapa, pos_candidata.x, pos_candidata.y)) {
            // 2. Probar la decisión: Colocar la torre
            colocar_torre(mapa, pos_candidata.x, pos_candidata.y, indiceTorre); // Asegúrate de que `colocar_torre` actualice el mapa

            // 3. Llamada recursiva para la siguiente torre
            if (encontrar_disposicion_torres(mapa, nivel, indiceTorre + 1)) {
                return 1; // Encontramos una solución
            }

            // 4. Si la llamada recursiva no encontró una solución (o llegó a un callejón sin salida),
            //    DESHACER la decisión: Quitar la torre que acabamos de colocar
            //    Esto es CRUCIAL para el backtracking.
            quitar_torre(mapa, pos_candidata.x, pos_candidata.y); // Necesitarás una función para esto
        }
    }

    // Si hemos probado todas las posiciones para esta torre y ninguna llevó a una solución
    return 0; // No hay solución a partir de este punto
}

// Función principal para iniciar el backtracking
void resolver_disposicion(Nivel* nivel, Mapa* mapa) {
    // Podrías inicializar el mapa aquí si es necesario (ej. limpiar cualquier torre existente)
    if (encontrar_disposicion_torres(mapa, nivel, 0)) {
        printf("¡Se encontró una disposición de torres ganadora!\n");
        // El mapa debería contener la disposición ganadora en este punto
    } else {
        printf("No se encontró ninguna disposición de torres ganadora.\n");
    }
}




void disponer_custom(Nivel* nivel, Mapa* mapa) {
    /* A cargo de la/el estudiante */
    return;
}