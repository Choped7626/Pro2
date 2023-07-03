
#include "dynamic_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>


tList createEmptyList(tList *L){ //PostCD : lista inicializada y sin elementos
    *L = LNULL;
    return *L;
}

bool isEmptyList(tList L){
    return (L==LNULL);
}

tPosL first(tList L){ //PreCD: La lista no está vacía.
    if(isEmptyList(L))
        return LNULL;
    return L;
}

tPosL last(tList L){ //PreCD: La lista no esta vacia.
    if(isEmptyList(L))
        return LNULL;
    tPosL P;
    for (P = L;P->next != LNULL; P = P->next);
    return P;
}

tPosL next(tPosL P , tList L){ //PreCD: La posición indicada es una posición válida en la lista.
    if(isEmptyList(L))
        return LNULL;
    return P->next;
}

tPosL previous(tPosL P ,tPosL L){ //PreCD: La posición indicada es una posición válida en la lista.
    if(isEmptyList(L))
        return LNULL;
    tPosL q;
    if(P==L)
        return LNULL;
    else{
        for (q = L;  q->next != P ; q = q->next);
        return q;
    }
}

bool insertItem(tItemL I , tPosL P , tList *L){ //PreCD: La posición indicada es una posición válida en la lista o bien nula (LNULL).
    tPosL q , r;                                //PostCD: Las posiciones de los elementos de la lista posteriores a la delelemento insertado pueden haber variado.
    if(!CreateNode(&q))
        return false;
    else {
        q->data = I;
        q->next = LNULL;
        if (*L == LNULL)
            *L = q;
        else if (P == LNULL){
            for (r = *L; r->next != LNULL; r = r->next);
            r->next = q;
        } else if (P==*L){
            q->next=*L;
            *L=q;
        }else{
            q->data = P->data;
            P->data = I;
            q->next = P->next;
            P->next=q;
        }
        return true;
    }
}

void deleteAtPosition(tPosL P , tList *L){  //PreCD: La posición indicada es una posición válida en la lista.PostCD: Las posiciones de los elementos de la lista posteriores a la de laposición eliminada pueden haber variado
    if(isEmptyList(*L))
        return;
    tPosL q;
    if(P==*L){
        *L=P->next;
    } else if (P->next == LNULL){
        for (q = *L; q->next!=P ; q=q->next);
        q->next=LNULL;
    } else{
        q=P->next;
        P->data=q->data;
        P->next=q->next;
        P=q;
    }
    free(P);
}

tItemL getItem(tPosL P , tList L){ //a lista debe estar inicializada // y la posicion ser una valida
    return P->data;
}

tList updateItem(tItemL I , tPosL P , tList *L){ // PreCD: La posición indicada es una posición válida en la lista.  //   PostCD: El orden de los elementos de la lista no se ve modificado.
    P->data=I;
    return *L;
}

tPosL findItem(tParticipantName N , tList L){
    if(isEmptyList(L)==true) return LNULL;
    tPosL P;
    for (P=L;(P!=LNULL)&&((strcmp(P->data.participantName , N)) != 0); P=P->next);
    return P;
}

bool CreateNode(tPosL *pos){
    *pos= malloc(sizeof (struct tNodo));        //reserva memoria para introducir datos
    return (*pos!=NULL);
}
