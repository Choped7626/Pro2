/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Mario Lamas Angeriz  LOGIN 1: m.lamasa@udc.es
 * AUTHOR 2: Andrés Rey Luna LOGIN 2: andres.rey1@udc.es
 * GROUP: 4.3
 * DATE: 27 / 03 / 2023
 */

#include "jury_list.h"
#include "participant_list.h"
#include <strings.h>

bool insertItemJ(tItemJ I, tListJ* L){ //Objetivo: Inserta un elemento de forma ordenada en función del campo juryName. Devuelve un valor true si el elemento fue insertado; false en caso contrario.
    tPosJ i;                           //PostCD: Las posiciones de los elementos de la lista posteriores al insertado pueden cambiar de valor.
    if(L->lastJ == MAX-1)
        return false;
    else{
        if(isEmptyListJ(*L)|| strcmp(I.juryName , L->dataJ[L->lastJ].juryName) > 0){
            L->lastJ++;
            L->dataJ[L->lastJ] = I;
        }
        else{
            L->lastJ++;
            for (i = L->lastJ; i>0 && strcmp(I.juryName , L->dataJ[i-1].juryName) < 0 ; i--) {
                L->dataJ[i] = L->dataJ[i-1];
            }
            L->dataJ[i] = I;
        }
        return true;
    }
}

tListJ deleteAtPositionJ(tPosJ P, tListJ* L){ //Objetivo: Elimina de la lista el elemento que ocupa la posición indicada.
    if (P >= 0 && P <= L->lastJ) {            //PreCD: PreCD: La posición indicada es una posición válida en la lista y el jurado en dicha posición tiene una lista de participantes vacía.
        tPosJ i;                              //PostCD: PostCD: Las posiciones de los elementos de la lista posteriores a la de la posición eliminada pueden haber variado.
        L->lastJ--;
        for (i = P; i <= L->lastJ; i++)          //despalazanse os items variando asi sua posicion
            L->dataJ[i] = L->dataJ[i + 1];
    }
    return *L;
}

tPosJ findItemJ(tJuryName N, tListJ L){ //Objetivo: Devuelve la posición del primer elemento de la lista cuyo nombre de participante se corresponda con el indicado (o LNULL si no existe tal elemento).
    tPosJ P = 0;
    tPosJ mitad = L.lastJ/2;
    if(L.lastJ == NULLJ || (strcmp(N , L.dataJ[0].juryName) < 0)||(strcmp(N , L.dataJ[L.lastJ].juryName) > 0))
        return NULLJ;
    else{
//busqueda binaria implementada
        if(strcmp(N , L.dataJ[mitad].juryName) == 0){
            return mitad;
        }else if(strcmp(N , L.dataJ[mitad].juryName) > 0){
            for (P = mitad; P < L.lastJ && strcmp(N , L.dataJ[P].juryName) > 0 ; P++);
        }else if(strcmp(N , L.dataJ[mitad].juryName) < 0){
            for (P = L.lastJ ; P > firstJ(L) && strcmp(N , L.dataJ[P].juryName) < 0 ; P-- );
        }

        if(strcmp(N , L.dataJ[P].juryName) == 0)
            return P;
        else
            return NULLJ;
    }
}

tListJ createEmptyListJ(tListJ *L){ //PostCD : lista inicializada y sin elementos //Objetivo: Crea una lista vacia
    L->lastJ = NULLJ;
    return *L;
}

bool isEmptyListJ(tListJ L){ // Objetivo: Determina si la lista está vacia
    if(L.lastJ == NULLJ)
        return true;
    else
        return false;
}

tPosJ firstJ(tListJ L){ //PreCD: La lista no está vacía. // Objetivo: Devuelve  la 1º posición de la lista
        return 0;
}

tPosJ lastJ(tListJ L){ //PreCD: La lista no esta vacia. // Objetivo: Devuelve la última posición
        return L.lastJ;
}

tPosJ nextJ(tPosJ P , tListJ L){ //PreCD: La posición indicada es una posición válida en la lista //Objetivo: Devuelve la posición en la lista del elemento siguiente al de la posicion indicada , si no tiene siguiente LNULL.
    if(isEmptyListJ(L)) return 0; //non se pode devolver LNULL porq podria confundir , devolvemos 0 porq en ningun caso a posicion siguiente pode ser 0
    if(L.lastJ > P && P >= 0){
        return P+1;
    }else
        return NULLJ;
}


tPosJ previousJ(tPosJ P , tListJ L){ //PreCD: La posición indicada es una posición válida en la lista. // Objetivo: Devuelve la posición en la lista del elemento anterior al de la posición indicada , LNULL si  la posicion no tiene anterior
    if(L.lastJ <= P && P > 0){
        return P-1;
    }else
        return NULLJ;
}


tItemJ getItemJ(tPosJ P , tListJ L){//Objetivo : Devuelve el contenido del elemento de la lista que ocupa la posición indicada. // PreCD: La posición indicada es una posición válida en la lista.
    return L.dataJ[P];
}


tListJ updateItemJ(tItemJ I, tPosJ P, tListJ *L){ // PreCD: La posición indicada es una posición válida en la lista.  //   PostCD: El orden de los elementos de la lista no se ve modificado.
    if(isEmptyListJ(*L) == true) return *L;       //Objetivo:Modifica el contenido del elemento situado en la posición indicada.
    if (P >= 0 && P <= L->lastJ) {
        L->dataJ[P] = I;
    }
    return *L;
}
