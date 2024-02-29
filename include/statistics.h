#ifndef STATISTICS_H
#define STATISTICS_H

#include "q.h"

typedef struct {
    int length_Q5_6;
    int length_feminino;
    int length_masculino;
    int length_Q9;
    Q5_6** sorted_Q5_6_array;
    Q8** sorted_Q8_feminino_array;
    Q8** sorted_Q8_masculino_array;
    Q9** sorted_Q9_array;
    GHashTable *StatisticsHash;
} StatisticsCollection;

typedef struct {
    int nViagens;
    int finalDate_number;
    int type; //0
    double avaliacaoMedia;
    double totalAuferido; 
} StatisticsDrivers;

typedef struct {
    int distanciaTotal;
    int finalDate_number;
    int type; //1
    int nViagens; 
    double totalGasto; 
    double avaliacaoMedia;
} StatisticsUsers;

typedef struct {
    int nViagens;
    int type; //2
    double precoMedio;
} StatisticsCity;

StatisticsCollection* create_StatisticsCollection (GHashTable* DriversHash, GHashTable* RidesHash,GHashTable* UsersHash);

//gets

double get_statisticsDrivers_avaliacaoMedia(GHashTable* StatisticsHash,char *id);
int get_statisticsDrivers_nViagens(GHashTable* StatisticsHash,char *id);
double get_statisticsDrivers_totalAuferido(GHashTable* StatisticsHash,char *id);
int get_statisticsDrivers_finalDate_number(GHashTable* StatisticsHash,char *id);
double get_StatisticsUsers_avaliacaoMedia(GHashTable* StatisticsHash,char *id);
int get_StatisticsUsers_nViagens(GHashTable* StatisticsHash,char *id);
double get_StatisticsUsers_totalGasto(GHashTable* StatisticsHash,char *id);
int get_StatisticsUsers_distanciaTotal(GHashTable* StatisticsHash,char *id);
int get_StatisticsUsers_finalDate_number(GHashTable* StatisticsHash,char *id);
double get_StatisticsCity_precoMedio(GHashTable* StatisticsHash,char *id);
int get_StatisticsCity_nViagens(GHashTable* StatisticsHash,char *id);
int statistics_contains(GHashTable* StatisticsHash,char *id);

#endif