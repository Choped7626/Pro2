
#include "participant_list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

tListP createEmptyListP(tListP *L){ //PostCD : lista inicializada y sin elementos //Objetivo: crea una lista vacia
    *L = NULLP;
    return *L;
}

bool isEmptyListP(tListP L){//Objetivo: Determina si la lista esta vacia
    return (L==NULLP);
}

tPosP firstP(tListP L){ //PreCD: La lista no está vacía. // Objetivo: Devuelve  la 1º posición de la lista
    return L;
}

tPosP lastP(tListP L){ //PreCD: La lista no esta vacia. // Objetivo: Devuelve la última posición
    tPosP P;
    for (P = L;P->nextP != NULLP; P = P->nextP);
    return P;
}

tPosP followingP(tPosP P , tListP L){ //PreCD: La posición indicada es una posición válida en la lista //Objetivo: Devuelve la posición en la lista del elemento siguiente al de la posicion indicada , si no tiene siguiente LNULL.
    if(isEmptyListP(L))
        return NULLP;
    return P->nextP;
}

tPosP previousP(tPosP P ,tPosP L){ //PreCD: La posición indicada es una posición válida en la lista. // Objetivo: Devuelve la posición en la lista del elemento anterior al de la posición indicada , LNULL si  la posicion no tiene anterior
    tPosP q;
    if(P==L || P==NULLP)
        return NULLP;
    else{
        for (q = L;  q->nextP != P ; q = q->nextP);
        return q;
    }
}

bool insertItemP(tItemP I , tListP *L){ //Objetivo: Inserta un elemento de forma ordenada en función del campo participantName. Devuelve un valor true si el elemento fue insertado; false en caso contrario.
    tPosP q , p; //PostCD: Las posiciones de los elementos de la lista posteriores a la del elemento insertado pueden haber variado.
    //createNode
    q = malloc(sizeof (struct tNodo));
    //create node
    if(q == NULL)
        return false;
    else{
        q->dataP=I;
        q->nextP=NULLP;
        if(*L==NULLP)
            *L=q;
        else if(strcmp(I.participantName , (*L)->dataP.participantName) < 0){
            q->nextP=(*L);
            *L=q;
        }else{
            p= findPosiotionP(*L , I);
            q->nextP = p->nextP;
            p -> nextP = q;
        }
        return true;
    }
}

tPosP findPosiotionP(tListP miL , tItemP I){ // Objetivo: Devuelve la posición del primer elemento de la lista cuyo nombre de participante se corresponda con el indicado (o LNULL si no existe tal elemento)
    tPosP pos;
    pos = miL;
    while ((pos->nextP != NULLP) && (strcmp(I.participantName , pos->nextP->dataP.participantName) > 0) ){
    pos = pos->nextP;
    }
    return pos;
}

void deleteAtPositionP(tPosP P , tListP *L){  //PreCD: La posición indicada es una posición válida en la lista.PostCD: Las posiciones de los elementos de la lista posteriores a la de laposición eliminada pueden haber variado
    if(isEmptyListP(*L))
        return;
    tPosP q;
    if(P==*L){
        *L=P->nextP;
    } else if (P->nextP == NULLP){
        for (q = *L; q->nextP!=P ; q=q->nextP);
        q->nextP=NULLP;
    } else{
        q=P->nextP;
        P->dataP=q->dataP;
        P->nextP=q->nextP;
        P=q;
    }
    free(P);
}

tItemP getItemP(tPosP P , tListP L){//Objetivo : Devuelve el contenido del elemento de la lista que ocupa la posición indicada. // PreCD: La posición indicada es una posición válida en la lista.
    return P->dataP;
}

tListP updateItemP(tItemP I , tPosP P , tListP *L){ // PreCD: La posición indicada es una posición válida en la lista.  //   PostCD: El orden de los elementos de la lista no se ve modificado.
    P->dataP=I;                                     //Objetivo:Modifica el contenido del elemento situado en la posición indicada.
    return *L;
}

tPosP findItemP(tParticipantName N , tListP L){ //Objetivo: Devuelve la posición del primer elemento de la lista cuyo nombre de participante se corresponda con el indicado (o LNULL si no existe tal elemento).
    if(isEmptyListP(L)) return NULLP;
//esta implementada la busqueda binaria para mayor eficiencia
    tPosP P = L;

    //count items
    tPosP C;
    int count = 0;
    for (C = L; C != NULLP ; C = C->nextP) {
        count++;
    }
    //count items

    int numeroPart = count;
    int mitad = numeroPart / 2;
    for(mitad ; mitad != 0 ; mitad--){
        P = P->nextP;
    }

    if(strcmp(N , P->dataP.participantName) == 0){
        return P;
    }else if(strcmp(N , P->dataP.participantName) > 0){
        for (P ; P != NULLP ; P = P->nextP){
            if(strcmp(N , P->dataP.participantName) == 0){
                return P;
            }
        }
    }else if(strcmp(N , P->dataP.participantName) < 0){
        for (P ; P != NULLP ; P = previousP(P , L)){
            if(strcmp(N , P->dataP.participantName) == 0){
                return P;
            }
        }
    }
}
