#ifndef RIDES_H
#define RIDES_H

#include <glib.h>
#include "parse.h"

typedef struct {
    int distance;
    int date_number;
    double score_user;
    double score_driver;
    double tip;
    char *id;    
    char *date;
    char *driver;
    char *user;
    char *city;
} Ride;

typedef struct {
    int num_valid_rows;
    Ride* rides;
    GHashTable *RidesHash;
} RidesCollection;

RidesCollection *build_Rides(const char *filename);

void create_RidesHash(RidesCollection *collection);

//gets
char* get_rides_id(GHashTable* RidesHash,char *id);
int get_rides_date_number(GHashTable* RidesHash,char *id);
char* get_rides_date(GHashTable* RidesHash,char *id);
char* get_rides_driver(GHashTable* RidesHash,char *id);
char* get_rides_user(GHashTable* RidesHash,char *id);
char* get_rides_city(GHashTable* RidesHash,char *id);
int get_rides_distance(GHashTable* RidesHash,char *id);
double get_rides_score_user(GHashTable* RidesHash,char *id);
double get_rides_score_driver(GHashTable* RidesHash,char *id);
double get_rides_tip(GHashTable* RidesHash,char *id);
char** get_rides_keys(GHashTable* RidesHash);

#endif