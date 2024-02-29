#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h>
#include <ctype.h>
#include "users.h"
#include "drivers.h"
#include "rides.h"
#include "statistics.h"
#include "helpers.h"
#include "q.h"

StatisticsCollection* create_StatisticsCollection (GHashTable* DriversHash, GHashTable* RidesHash,  GHashTable* UsersHash) {
    StatisticsCollection *collection = malloc(sizeof(StatisticsCollection));
    
    collection->StatisticsHash = g_hash_table_new(g_str_hash, g_str_equal);

    //usar os gets rides_Keys 
    uint length;
    char** KeysRides = (char **) g_hash_table_get_keys_as_array (RidesHash,&length);

    int numRides = g_hash_table_size(RidesHash);
    
    double tarifa;

    //Para os reallocs
    int capacidade_f=1,capacidade_m=1; //Da Q8
    int capacidade_Q56=1,ocupacao_total_Q56=0; //Da Q5_6
    int capacidade_Q9=1,ocupacao_total_Q9=0; //Da Q9

    Q5_6** sortedQ5_6 = malloc(sizeof(Q5_6*));
    Q8** sortedQ8_feminino = malloc(sizeof(Q8*));
    Q8** sortedQ8_masculino = malloc(sizeof(Q8*));
    Q9** sortedQ9 = malloc(sizeof(Q9*));
    int lenght_feminino=0, length_masculino=0, length_Q9=0;

    for (int i = 0; i < numRides; i++) {
        Ride* ride = g_hash_table_lookup(RidesHash, KeysRides[i]);
        char* id =ride->id;
        int date_number=ride->date_number;
        char* driverID = ride->driver;
        char* username = ride->user;
        char* city = ride->city;
        int distance = ride->distance;
        double tip = ride->tip;
        double score_user = ride->score_user;
        double score_driver = ride->score_driver;
        char* car_class = get_drivers_car_class(DriversHash,driverID);
        char* drivers_gender = get_drivers_gender(DriversHash,driverID);
        char* users_gender = get_users_gender(UsersHash,username);
        char* drivers_account_status = get_drivers_account_status(DriversHash,driverID);
        char* users_account_status = get_users_account_status(UsersHash,username);
        int drivers_account_creation = get_drivers_account_creation(DriversHash,driverID);
        int users_account_creation = get_users_account_creation(UsersHash,username);


        StatisticsDrivers* driverPointer = NULL;
        StatisticsUsers* userPointer = NULL;
        StatisticsCity* cityPointer = NULL;

        //Inicio Q5_6
        Q5_6* atualQ5_6 = malloc(sizeof(Q5_6));
        ++ocupacao_total_Q56;
        if (ocupacao_total_Q56 > capacidade_Q56) {
            capacidade_Q56 *= 2;
            sortedQ5_6 = realloc(sortedQ5_6, capacidade_Q56 * sizeof(Q5_6*));
        }
        atualQ5_6->data = date_number;
        atualQ5_6->city = city;
        atualQ5_6->distance = distance;

        //Criar os arrays da QUERIE Q8
        if (!strcmp(drivers_gender,"F") && !strcmp(users_gender,"F")){
            if (!(strcmp(drivers_account_status,"active")) && !(strcmp(users_account_status,"active"))){
                Q8* atual_Q8 = malloc(sizeof(Q8));
                if (lenght_feminino == capacidade_f) {
                    capacidade_f *= 2;
                    sortedQ8_feminino = realloc(sortedQ8_feminino, capacidade_f * sizeof(Q8*));
                }
                atual_Q8->id_ride=id;
                atual_Q8->conta_driver=drivers_account_creation;
                atual_Q8->conta_user=users_account_creation;

                if(atual_Q8->conta_user>atual_Q8->conta_driver){
                    atual_Q8->idade_menor=idade(atual_Q8->conta_user);
                }else{
                    atual_Q8->idade_menor=idade(atual_Q8->conta_driver);
                }
                sortedQ8_feminino[lenght_feminino++] = atual_Q8;
            }
        }else{
            if (!strcmp(drivers_gender,"M") && !strcmp(users_gender,"M")){
                if (!(strcmp(users_account_status,"active")) && !(strcmp(drivers_account_status,"active"))){
                    Q8* atual_Q8 = malloc(sizeof(Q8));
                    if (length_masculino == capacidade_m) {
                        capacidade_m *= 2;
                        sortedQ8_masculino = realloc(sortedQ8_masculino, capacidade_m * sizeof(Q8*));
                    }
                    atual_Q8->id_ride=id;
                    atual_Q8->conta_driver=drivers_account_creation;
                    atual_Q8->conta_user=users_account_creation;

                    if(atual_Q8->conta_user>atual_Q8->conta_driver){
                        atual_Q8->idade_menor=idade(atual_Q8->conta_user);
                    }else{
                        atual_Q8->idade_menor=idade(atual_Q8->conta_driver);
                    }
                    sortedQ8_masculino[length_masculino++] = atual_Q8;
                }
            }
        }

        //Criar o array da Q9
        ++ocupacao_total_Q9;
        if (ocupacao_total_Q9 > capacidade_Q9) {
            capacidade_Q9 *= 2;
            sortedQ9 = realloc(sortedQ9, capacidade_Q9 * sizeof(Q9*));
        }
        if (tip>0){
            Q9* atual_Q9 = malloc(sizeof(Q9));
            atual_Q9->date_ride=date_number;
            atual_Q9->distance=distance;
            atual_Q9->id_ride=id;
            sortedQ9[length_Q9]=atual_Q9;
            ++length_Q9;
        }


        if (!g_hash_table_contains(collection->StatisticsHash, driverID)) {
            driverPointer = malloc(sizeof(StatisticsDrivers));
            driverPointer->avaliacaoMedia = 1;
            driverPointer->nViagens = 0;
            driverPointer->finalDate_number=date_number;
            driverPointer->type=0;
            driverPointer->totalAuferido = 0;
            g_hash_table_insert(collection->StatisticsHash, driverID, driverPointer);
        }
        else {
            driverPointer = g_hash_table_lookup(collection->StatisticsHash, driverID);
        }

        if (!g_hash_table_contains(collection->StatisticsHash, username)) {
            userPointer = malloc(sizeof(StatisticsUsers));
            userPointer->avaliacaoMedia = 1;
            userPointer->nViagens = 0;
            userPointer->finalDate_number=date_number;
            userPointer->distanciaTotal = 0;
            userPointer->type=1;
            userPointer->totalGasto=0;
            g_hash_table_insert(collection->StatisticsHash, username, userPointer);
        }
        else {
            userPointer = g_hash_table_lookup(collection->StatisticsHash, username);
        }

        if (!g_hash_table_contains(collection->StatisticsHash, city)) {
            cityPointer = malloc(sizeof(StatisticsCity));
            cityPointer->precoMedio = 1;
            cityPointer->nViagens = 0;
            cityPointer->type=2;
            g_hash_table_insert(collection->StatisticsHash, city, cityPointer);
        }
        else {
            cityPointer = g_hash_table_lookup(collection->StatisticsHash, city);
        }

        userPointer->distanciaTotal += distance;

        userPointer->avaliacaoMedia= ((userPointer->avaliacaoMedia)*(userPointer->nViagens)+score_user)/((userPointer->nViagens)+1);
        userPointer->nViagens+=1;

        driverPointer->avaliacaoMedia= ((driverPointer->avaliacaoMedia)*(driverPointer->nViagens)+score_driver)/((driverPointer->nViagens)+1);
        driverPointer->nViagens+=1;


        if (date_number>driverPointer->finalDate_number) driverPointer->finalDate_number=date_number;

        if (date_number>userPointer->finalDate_number) userPointer->finalDate_number=date_number;
           

        if (!(strcmp(car_class,"basic"))){
            tarifa = 3.25 + 0.62*distance;
            driverPointer->totalAuferido+=(tarifa+tip);
            userPointer->totalGasto+=(tarifa+tip);
            cityPointer->precoMedio=((cityPointer->precoMedio)*(cityPointer->nViagens)+tarifa)/((cityPointer->nViagens)+1);
            cityPointer->nViagens+=1;  
            atualQ5_6->preco = tarifa;
        }else{
            if (!(strcmp(car_class,"green"))){
                tarifa = 4.00 + 0.79*distance;
                driverPointer->totalAuferido+=(tarifa+tip);
                userPointer->totalGasto+=(tarifa+tip);
                cityPointer->precoMedio=((cityPointer->precoMedio)*(cityPointer->nViagens)+tarifa)/((cityPointer->nViagens)+1);
                cityPointer->nViagens+=1;
                atualQ5_6->preco = tarifa;
            }else{
                tarifa=5.20 + 0.94*distance;
                driverPointer->totalAuferido+=(tarifa+tip);
                userPointer->totalGasto+=(tarifa+tip);
                cityPointer->precoMedio=((cityPointer->precoMedio)*(cityPointer->nViagens)+tarifa)/((cityPointer->nViagens)+1);
                cityPointer->nViagens+=1;
                atualQ5_6->preco = tarifa;
            }
        }
        //Frees the memory allocated from the strdup in the gets
        free(car_class);
        free(drivers_gender);
        free(users_gender);
        free(drivers_account_status);
        free(users_account_status);
        sortedQ5_6[i] = atualQ5_6;
    }   

    //Sorts the arrays and stored them in the statistics collection with their size
    qsort(sortedQ5_6, numRides, sizeof(Q5_6*), sort_Statistics_Q5_6);
    collection->sorted_Q5_6_array = sortedQ5_6;
    collection->length_Q5_6=numRides;

    qsort(sortedQ8_feminino,lenght_feminino , sizeof(Q8*), sort_Statistics_Q8);
    qsort(sortedQ8_masculino,length_masculino , sizeof(Q8*), sort_Statistics_Q8);
    collection->sorted_Q8_feminino_array = sortedQ8_feminino;
    collection->sorted_Q8_masculino_array = sortedQ8_masculino;
    collection->length_feminino=lenght_feminino;
    collection->length_masculino=length_masculino;

    qsort(sortedQ9, length_Q9, sizeof(Q9*), sort_Statistics_Q9);
    collection->sorted_Q9_array = sortedQ9;
    collection->length_Q9=length_Q9;
    free(KeysRides);
    return collection;
}

double get_statisticsDrivers_avaliacaoMedia(GHashTable* StatisticsHash,char *id){
    StatisticsDrivers* statisticsDrivers = g_hash_table_lookup(StatisticsHash, id);
    double avaliacaoMedia=statisticsDrivers->avaliacaoMedia;
    return avaliacaoMedia;
} 

int get_statisticsDrivers_nViagens(GHashTable* StatisticsHash,char *id){
    StatisticsDrivers* statisticsDrivers = g_hash_table_lookup(StatisticsHash, id);
    int nViagens=statisticsDrivers->nViagens;
    return nViagens;
} 

double get_statisticsDrivers_totalAuferido(GHashTable* StatisticsHash,char *id){
    StatisticsDrivers* statisticsDrivers = g_hash_table_lookup(StatisticsHash, id);
    double totalAuferido=statisticsDrivers->totalAuferido;
    return totalAuferido;
} 

int get_statisticsDrivers_finalDate_number(GHashTable* StatisticsHash,char *id){
    StatisticsDrivers* statisticsDrivers = g_hash_table_lookup(StatisticsHash, id);
    int finalDate_number = statisticsDrivers->finalDate_number;
    return finalDate_number;
} 

double get_StatisticsUsers_avaliacaoMedia(GHashTable* StatisticsHash,char *id){
    StatisticsUsers* statisticsUsers = g_hash_table_lookup(StatisticsHash, id);
    double avaliacaoMedia=statisticsUsers->avaliacaoMedia;
    return avaliacaoMedia;
} 

int get_StatisticsUsers_nViagens(GHashTable* StatisticsHash,char *id){
    StatisticsUsers* statisticsUsers = g_hash_table_lookup(StatisticsHash, id);
    int nViagens=statisticsUsers->nViagens;
    return nViagens;
} 

double get_StatisticsUsers_totalGasto(GHashTable* StatisticsHash,char *id){
    StatisticsUsers* statisticsUsers = g_hash_table_lookup(StatisticsHash, id);
    double totalGasto=statisticsUsers->totalGasto;
    return totalGasto;
} 

int get_StatisticsUsers_distanciaTotal(GHashTable* StatisticsHash,char *id){
    StatisticsUsers* statisticsUsers = g_hash_table_lookup(StatisticsHash, id);
    int distanciaTotal=statisticsUsers->distanciaTotal;
    return distanciaTotal;
} 

int get_StatisticsUsers_finalDate_number(GHashTable* StatisticsHash,char *id){
    StatisticsUsers* statisticsUsers = g_hash_table_lookup(StatisticsHash, id);
    int finalDate_number = statisticsUsers->finalDate_number;
    return finalDate_number;
} 

double get_StatisticsCity_precoMedio(GHashTable* StatisticsHash,char *id){
    StatisticsCity* statisticsCity = g_hash_table_lookup(StatisticsHash, id);
    double precoMedio=statisticsCity->precoMedio;
    return precoMedio;
} 

int get_StatisticsCity_nViagens(GHashTable* StatisticsHash,char *id){
    StatisticsCity* statisticsCity = g_hash_table_lookup(StatisticsHash, id);
    int nViagens=statisticsCity->nViagens;
    return nViagens;
} 

int statistics_contains(GHashTable* StatisticsHash,char *id){
    int valor=0;
    if (g_hash_table_contains(StatisticsHash,id)) valor=1;        
    return valor;
}


