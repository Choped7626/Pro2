/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Mario Lamas Angeriz  LOGIN 1: m.lamasa@udc.es
 * AUTHOR 2: Andrés Rey Luna LOGIN 2: andres.rey1@udc.es
 * GROUP: 4.3
 * DATE: 27 / 03 / 2023
 */

#ifndef JURY_LIST_H
#define JURY_LIST_H

#include "types.h"
#include "participant_list.h"
#define NULLJ -1
#define MAX 1000


typedef struct tItemJ{
    tParticipantName juryName;
    tNumVotes totalVoters;
    tNumVotes validVotes;
    tNumVotes nullVotes;
    tListP participantList;
} tItemJ;

typedef int tPosJ;

typedef struct tListJ{
    tItemJ dataJ[MAX];
    tPosJ lastJ;
}tListJ;


bool insertItemJ (tItemJ data, tListJ *L);

tListJ deleteAtPositionJ(tPosJ P, tListJ *L);

tPosJ findItemJ(tJuryName N,tListJ L);

tListJ createEmptyListJ(tListJ* L);

bool isEmptyListJ(tListJ L);

tPosJ firstJ(tListJ L);

tPosJ lastJ(tListJ L);

tPosJ nextJ(tPosJ P, tListJ L);

tPosJ previousJ(tPosJ P, tListJ L);

tItemJ getItemJ(tPosJ P, tListJ L);

tListJ updateItemJ(tItemJ I, tPosJ P, tListJ* L);

#endif