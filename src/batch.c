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

void batch(int argc,char **argv){

    //Create 3 directories to the users , drivers and rides csvs, using the path to their folder
    char *dirUsers;
    char *dirDrivers;
    char *dirRides;

    dirUsers = malloc(strlen(argv[1]) + strlen("/users.csv") + 1);
    dirDrivers = malloc(strlen(argv[1]) + strlen("/drivers.csv") + 1);
    dirRides = malloc(strlen(argv[1]) + strlen("/rides.csv") + 1);

    sprintf(dirUsers, "%s/users.csv", argv[1]);
    sprintf(dirDrivers, "%s/drivers.csv", argv[1]);
    sprintf(dirRides, "%s/rides.csv", argv[1]);

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

    /*Function that with the table returned by the parse of the file with the inputs,
    selects the query and passed the arguments needed as well */
    Query_Selector(argv[2],userscollection,driverscollection,ridescollection,statisticscollection,q7_collection);

    //Free the collections
    free_Q7_collection(q7_collection);
    free_StatisticsCollection(statisticscollection);
    free_DriversCollection(driverscollection);
    free_UsersCollection(userscollection);
    free_RidesCollection(ridescollection);
}