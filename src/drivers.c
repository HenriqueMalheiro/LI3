#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <glib.h>
#include "parse.h"
#include "drivers.h"
#include "statistics.h"
#include "helpers.h"
#include "q.h"
#include "rides.h"
#include "valid.h"
#include "free.h"

DriversCollection *build_Drivers(const char *filename) {
    // Allocate memory for the DriversCollection struct
    DriversCollection *collection = malloc(sizeof(DriversCollection));

    // Allocate an array of Drivers, but with one less than the number of rows
    Driver *drivers = malloc(sizeof(Driver));
    int drivers_capacity=1;
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

        char* account_status =array_tokens[8];
        account_status[strlen(account_status)-1] = '\0';
                
        if(strlen(array_tokens[0])>0 && strlen(array_tokens[1])>0 && strlen(array_tokens[3])>0 
        && strlen(array_tokens[5])>0 && strlen(array_tokens[6])>0 && date_valid(array_tokens[2]) 
        && date_valid(array_tokens[7])){

            if (num_valid_rows == drivers_capacity) {
                drivers_capacity *= 2;
                drivers = realloc(drivers, drivers_capacity * sizeof(Driver));
            } 

            // Store the values in the Driver struct
            drivers[num_valid_rows] = (Driver){
                .id = strdup(array_tokens[0]),
                .name = strdup(array_tokens[1]),
                .birth_date_number = data_number(array_tokens[2]),
                .gender = strdup(array_tokens[3]),
                .car_class = strdup(array_tokens[4]),
                .city = strdup(array_tokens[6]),
                .account_creation = data_number(array_tokens[7]),
                .account_status = strdup(account_status)
            };
            toLower_string(drivers[num_valid_rows].car_class);
            toLower_string(drivers[num_valid_rows].account_status);
            num_valid_rows++;
        }
        free_array_tokens(array_tokens,9);
    }
    free(line);
    // Close the file
    fclose(file);  

    collection->num_valid_rows=num_valid_rows;
    collection->drivers=drivers;
    return collection;
}


void create_DriversHash(DriversCollection *collection) {
    // Create the hashtable
    collection->DriversHash = g_hash_table_new(g_str_hash, g_str_equal);

    // Add the Driver structs to the hashtable
    for (int i = 0; i < collection->num_valid_rows; i++) {
        Driver *driver = &(collection->drivers[i]);
        g_hash_table_insert(collection->DriversHash, driver->id, driver);
    }
}

void sortDriversArray(DriversCollection* driverscollection,GHashTable* StatisticsHash) {
    int count = 0;
    Q2** sortedDrivers = malloc(sizeof(Q2*) * driverscollection->num_valid_rows);

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, driverscollection->DriversHash);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Driver* current_driver = (Driver*) value;
        char *drivers_account_status = get_drivers_account_status(driverscollection->DriversHash,current_driver->id);

        if (!(strcmp(drivers_account_status,"active")) && g_hash_table_contains(StatisticsHash,current_driver->id)){
            // Create a new driver struct with only the desired values
            Q2* filtered_driver = malloc(sizeof(Q2));
            filtered_driver->id = current_driver->id;
            filtered_driver->avaliacaoMedia = get_statisticsDrivers_avaliacaoMedia(StatisticsHash,current_driver->id);
            filtered_driver->finalDate_number = get_statisticsDrivers_finalDate_number(StatisticsHash,current_driver->id);

            // Add the filtered driver to the array
            sortedDrivers[count++] = filtered_driver;
        }
        free(drivers_account_status);
    }

    // Sort the array by the driver's name
    qsort(sortedDrivers, count, sizeof(Q2*), sort_Drivers_array);

    // Assign the sorted array to the driverscollection
    driverscollection->sorted_Drivers_array = sortedDrivers;
    driverscollection->lenght_sorted_Drivers_array=count;
}



Q7_collection* create_Q7_collection(GHashTable* RidesHash) {
    Q7_collection *collection = malloc(sizeof(Q7_collection));

    collection->citysHash_Q7 = g_hash_table_new(g_str_hash, g_str_equal);

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, RidesHash);

    while (g_hash_table_iter_next(&iter, &key, &value)) {

        Ride* ride = (Ride*) value;
        char *city=ride->city;
        char *driverID=ride->driver;
        double score_driver =ride->score_driver;

        City_Q7 *cityPointer;
        Driver_Q7 *driverPointer;

        if (!g_hash_table_contains(collection->citysHash_Q7, city)) {
            cityPointer = malloc(sizeof(City_Q7));
            cityPointer->driversHash_Q7 = g_hash_table_new(g_str_hash, g_str_equal);
            g_hash_table_insert(collection->citysHash_Q7, city, cityPointer);
        }
        else {
            cityPointer = g_hash_table_lookup(collection->citysHash_Q7, city);
        }

        if (!g_hash_table_contains(cityPointer->driversHash_Q7, driverID)) {
            driverPointer = malloc(sizeof(Driver_Q7));
            driverPointer->avaliacaoMedia = 1;
            driverPointer->nViagens = 0;
            driverPointer->id=driverID;
            g_hash_table_insert(cityPointer->driversHash_Q7, driverID, driverPointer);
        }
        else {
            driverPointer = g_hash_table_lookup(cityPointer->driversHash_Q7, driverID);
        }

        driverPointer->avaliacaoMedia= ((driverPointer->avaliacaoMedia)*(driverPointer->nViagens)+score_driver)/((driverPointer->nViagens)+1);
        driverPointer->nViagens+=1;
    }
    return collection;
}

char* get_drivers_id(GHashTable* DriversHash,char *id){
    Driver* driver = g_hash_table_lookup(DriversHash, id);
    char *driverID = strdup(driver->id); //name is driverID and not id because of the id received as argument
    return driverID;
} 

char* get_drivers_name(GHashTable* DriversHash,char *id){
    Driver* driver = g_hash_table_lookup(DriversHash, id);
    char *name = strdup(driver->name);
    return name;
} 

int get_drivers_birth_date_number(GHashTable* DriversHash,char *id){
    Driver* driver = g_hash_table_lookup(DriversHash, id);
    int birth_date_number = driver->birth_date_number;
    return birth_date_number;
} 

char* get_drivers_gender(GHashTable* DriversHash,char *id){
    Driver* driver = g_hash_table_lookup(DriversHash, id);
    char *gender = strdup(driver->gender);
    return gender;
} 

char* get_drivers_car_class(GHashTable* DriversHash,char *id){
    Driver* driver = g_hash_table_lookup(DriversHash, id);
    char *car_class = strdup(driver->car_class);
    return car_class;
} 

char* get_drivers_city(GHashTable* DriversHash,char *id){
    Driver* driver = g_hash_table_lookup(DriversHash, id);
    char *city = strdup(driver->city);
    return city;
} 

int get_drivers_account_creation(GHashTable* DriversHash,char *id){
    Driver* driver = g_hash_table_lookup(DriversHash, id);
    int account_creation = driver->account_creation;
    return account_creation;
} 

char* get_drivers_account_status(GHashTable* DriversHash,char *id){
    Driver* driver = g_hash_table_lookup(DriversHash, id);
    char *account_status = strdup(driver->account_status);
    return account_status;
} 

int drivers_contains(GHashTable* DriversHash,char *id){
    int valor=0;
    if (g_hash_table_contains(DriversHash, id)) valor=1;        
    return valor;
}