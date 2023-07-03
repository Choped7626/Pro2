
#ifndef STATIC_LIST_H
#define STATIC_LIST_H
#define MAX 1000
#define LNULL -1
#include "types.h"


typedef int tPosL;

typedef struct {
    tPosL last;
    tItemL data[MAX];
}tList;

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

#endif
