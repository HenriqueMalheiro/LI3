#ifndef FREE_H
#define FREE_H

#include "parse.h"
#include "drivers.h"
#include "users.h"
#include "rides.h"
#include "statistics.h"

//void free_table(Table* table);

void free_array_tokens(char ** array_tokens,int lenght_array_tokens);
void free_array_drivers(Driver* drivers, int num_valid_rows);
void free_array_users(User* users, int num_valid_rows);
void free_array_rides(Ride* rides, int num_valid_rows);
void free_DriversCollection(DriversCollection* collection);
void free_UsersCollection(UsersCollection* collection);
void free_RidesCollection(RidesCollection* collection);
void free_StatisticsCollection(StatisticsCollection* collection);
void free_Q7_collection (Q7_collection *q7_collection);


#endif