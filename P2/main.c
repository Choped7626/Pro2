/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Mario Lamas Angeriz  LOGIN 1: m.lamasa@udc.es
 * AUTHOR 2: Andrés Rey Luna LOGIN 2: andres.rey1@udc.es
 * GROUP: 4.3
 * DATE: 27 / 03 / 2023
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "jury_list.h"

#define MAX_BUFFER 255

void Create(tListJ *Jurados, char *juryName ,char *totalVoters){

    tItemJ Jurado;                                                                  //variable auxiliar para poder crear el jurado  en la lista

    if (findItemJ(juryName , *Jurados) != NULLJ){                                   //comprobamos q no existe el jurado q intentamos crear  en la lista
        printf("+ Error: Create not possible\n");
        return;
    }

    strcpy(Jurado.juryName , juryName);                                             //utilizamos diferentes variables auxiliares para crear al jurado con los valores iniciales indicados
    int votantesTotales;
    votantesTotales = strtol(totalVoters , NULL , 10);                              //pasamos el string al int para poder asignarlo
    Jurado.totalVoters=votantesTotales;
    tListP parts;
    Jurado.participantList = createEmptyListP(&parts);                              //se crea la lista Part asignada al item jury
    Jurado.nullVotes = 0;                                                           //se inicializan los votos a 0
    Jurado.validVotes = 0;
    if(!insertItemJ(Jurado , Jurados)){                                             //comprobamos q se inserta correctamente
        printf("+ Error: New not possible\n");
        return;
    }
    printf("* Create: jury %s totalvoters %s\n" , juryName,totalVoters);            //se imprime la confirmacion del exito
}

void New(tListJ *Jurados , char *juryName , char *participantName , char *EUParticipant){
                                                                                    //comprobamos si no existe el jurado en su lista o si el participante no existe en su lista
    if(findItemJ(juryName,*Jurados) == NULLJ  || findItemP(participantName , getItemJ(findItemJ(juryName , *Jurados) , *Jurados).participantList) != NULLP){
        printf("+ Error: New not possible\n");
        return;
    }

    tItemP Participante;                                                            //valor auxiliar donde almacenar los valores

    Participante.numVotes=0;                                                        //asignacion de valores
    strcpy(Participante.participantName , participantName);

    if(strcmp(EUParticipant , "eu") == 0){
        Participante.EUParticipant = true;
    }else if (strcmp(EUParticipant , "non-eu") == 0){
        Participante.EUParticipant = false;
    }

    tPosJ juryPos;                                                                 //obtenemos la lista de participantes
    juryPos = findItemJ(juryName , *Jurados);                                      //del jurado correspondiente
    tItemJ juryItem;
    juryItem = getItemJ(juryPos , *Jurados);
    tListP* Participants;
    Participants = &juryItem.participantList;
    if(!insertItemP(Participante , Participants)){                                 //insertamos el participante en la lista de participantes obtenida anteriormente y comprobamos q funciona correctamente
        printf("+ Error: New not possible\n");
        return;
    }
    juryItem.participantList = *Participants;
    updateItemJ(juryItem , juryPos , Jurados);                                     //Se actualiza el item jurado con la lista de participantes con los valores insertados en la lista principal de jurados

    printf("* New: jury %s participant %s location %s\n" , juryName , participantName , EUParticipant);
}

void Vote(tListJ *Jurados , char *juryName , char *participantName){

    if(findItemJ(juryName , *Jurados) == NULLJ){                                   //comprobamos  q  exista el  jurado
        printf("+ Error: Vote not possible\n");
        return;
    }

    tPosJ juryPos;                                                                 //obtenemos  la  lista de participantes del jurado correspondiente
    juryPos = findItemJ(juryName , *Jurados);
    tItemJ juryItem = getItemJ(juryPos , *Jurados);
    tListP *Participants;
    Participants = &juryItem.participantList;

    if(findItemP(participantName , *Participants) == NULLP){                       //si no existe el participante en la lista aumentamos los votos nulos  y se imprime el error
        juryItem.nullVotes++;
        updateItemJ(juryItem , juryPos , Jurados);
        printf("+ Error: Vote not possible. Participant %s not found in jury %s. NULLVOTE\n" , participantName , juryName);
        return;
    }

    tPosP PartPos;                                                                 //se aumenta el numero de votos del participante y se acttualiza en la lista
    PartPos = findItemP(participantName , *Participants);                          //y luego la variable auxiliar jury item con variables actualizadas y la  lista anterior dentro de este item se actualiza en la lista jurados
    tItemP PartItem;
    PartItem = getItemP(PartPos , *Participants);
    PartItem.numVotes++;
    updateItemP(PartItem , PartPos , Participants);

    juryItem.validVotes++;
    juryItem.participantList = *Participants;
    updateItemJ(juryItem , juryPos , Jurados);

    printf("* Vote: jury %s participant %s location %s numvotes %d\n" , juryName , participantName , PartItem.EUParticipant ? "eu" : "non-eu" , PartItem.numVotes);
}

void Stats(tListJ *Jurados){

    if(isEmptyListJ(*Jurados)){
        printf("+ Error: Stats not possible\n");
        return;
    }

    tPosJ referencia;
    referencia = firstJ(*Jurados);

    for (referencia ; referencia != NULLJ ; referencia = nextJ(referencia , *Jurados)) {        //se recorre toda la lista obteninendo e imprimiendo los jurados y sus participantes

        tItemJ Juradoi = getItemJ(referencia, *Jurados);//se obtiene el item numero 'n'
        printf("Jury %s\n", Juradoi.juryName);

        tListP *parts;
        parts = &Juradoi.participantList;


        if (isEmptyListP(*parts)) {
            printf("No participants\n");
        }else {
            tPosP ref;
            ref = firstP(*parts);
            for (ref; ref != NULLP; ref = followingP(ref, *parts)) {//se recorre la lista participantes obtenindo sus items e imprimiendo los valores

                tItemP Participantei = getItemP(ref, *parts);
                printf("Participant %s location %s numvotes %d (%.2f%%)\n", Participantei.participantName,
                       Participantei.EUParticipant ? "eu" : "non-eu", Participantei.numVotes,
                       Juradoi.validVotes == 0 ? 0.00 : ((float)Participantei.numVotes / (float)Juradoi.validVotes)*100);

            }
        }
        printf("Nullvotes %d\n", Juradoi.nullVotes);            //se debe apreciar q en esta orden el procentaje puede ser mayor que el 100% dependiendo de los valores introducidos por el usuario , consideramos q esto debe producirse pues en el enunciado no se especifica q esto no pueda ocurrir
        printf("Participation: %d votes from %d voters (%.2f%%)\n", Juradoi.validVotes + Juradoi.nullVotes , Juradoi.totalVoters, (((float)Juradoi.validVotes + (float)Juradoi.nullVotes) / (float)Juradoi.totalVoters) * 100.00);
        printf("\n");
    }
}

void Dissqualify(tListJ *Jurados , char *participantName){

    if(isEmptyListJ(*Jurados) == true){                                      //comprobamos si la lista esta vacia
        printf("+ Error: Disqualify not possible\n");
        return;
    }
    tPosJ i = firstJ(*Jurados);

    for(i ; i != NULLJ ; i = nextJ(i  , *Jurados)){                         //empezando desde la posicion inicial de la lista jurados
        tItemJ Juradoi = getItemJ(i , *Jurados);                            //buscamos el item participante con el nombre proporcionado por el usuario
        tPosP j = findItemP(participantName , Juradoi.participantList);

        if(j != NULLP){                                                     //si  ese nombre se encuentra en la lista entonces
            tItemP PartVotes = getItemP(j ,Juradoi.participantList);        //se cambian lso valores de votos como indica el enunciado en el caso discualify
            Juradoi.nullVotes += PartVotes.numVotes;                        // se elimina el participante de la lista participantes
            Juradoi.validVotes -= PartVotes.numVotes;                       // y se actualiza el item jurado con su listapartticipantes si ese participante
            deleteAtPositionP(j , &Juradoi.participantList);
            updateItemJ(Juradoi , i , Jurados);
            printf("Jury %s\n" , Juradoi.juryName);
            printf("Participant %s disqualified\n \n" , participantName);
        }else{
            printf("Jury %s\n" , Juradoi.juryName);                         //en caso de q no exista el participante en la lista se imprime el error
            printf("No participant %s\n \n" , participantName);
        }
    }

}

void Remove(tListJ *Jurados){
    if(isEmptyListJ(*Jurados)){
        printf("+ Error: Remove not possible\n");
        return;
    }
    int juradosEliminados = 0;                                          //utilizamos esta variable para comprobar si se ha eliminado algun jurado , pues en caso de q no debemos imprimir un error mas abajo
    tPosJ i = firstJ(*Jurados);

    while (i !=NULLJ){
        tItemJ Juradoi = getItemJ(i , *Jurados);                        //se comprueba q los votos validos sean 0 , q la lista no este vacia y q el item q se intenta eliminar exista
        if(Juradoi.validVotes == 0 && !isEmptyListJ(*Jurados) && findItemJ(getItemJ(i , *Jurados).juryName , *Jurados) != NULLJ){           //
            deleteAtPositionJ(i , Jurados);                             //se elimina el item y se aumenta la variable juradoseliminados
            juradosEliminados++;
            printf("* Remove: jury %s\n" , Juradoi.juryName);
        }else if(isEmptyListJ(*Jurados)){                               //debemos insertar este else if pues si se borran todos los jurados la lista quedaria vacia y por tanto i no se actualizaria
            i = NULLJ;
        }else
            i = nextJ(i , *Jurados);
    }

    if(juradosEliminados == 0){
        printf("+ Error: Remove not possible\n");
    }
}

void Winners(tListJ *Jurados){

    if(isEmptyListJ(*Jurados)){
        printf("+ Error: Winners not possible\n");
        return;
    }

    bool empateEU;          //estas dos variables seriviran para almacenar si se produce empate o no
    bool empate_nonEU;
    tPosJ i = firstJ(*Jurados);

    for (i ; i!=NULLJ ; i = nextJ(i , *Jurados)) {

        tItemP ganadorEU;               //se crean los items para guardar los valores delos ganadores
        tItemP ganador_nonEU;
        ganadorEU.numVotes = -1;        //se inicializan los votos a -1 para q el primer participante sea considerado el ganador aunq tenga 0 votos
        ganador_nonEU.numVotes = -1;
        strcpy(ganadorEU.participantName , "N"); //se asigna la letra N a los ganadores para q si no existiesen participantes entonces la letra N seriviria para saber eso
        strcpy(ganador_nonEU.participantName  , "N");

        tItemJ Juradoi = getItemJ(i, *Jurados);
        tListP participantList = Juradoi.participantList;

        tPosP j;
        if(isEmptyListP(participantList)){
            j = NULLP;
        } else
            j = firstP(participantList);

        printf("Jury %s\n", Juradoi.juryName);

        for (j; j != NULLP; j = followingP(j, participantList)) { //recorremos la lista obteniendo cada participante

            tItemP Participantei = getItemP(j, participantList);

            if (j == firstP(participantList) && followingP(j, participantList) == NULLP &&  //comprobamos si el primer item es el único , por lo q es el ganador
                Participantei.EUParticipant == true) {
                ganadorEU = Participantei;
            } else if (j == firstP(participantList) && followingP(j, participantList) == NULLP && //lo mismo pero para non-eu
                       Participantei.EUParticipant == false) {
                ganador_nonEU = Participantei;
            } else if (Participantei.numVotes >= ganadorEU.numVotes && Participantei.EUParticipant == true) {   //comprobamos si los votos del participante 'n' son mas o lo smismos q los del ganador
                if(ganadorEU.numVotes == Participantei.numVotes && strcmp(ganadorEU.participantName , Participantei.participantName) != 0 ){ // y si es asi comprobamos si existe empate mirando si los votos son iguales y los nombres distintos
                    empateEU = true;
                }else {
                    empateEU = false;
                    ganadorEU = Participantei;
                }
            } else if (Participantei.numVotes >= ganador_nonEU.numVotes && Participantei.EUParticipant == false) { //lo mismmo pero para non-eu
                if (ganador_nonEU.numVotes == Participantei.numVotes && strcmp(ganador_nonEU.participantName , Participantei.participantName) != 0){
                    empate_nonEU = true;
                }else{
                    empate_nonEU = false;
                    ganador_nonEU = Participantei;
                }
            }

        }

        if (strcmp(ganadorEU.participantName, "N") == 0 || empateEU) { //comprobamos q el valor N haya variado o si existe empate , por lo q si no varia no existen ganadores
            printf("Location eu: No winner\n");
        } else {                                                                //se muestran los datos del gandor
            printf("Location eu: Participant %s numvotes %d\n", ganadorEU.participantName, ganadorEU.numVotes);
        }

        if (strcmp(ganador_nonEU.participantName, "N") == 0 || empate_nonEU) { //lo mismo pero para non-eu
            printf("Location non-eu: No winner\n");
        } else {
            printf("Location non-eu: Participant %s numvotes %d\n", ganador_nonEU.participantName,
                   ganador_nonEU.numVotes);
        }

        printf("\n");
    }
}

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3 , tListJ *Jurados) {

    switch (command) {
        case 'C':
            printf("********************\n");
            printf("%s %c: jury %s totalvoters %s\n" , commandNumber , command , param1 , param2);//Imprimimos  la cabecera y pasamos valores a la funcion
            Create(Jurados , param1 , param2);
            break;
        case 'N':
            printf("********************\n");
            printf("%s %c: jury %s participant %s location %s\n" , commandNumber , command , param1 , param2, param3);//Imprimimos  la cabecera y pasamos valores a la funcion
            New(Jurados , param1 , param2 , param3);
            break;
        case 'V':
            printf("********************\n");
            printf("%s %c: jury %s participant %s\n" , commandNumber , command , param1 , param2);//Imprimimos  la cabecera y pasamos valores a la funcion
            Vote(Jurados , param1 , param2);
            break;
        case 'D':
            printf("********************\n");
            printf("%s %c: participant %s\n" , commandNumber , command , param1);//Imprimimos  la cabecera y pasamos valores a la funcion
            Dissqualify(Jurados , param1);
            break;
        case 'S':
            printf("********************\n");
            printf("%s %c:\n" , commandNumber , command);//Imprimimos  la cabecera y pasamos valores a la funcion
            Stats(Jurados);
            break;
        case 'R':
            printf("********************\n");
            printf("%s %c:\n" , commandNumber , command);//Imprimimos  la cabecera y pasamos valores a la funcion
            Remove(Jurados);
            break;
        case 'W':
            printf("********************\n");
            printf("%s %c:\n" ,commandNumber , command);//Imprimimos  la cabecera y pasamos valores a la funcion
            Winners(Jurados);
            break;
        default:
            break;
    }
}

void readTasks(char *filename , tListJ *Jurados) {

    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3 , Jurados);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {

    tListJ Jurados;
    createEmptyListJ(&Jurados);

    char *file_name = "create.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name , &Jurados);

    return 0;
}
