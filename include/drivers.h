#ifndef DRIVERS_H
#define DRIVERS_H

#include <glib.h>
#include "parse.h"
#include "q.h"

typedef struct {
    int birth_date_number;
    int account_creation;
    char *id;
    char *name;
    char *gender;
    char *car_class;
    char *city;
    char *account_status;
} Driver;


typedef struct {
    int lenght_sorted_Drivers_array;
    int num_valid_rows;
    Q2** sorted_Drivers_array;
    Driver *drivers;
    GHashTable *DriversHash;
} DriversCollection;

DriversCollection *build_Drivers(const char *filename);
 
void create_DriversHash(DriversCollection *collection);

void sortDriversArray(DriversCollection* driverscollection,GHashTable* StatisticsHash);

Q7_collection* create_Q7_collection(GHashTable* RidesHash);

//gets

char* get_drivers_id(GHashTable* DriversHash,char *id);
char* get_drivers_name(GHashTable* DriversHash,char *id);
int get_drivers_birth_date_number(GHashTable* DriversHash,char *id);
char* get_drivers_gender(GHashTable* DriversHash,char *id);
char* get_drivers_car_class(GHashTable* DriversHash,char *id);
char* get_drivers_city(GHashTable* DriversHash,char *id);
int get_drivers_account_creation(GHashTable* DriversHash,char *id);
char* get_drivers_account_status(GHashTable* DriversHash,char *id);
int drivers_contains(GHashTable* DriversHash,char *id);

#endif