/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Mario Lamas Angeriz LOGIN 1: m.lamasa
 * AUTHOR 2: Andrés Rey Luna LOGIN 2: andres.rey1
 * GROUP: 4.3
 * DATE: 13 / 02 / 2023
 */

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
