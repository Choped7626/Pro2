/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Mario Lamas Angeriz  LOGIN 1: m.lamasa@udc.es
 * AUTHOR 2: Andrés Rey Luna LOGIN 2: andres.rey1@udc.es
 * GROUP: 4.3
 * DATE: 27 / 03 / 2023
 */

#ifndef PARTICIPANT_LIST_H
#define PARTICIPANT_LIST_H
#define NULLP NULL

#include <stdio.h>
#include "types.h"

typedef struct tItemP{
    tParticipantName participantName;
    tNumVotes numVotes;
    tEUParticipant EUParticipant;
}tItemP;

typedef struct tNodo* tPosP;

struct tNodo{
    tItemP dataP;
    tPosP nextP;
};

typedef tPosP tListP;


tListP createEmptyListP(tListP* L);

bool isEmptyListP(tListP L);

tPosP firstP(tListP L);

tPosP lastP(tListP L);

tPosP findPosiotionP(tListP miL , tItemP I);

tPosP followingP(tPosP P, tListP L);

tPosP previousP(tPosP P, tListP L);

bool insertItemP(tItemP I , tListP *L);

void deleteAtPositionP(tPosP P, tListP* L);

tItemP getItemP(tPosP P, tListP L);

tListP updateItemP(tItemP I, tPosP P, tListP* L);

tPosP findItemP(tParticipantName N, tListP L);

#endif