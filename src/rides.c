#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h>
#include <ctype.h>
#include "parse.h"
#include "rides.h"
#include "helpers.h"
#include "valid.h"
#include "free.h"

RidesCollection *build_Rides(const char *filename) {
    // Allocate memory for the RidesCollection struct
    RidesCollection *collection = malloc(sizeof(RidesCollection));

    // Allocate an array of Rides
    Ride *rides = malloc(sizeof(Ride));
    int rides_capacity=1;
    int num_valid_rows=0;

    // Open the file
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: could not open file %s\n", filename);
        return NULL;
    }

    // Read each line of the file
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, file)) != -1) {
        char **array_tokens=parse(line,";");

        if (strlen(array_tokens[0])>0 && strlen(array_tokens[2])>0 && strlen(array_tokens[3])>0 && strlen(array_tokens[4])>0 
        && strlen(array_tokens[6])>0 && strlen(array_tokens[7])>0 && strlen(array_tokens[8])>0
        && date_valid(array_tokens[1]) && is_int_string(array_tokens[5]) && atoi(array_tokens[5])>0 
        && is_decimal_string(array_tokens[6]) && is_decimal_string(array_tokens[7]) && is_decimal_string(array_tokens[8])
        && atof(array_tokens[6])>0.0 && atof(array_tokens[7])>0.0 && atof(array_tokens[8])>=0.0){

            if (num_valid_rows == rides_capacity) {
                rides_capacity *= 2;
                rides = realloc(rides, rides_capacity * sizeof(Ride));
            }           

            // Store the values in the Ride struct
            rides[num_valid_rows] = (Ride){
                .id = strdup(array_tokens[0]),
                .date_number=data_number(array_tokens[1]),
                .date=strdup(array_tokens[1]),
                .driver = strdup(array_tokens[2]),
                .user = strdup(array_tokens[3]),
                .city = strdup(array_tokens[4]),
                .distance = atoi(array_tokens[5]),
                .score_user = atof(array_tokens[6]),
                .score_driver = atof(array_tokens[7]),
                .tip = atof(array_tokens[8]) 
            };
            num_valid_rows++;
        }
        free_array_tokens(array_tokens,10);
    }
    free(line);
    // Close the file
    fclose(file);  

    collection->num_valid_rows=num_valid_rows;
    collection->rides=rides;
    return collection;
} 

void create_RidesHash(RidesCollection *collection) {
    // Create the hashtable
    collection->RidesHash = g_hash_table_new(g_str_hash, g_str_equal);

    // Add the Ride structs to the hashtable
    for (int i = 0; i < collection->num_valid_rows; i++) {
        Ride *ride = &(collection->rides[i]);
        g_hash_table_insert(collection->RidesHash, ride->id, ride);
    }
}


char* get_rides_id(GHashTable* RidesHash,char *id){
    Ride* ride = g_hash_table_lookup(RidesHash, id);
    char *rideID = strdup(ride->id); //name is rideID and not id because of the id received as argument
    return rideID;
}

int get_rides_date_number(GHashTable* RidesHash,char *id){
    Ride* ride = g_hash_table_lookup(RidesHash, id);
    int date_number = ride->date_number;
    return date_number;
}

char* get_rides_driver(GHashTable* RidesHash,char *id){
    Ride* ride = g_hash_table_lookup(RidesHash, id);
    char *driver = strdup(ride->driver);
    return driver;
}

char* get_rides_user(GHashTable* RidesHash,char *id){
    Ride* ride = g_hash_table_lookup(RidesHash, id);
    char *user = strdup(ride->user);
    return user;
}

char* get_rides_city(GHashTable* RidesHash,char *id){
    Ride* ride = g_hash_table_lookup(RidesHash, id);
    char *city = strdup(ride->city);
    return city;
}

int get_rides_distance(GHashTable* RidesHash,char *id){
    Ride* ride = g_hash_table_lookup(RidesHash, id);
    int distance = ride->distance;
    return distance;
}

double get_rides_score_user(GHashTable* RidesHash,char *id){
    Ride* ride = g_hash_table_lookup(RidesHash, id);
    double score_user = ride->score_user;
    return score_user;
}

double get_rides_score_driver(GHashTable* RidesHash,char *id){
    Ride* ride = g_hash_table_lookup(RidesHash, id);
    double score_driver = ride->score_driver;
    return score_driver;
}

double get_rides_tip(GHashTable* RidesHash,char *id){
    Ride* ride = g_hash_table_lookup(RidesHash, id);
    double tip = ride->tip;
    return tip;
}

char* get_rides_date(GHashTable* RidesHash,char *id){
    Ride* ride = g_hash_table_lookup(RidesHash, id);
    char *date = strdup(ride->date);
    return date;
}

char** get_rides_keys(GHashTable* RidesHash){
    uint length;
    char** KeysRides = (char **) g_hash_table_get_keys_as_array (RidesHash,&length);
    return KeysRides;
}