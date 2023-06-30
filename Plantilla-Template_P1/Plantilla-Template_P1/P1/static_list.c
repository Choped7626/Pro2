/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Mario Lamas Angeriz LOGIN 1: m.lamasa
 * AUTHOR 2: Andrés Rey Luna LOGIN 2: andres.rey1
 * GROUP: 4.3
 * DATE: 13 / 02 / 2023
 */

#include "static_list.h"
#include <strings.h>

tList createEmptyList(tList *L){ //PostCD : lista inicializada y sin elementos
    L->last = LNULL;
    return *L;
}

bool isEmptyList(tList L){
    if(L.last == LNULL)
        return true;
    else
        return false;
}

tPosL first(tList L){ //PreCD: La lista no está vacía.
    if(!isEmptyList(L))
    return 0;
}

tPosL last(tList L){ //PreCD: La lista no esta vacia.
    if (!isEmptyList(L)){
        return L.last;
    }
    return LNULL;
}

tPosL next(tPosL P , tList L){ //PreCD: La posición indicada es una posición válida en la lista.
    if(isEmptyList(L)==true) return 0; //non se pode devolver LNULL porq podria confundir , devolvemos 0 porq en ningun caso a posicion siguiente pode ser 0
    if(L.last > P && P >= 0){
        return P+1;
    }else
        return LNULL;
    }

tPosL previous(tPosL P , tList L){ //PreCD: La posición indicada es una posición válida en la lista.
    if(isEmptyList(L) == true) return L.last; // non se pode devolver LNULL porq podria confundir, a ultima posicion nunca podería ser a previa a algo porq e a ultima
    if(L.last <= P && P > 0){
        return P-1;
    }else
        return LNULL;
    }

bool insertItem(tItemL I , tPosL P , tList *L){ //PreCD: La posición indicada es una posición válida en la lista o bien nula (LNULL).
    if(L->last == MAX - 1 )                     //PostCD: Las posiciones de los elementos de la lista posteriores a la delelemento insertado pueden haber variado.
        return false;//lista llena
    L->last++;
    if (P == LNULL) {
        L->data[L->last] = I;
    } else {
        for (tPosL i = L->last; i >= P + 1; i--)    //recorre la lista asignando valores
            L->data[i] = L->data[i - 1];
        L->data[P] = I;
    }
        return true;
}

void deleteAtPosition(tPosL P , tList *L) {             //PreCD: La posición indicada es una posición válida en la lista.PostCD: Las posiciones de los elementos de la lista posteriores a la de laposición eliminada pueden haber variado
    if(isEmptyList(*L) == true) return;
    if (P >= 0 && P <= L->last) {
        tPosL i;
        L->last--;
        for (i = P; i <= L->last; i++)          //despalazanse os items variando asi sua posicion
            L->data[i] = L->data[i + 1];
    }
}

tItemL getItem(tPosL P , tList L){//a lista debe estar inicializada //y la posicion ser una valida
        return L.data[P];
}

tList updateItem(tItemL I, tPosL P, tList *L){ // PreCD: La posición indicada es una posición válida en la lista.  //   PostCD: El orden de los elementos de la lista no se ve modificado.
    if(isEmptyList(*L) == true) return *L;
    if (P >= 0 && P <= L->last) {
        L->data[P] = I;
    }
    return *L;
}

tPosL findItem(tParticipantName N, tList L){
    if(isEmptyList(L)==true) return LNULL;
    tPosL P;
    if(L.last == LNULL)
        return LNULL;
    else{
        for (P = 0; (P < L.last) && (strcmp(L.data[P].participantName , N) != 0); P++); //recorre la lista comparando hasta q encuantra dodnde esta
        if(strcmp(L.data[P].participantName , N) == 0){
            return P;
        } else{
            return LNULL;
        }
    }
}