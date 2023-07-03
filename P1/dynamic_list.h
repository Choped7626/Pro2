
#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

#include "types.h"
#define LNULL NULL

typedef struct tNodo* tPosL;

struct tNodo{
    tItemL data;
    tPosL next;
};

typedef tPosL tList;

tList createEmptyList(tList* L);

bool isEmptyList(tList L);

tPosL first(tList L);

tPosL last(tList L);

tPosL next(tPosL P, tList L);

tPosL previous(tPosL P, tList L);

bool insertItem(tItemL I, tPosL P, tList* L);

void deleteAtPosition(tPosL P, tList* L);

tItemL getItem(tPosL P, tList L);

tList updateItem(tItemL I, tPosL P, tList* L);

tPosL findItem(tParticipantName N, tList L);

bool CreateNode(tPosL *pos);

#endif
