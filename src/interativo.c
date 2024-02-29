#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <glib.h>
#include <sys/time.h>
#include <unistd.h>
#include "parse.h"
#include "users.h"
#include "drivers.h"
#include "rides.h"
#include "statistics.h"
#include "helpers.h"
#include "query_selector.h"
#include "free.h"
#include "valid.h"

void query_selector_interativo( UsersCollection* userscollection, DriversCollection* driverscollection, 
    RidesCollection* ridescollection, StatisticsCollection* statisticscollection,Q7_collection* q7_collection){

    printf(" .............................................................Menu.............................................................\n 0 - Sair do programa\n 1 - Q1: Lista o resumo de um perfil através do seu id/username\n 2 - Q2: Lista os N condutores com maior avaliação média\n 3 - Q3: Lista os N utilizadores com maior distância viajada\n 4 - Q4: Preço médio das viagens numa determinada cidade\n 5 - Q5: Preço médio das viagens num dado intervalo de tempo\n 6 - Q6: Distância média percorrida, numa determinada cidade, num dado intervalo de tempo\n 7 - Q7: Top N condutores numa determinada cidade\n 8 - Q8: Lista todas as viagens nas quais o utilizador e o condutor são do género passado e têm perfis com X ou mais anos\n 9 - Q9: Lista as viagens nas quais o passageiro deu gorjeta, num dado intervalo de tempo \n................................................................................................................................\n\nIntroduza o número da operação que pretende realizar: ");
            
    char querie[64];
    scanf("%s",querie);
    if (strlen(querie)==1 && isdigit(querie[0])){
        printf("\n");
        int num=atoi(querie);

        char arg1[64],arg2[64],arg3[64];
        switch (num) {
            case 0:
                exit(0);
            case 1:
                printf("Introduza o ID: ");
                scanf("%s",arg1);
                if (!(g_hash_table_contains(userscollection->UsersHash, arg1) || g_hash_table_contains(driverscollection->DriversHash, arg1))){
                    printf("Argumento inválido!\n\n");
                    query_selector_interativo(userscollection,driverscollection,ridescollection,statisticscollection,q7_collection);
                }
                printf("\n");
                q1(userscollection->UsersHash, driverscollection->DriversHash,statisticscollection->StatisticsHash, arg1, (-1));
                break;
            case 2:
                printf("Introduza o N: ");
                scanf("%s",arg1);
                for (int i=0;i<strlen(arg1);i++){
                    if (!isdigit(arg1[i])){
                        printf("Argumento inválido!\n\n");
                        query_selector_interativo(userscollection,driverscollection,ridescollection,statisticscollection,q7_collection);
                    }
                }
                q2(atoi(arg1), driverscollection->DriversHash, driverscollection->sorted_Drivers_array, (-1));
                break;
            case 3:
                printf("Introduza o N: ");
                scanf("%s",arg1);
                for (int i=0;i<strlen(arg1);i++){
                    if (!isdigit(arg1[i])){
                        printf("Argumento inválido!\n\n");
                        query_selector_interativo(userscollection,driverscollection,ridescollection,statisticscollection,q7_collection);
                    }
                }
                q3(atoi(arg1), userscollection->UsersHash, userscollection->sorted_Users_array, (-1));
                break;
            case 4:
                printf("Introduza o cidade: ");
                scanf("%s",arg1);
                if (!g_hash_table_contains(statisticscollection->StatisticsHash, arg1)){
                    printf("Argumento inválido!\n\n");
                    query_selector_interativo(userscollection,driverscollection,ridescollection,statisticscollection,q7_collection); 
                }
                printf("\n");
                q4(statisticscollection->StatisticsHash, arg1,(-1));
                break;
            case 5:
                printf("Introduza a primeira data (xx/xx/xxxx): ");
                scanf("%s",arg1);
                if(!date_valid(arg1)){
                    printf("Argumento inválido!\n\n");
                    query_selector_interativo(userscollection,driverscollection,ridescollection,statisticscollection,q7_collection);
                }
                printf("Introduza a segunda data (xx/xx/xxxx): ");
                scanf("%s",arg2);
                if(!date_valid(arg2)){
                    printf("Argumento inválido!\n\n");
                    query_selector_interativo(userscollection,driverscollection,ridescollection,statisticscollection,q7_collection);
                }
                printf("\n");
                q5(statisticscollection->sorted_Q5_6_array,statisticscollection->length_Q5_6, 
                arg1, arg2, (-1)); 
                break;
            case 6:
                printf("Introduza a cidade: ");
                scanf("%s",arg1);
                if (!g_hash_table_contains(statisticscollection->StatisticsHash, arg1)){
                    printf("Argumento inválido!\n\n");
                    query_selector_interativo(userscollection,driverscollection,ridescollection,statisticscollection,q7_collection); 
                }
                printf("Introduza a primeira data (xx/xx/xxxx): ");
                scanf("%s",arg2);
                if(!date_valid(arg2)){
                    printf("Argumento inválido!\n\n");
                    query_selector_interativo(userscollection,driverscollection,ridescollection,statisticscollection,q7_collection);
                }
                printf("Introduza a segunda data (xx/xx/xxxx): ");
                scanf("%s",arg3);
                if(!date_valid(arg3)){
                    printf("Argumento inválido!\n\n");
                    query_selector_interativo(userscollection,driverscollection,ridescollection,statisticscollection,q7_collection);
                }
                printf("\n");
                q6(statisticscollection->StatisticsHash,statisticscollection->sorted_Q5_6_array,
                statisticscollection->length_Q5_6, arg1, arg2, arg3, (-1));

                break;
            case 7:
                printf("Top N: ");
                scanf("%s",arg1);
                for (int i=0;i<strlen(arg1);i++){
                    if (!isdigit(arg1[i])){
                        printf("Argumento inválido!\n\n");
                        query_selector_interativo(userscollection,driverscollection,ridescollection,statisticscollection,q7_collection);
                    }
                }
                printf("Cidade: ");
                scanf("%s",arg2);
                if (!g_hash_table_contains(statisticscollection->StatisticsHash, arg2)){
                    printf("Argumento inválido!\n\n");
                    query_selector_interativo(userscollection,driverscollection,ridescollection,statisticscollection,q7_collection); 
                }
                q7(statisticscollection->StatisticsHash,driverscollection->DriversHash,q7_collection,atoi(arg1),arg2,(-1));
                break;
            case 8:
                printf("Genero: ");
                scanf("%s",arg1);
                if (!((!strcmp(arg1,"F")) || (!strcmp(arg1,"M")))){
                    printf("Argumento inválido!\n\n");
                    query_selector_interativo(userscollection,driverscollection,ridescollection,statisticscollection,q7_collection); 
                }
                printf("Idade dos perfis: ");
                scanf("%s",arg2);
                for (int i=0;i<strlen(arg1);i++){
                    if (!isdigit(arg2[i])){
                        printf("Argumento inválido!\n\n");
                        query_selector_interativo(userscollection,driverscollection,ridescollection,statisticscollection,q7_collection);
                    }
                }
                if (!strcmp(arg1,"F")){
                    q8(ridescollection->RidesHash,driverscollection->DriversHash,userscollection->UsersHash,statisticscollection->sorted_Q8_feminino_array,statisticscollection->length_feminino, atoi(arg2), (-1));
                }else{
                    if (!strcmp(arg1,"M")){
                    q8(ridescollection->RidesHash,driverscollection->DriversHash,userscollection->UsersHash,statisticscollection->sorted_Q8_masculino_array,statisticscollection->length_masculino, atoi(arg2), (-1));
                    }
                }
                break;
            case 9:
                printf("Introduza a primeira data (xx/xx/xxxx): ");
                scanf("%s",arg1);
                if(!date_valid(arg1)){
                    printf("Argumento inválido!\n\n");
                    query_selector_interativo(userscollection,driverscollection,ridescollection,statisticscollection,q7_collection);
                }
                printf("Introduza a segunda data (xx/xx/xxxx): ");
                scanf("%s",arg2);
                if(!date_valid(arg2)){
                    printf("Argumento inválido!\n\n");
                    query_selector_interativo(userscollection,driverscollection,ridescollection,statisticscollection,q7_collection);
                }
                q9(ridescollection->RidesHash,statisticscollection->sorted_Q9_array,statisticscollection->length_Q9, arg1, arg2, (-1));
                break;
            default:
                printf("Error! operator is not correct");   
        }
        query_selector_interativo(userscollection,driverscollection,ridescollection,statisticscollection,q7_collection);
    }else{
        printf("Erro! Introduza um dos numeros acima mencionados!\n\n");
        query_selector_interativo(userscollection,driverscollection,ridescollection,statisticscollection,q7_collection);
    }

    }

void interativo(){
    printf("Diretoria para a pasta dos datasets (0 para sair): ");
    char diretoria[64];
    scanf("%s",diretoria);

    if (!strcmp("0",diretoria)){
        return;
    }
    printf("\n");

    char *dirUsers;
    char *dirDrivers;
    char *dirRides;

    dirUsers = malloc(strlen(diretoria) + strlen("/users.csv") + 1);
    dirDrivers = malloc(strlen(diretoria) + strlen("/drivers.csv") + 1);
    dirRides = malloc(strlen(diretoria) + strlen("/rides.csv") + 1);

    sprintf(dirUsers, "%s/users.csv", diretoria);
    sprintf(dirDrivers, "%s/drivers.csv", diretoria);
    sprintf(dirRides, "%s/rides.csv", diretoria);

    FILE *file1 = fopen(dirUsers, "r");
    FILE *file2 = fopen(dirDrivers, "r");
    FILE *file3 = fopen(dirRides, "r");
    if ((!file1) ||(!file2) || (!file3) ) {
        printf("Erro na diretoria.\n");
        interativo();   
    }

    //Makes the parse of the 3 csvs and the file with the queries inputs and their builds, freeing the memory once it is not needed anymore
    UsersCollection *userscollection = build_Users(dirUsers);
    free(dirUsers);

    DriversCollection *driverscollection = build_Drivers(dirDrivers); 
    free(dirDrivers);

    RidesCollection *ridescollection = build_Rides(dirRides);
    free(dirRides);

    //Creates the collections of the 3 CSVs and the statistics, using the rides from the rides.csv 
    create_UsersHash (userscollection);
    create_DriversHash (driverscollection);
    create_RidesHash (ridescollection);
    StatisticsCollection *statisticscollection = create_StatisticsCollection(driverscollection->DriversHash,ridescollection->RidesHash,userscollection->UsersHash);

    //Functions that saves in the collection an sorted array, that will be used in the Q2 and Q3 
    sortDriversArray(driverscollection,statisticscollection->StatisticsHash);
    sortUsersArray(userscollection,statisticscollection->StatisticsHash);

    //Q7_collection that has stored the hash of hashes to be used in the Q7
    Q7_collection *q7_collection = create_Q7_collection(ridescollection->RidesHash);

    query_selector_interativo(userscollection,driverscollection,ridescollection,statisticscollection,q7_collection);

    //Free the collections
    free_Q7_collection(q7_collection);
    free_StatisticsCollection(statisticscollection);
    free_DriversCollection(driverscollection);
    free_UsersCollection(userscollection);
    free_RidesCollection(ridescollection);
}