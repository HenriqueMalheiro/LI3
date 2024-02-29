#ifndef INTERATIVO_H
#define INTERATIVO_H

#include "statistics.h"
#include "users.h"
#include "drivers.h"
#include "rides.h"

void query_selector_interativo( UsersCollection* userscollection, DriversCollection* driverscollection, 
RidesCollection* ridescollection, StatisticsCollection* statisticscollection,Q7_collection* q7_collection);

void interativo();

#endif
