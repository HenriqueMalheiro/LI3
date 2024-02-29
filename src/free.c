#include <stdlib.h>
#include <stdbool.h>
#include "parse.h"
#include "drivers.h"
#include "users.h"
#include "rides.h"
#include "statistics.h"

void free_array_tokens(char ** array_tokens,int lenght_array_tokens){
    for (int i = 0; i < lenght_array_tokens; i++) {
        free(array_tokens[i]);
    }
    free(array_tokens);  
}

//Free drivers array and their values
void free_driver(Driver* driver) {
    free(driver->id);
    free(driver->name);
    free(driver->gender);
    free(driver->car_class);
    free(driver->city);
    free(driver->account_status);
}

void free_array_drivers(Driver* drivers, int num_valid_rows){
    for (int i = 0; i < num_valid_rows; i++) {
        free_driver(&drivers[i]);
    }
    free(drivers);
}

//Free the collections
void free_DriversCollection(DriversCollection* collection){
    g_hash_table_destroy(collection->DriversHash);
    free_array_drivers(collection->drivers,collection->num_valid_rows);

    for (int i = 0; i < collection->lenght_sorted_Drivers_array; i++) {
        free(collection->sorted_Drivers_array[i]);
    }
    free(collection->sorted_Drivers_array);
    free(collection);
}

//Free users array and their values
void free_user(User* user) {
    free(user->username);
    free(user->name);
    free(user->gender);
    free(user->account_status);
}

void free_array_users(User* users, int num_valid_rows){
    for (int i = 0; i < num_valid_rows; i++) {
        free_user(&users[i]);
    }
    free(users);
}

void free_UsersCollection(UsersCollection* collection){
    g_hash_table_destroy(collection->UsersHash);
    free_array_users(collection->users,collection->num_valid_rows);

    for (int i = 0; i < collection->lenght_sorted_Users_array; i++) {
        free(collection->sorted_Users_array[i]);
    }
    free(collection->sorted_Users_array);
    free(collection);
}

//Free rides array and their values
void free_ride(Ride* ride) {
    free(ride->id);
    free(ride->date);
    free(ride->driver);
    free(ride->user);
    free(ride->city);
}

void free_array_rides(Ride* rides, int num_valid_rows){
    for (int i = 0; i < num_valid_rows; i++) {
        free_ride(&rides[i]);
    }
    free(rides);
}

void free_RidesCollection(RidesCollection* collection){
    g_hash_table_destroy(collection->RidesHash);
    free_array_rides(collection->rides,collection->num_valid_rows);
    free(collection);
} 

bool is_of_type_StatisticsDrivers(gpointer value) {
    return ((StatisticsDrivers*)value)->type == 0;
}

bool is_of_type_StatisticsCity(gpointer value) {
    return ((StatisticsCity*)value)->type == 2;
}

bool is_of_type_StatisticsUsers(gpointer value) {
    return ((StatisticsUsers*)value)->type == 1;
}

void free_StatisticsHash (GHashTable* StatisticsHash){
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, StatisticsHash);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        if (is_of_type_StatisticsDrivers(value)){
            StatisticsDrivers *driverPointer = (StatisticsDrivers *)value;
            free(driverPointer);
        }
        else if (is_of_type_StatisticsUsers(value)) {
            StatisticsUsers *userPointer = (StatisticsUsers *)value;
            free(userPointer);
        }
        else if (is_of_type_StatisticsCity(value)){
            StatisticsCity *cityPointer = (StatisticsCity *)value;
            free(cityPointer);
        }
    }
    g_hash_table_destroy(StatisticsHash);
}

void free_StatisticsCollection(StatisticsCollection* collection) {
    free_StatisticsHash(collection->StatisticsHash);

    int i;
    for (i = 0; i < collection->length_Q9; i++)
        free(collection->sorted_Q9_array[i]);
    free(collection->sorted_Q9_array);

    for (i = 0; i < collection->length_feminino; i++)
        free(collection->sorted_Q8_feminino_array[i]);
    free(collection->sorted_Q8_feminino_array);

    for (i = 0; i < collection->length_masculino; i++)
        free(collection->sorted_Q8_masculino_array[i]);
    free(collection->sorted_Q8_masculino_array);

    for (i = 0; i < collection->length_Q5_6; i++)
        free(collection->sorted_Q5_6_array[i]);
    free(collection->sorted_Q5_6_array);

    free(collection);
}

void free_driversHash_Q7 (GHashTable* driversHash_Q7){
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, driversHash_Q7);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Driver_Q7 *driverPointer = (Driver_Q7 *)value;
        free(driverPointer);
    }
    g_hash_table_destroy(driversHash_Q7);
}

void free_Q7_collection (Q7_collection *q7_collection){
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, q7_collection->citysHash_Q7);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        City_Q7 *cityPointer = (City_Q7 *)value;
        free_driversHash_Q7(cityPointer->driversHash_Q7);
        free(cityPointer);
    }
    g_hash_table_destroy(q7_collection->citysHash_Q7);
    free(q7_collection);
}