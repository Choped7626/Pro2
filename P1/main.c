

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif



void New(tList *Partici , char *param1 , char *param2 ){            //introduce un pais en la lista
    tItemL Pais;
    if(findItem(param1 , *Partici) != LNULL){       //si existe no se puede insertar
        printf("+ Error: New not possible\n");
        return;
    }
    strcpy(Pais.participantName , param1);
    if(strcmp(param2 , "eu") == 0){ //se asigna true o false dependiendo del param2
        Pais.EUParticipant = true;
    }else if(strcmp(param2 , "non-eu") == 0) {
        Pais.EUParticipant = false;
    }
    Pais.numVotes = 0;
    insertItem(Pais , LNULL , Partici);
    printf("* New: participant %s location %s\n" , param1 , param2);

}

void Vote(tList *Partici , char *param1 , int *NULLVOTES){                  //lleva a cabo una votacion de un pais
    tItemL Pais;
    if(findItem(param1 , *Partici) == LNULL || isEmptyList(*Partici)){//si el item no está en la lista o esta vacia da error y se suma 1 voto nulo
        printf("+ Error: Vote not possible. Participant %s not found. NULLVOTE\n" , param1);
        *NULLVOTES = *NULLVOTES + 1;
        return;
    }
    Pais=getItem(findItem(param1 , *Partici) ,*Partici);
    Pais.numVotes++;
    updateItem(Pais ,findItem(param1 , *Partici),Partici);
    printf("* Vote: participant %s  location %s numvotes %d\n" ,param1 , Pais.EUParticipant ? "eu" : "non-eu" , Pais.numVotes );
}

void Disqua(tList *Partici , char *param1 , int *NULLVOTES) {                   //elimina un pais de la lista haciendo q sus votos sean nulos
    tItemL Pais;
    tPosL borraraqui = findItem(param1 , *Partici);
    if(borraraqui != LNULL){        //si el item esta en la lista este se elimina y sus votos pasan a ser nulos
        if(findItem(param1 , *Partici) != LNULL)
            *NULLVOTES += getItem(borraraqui ,*Partici).numVotes;//
        deleteAtPosition(borraraqui , Partici);
        printf("* Disqualify: participant %s location %s\n" , param1 ,Pais.EUParticipant ? "eu" : "non-eu");
    }else if (isEmptyList(*Partici) || findItem(Pais.participantName, *Partici) == LNULL){//no se puede descalificar si la lista esta vacia o el pasi no esta en la lista
        printf("+ Error: Disqualify not possible\n");
    }
}

void Stats(tList Partici ,char *param1 , int *NULLVOTES , double cacho){ //muestra la lista por pantalla

    tItemL Pais;
    if (isEmptyList(Partici) ) { //si lista vacia no la muestra
        printf("+ Error: Stats not possible\n");
        return;
    } else {

        tPosL i;
        int votosValidos = 0;
        int nV = 0;
        double totalVoters;
        for (i = first(Partici); i != LNULL; i = next(i, Partici)) { //se recorre toda la lista recogiendo los valores de cada item y imprimiendolos por pantalla

            votosValidos += getItem(i, Partici).numVotes;
            Pais = getItem(i, Partici);
            char *name = getItem(i, Partici).participantName;
            strcpy(Pais.participantName, name);
            nV = getItem(i, Partici).numVotes;
            totalVoters = strtod(param1, NULL);
            printf("Participant %s location %s numvotes %d (%.2f %%) \n", name,
                   getItem(i, Partici).EUParticipant ? "eu" : "non-eu", nV,
                   (votosValidos == 0) ? cacho : ((double)nV / votosValidos) * 100); //contabilizar nulls
        }
        printf("Null votes %d\n", *NULLVOTES);//imprime datos de la lista por pantalla
        printf("Participation: %d votes from %d voters (%.2f %%)\n", votosValidos + *NULLVOTES, (int) totalVoters,
               (strtod(param1, NULL) == 0) ? cacho : ((float) (votosValidos + *NULLVOTES) / totalVoters) * 100);

    }
}

void processCommand(char *commandNumber, char command, char *param1, char *param2 , tList *Partici ,int *NULLVOTES , double cacho) {          //selecciona una operacion de las posibles y la lleeva a cabo

    switch (command) {

        case 'N':
            printf("********************\n");
            printf("%s %c: participant %s location %s\n" , commandNumber , command , param1 , param2);
            New(Partici , param1 , param2);
            break;

        case 'V':
            printf("********************\n");
            printf("%s %c: participant %s \n" , commandNumber , command , param1);
            Vote(Partici , param1 , NULLVOTES);
            break;

        case 'D':
            printf("********************\n");
            printf("%s %c: participant %s\n" , commandNumber , command , param1);
            Disqua(Partici , param1 , NULLVOTES);
            break;

        case 'S':
            printf("********************\n");
            printf("%s %c: totalvoters %s\n" , commandNumber , command , param1);
            Stats(*Partici , param1 , NULLVOTES , cacho);
            break;

        default:
            break;
    }
}

void readTasks(char *filename , tList *Partici , int *NULLVOTES , double cacho) {
    *NULLVOTES = 0;
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2 , Partici , NULLVOTES , cacho);

        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {

    tList Partici;
    createEmptyList(&Partici); //declaro y inicializo la lista
    int NULLVOTES = 0;
    double cacho = 0.00;

    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name , &Partici , &NULLVOTES , cacho);

    return 0;
}
