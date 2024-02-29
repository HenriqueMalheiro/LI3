#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <glib.h>
#include "q.h"
#include "parse.h"
#include "users.h"
#include "drivers.h"
#include "rides.h"
#include "statistics.h"
#include "free.h"

void Query_Selector(const char *filename, UsersCollection* userscollection, DriversCollection* driverscollection, 
RidesCollection* ridescollection, StatisticsCollection* statisticscollection,Q7_collection* q7_collection) {

    // Open the file
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: could not open file %s\n", filename);
        return;
    }

    // Read each line of the file
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int i=0;
    while ((read = getline(&line, &len, file)) != -1) {
        int lenght_array_tokens=0;
        char **array_tokens=parse(line," ");
        char *arg;

        int num = atoi(array_tokens[0]);  // Convert the first value to an integer
        switch (num) {
            case 1:
                lenght_array_tokens = 2;
                arg= array_tokens[1];
                arg[strlen(arg)-1] = '\0';
                q1(userscollection->UsersHash, driverscollection->DriversHash,statisticscollection->StatisticsHash, arg, i + 1);
                break;
            case 2:
                lenght_array_tokens = 2;
                q2(atoi(array_tokens[1]), driverscollection->DriversHash, driverscollection->sorted_Drivers_array, i + 1);
                break;
            case 3:
                lenght_array_tokens = 2;
                q3(atoi(array_tokens[1]), userscollection->UsersHash, userscollection->sorted_Users_array, i + 1);
                break;
            case 4:
                lenght_array_tokens = 2;
                arg= array_tokens[1];
                arg[strlen(arg)-1] = '\0';
                q4(statisticscollection->StatisticsHash, arg, i + 1);
                break;
            case 5:
                lenght_array_tokens = 3;
                arg= array_tokens[2];
                arg[strlen(arg)-1] = '\0';
                q5(statisticscollection->sorted_Q5_6_array,statisticscollection->length_Q5_6, 
                array_tokens[1], arg, i + 1); 
                break;
            case 6:
                lenght_array_tokens = 4;
                arg= array_tokens[3];
                arg[strlen(arg)-1] = '\0';
                q6(statisticscollection->StatisticsHash,statisticscollection->sorted_Q5_6_array,
                statisticscollection->length_Q5_6, array_tokens[1], array_tokens[2], arg, i + 1);
                break;
            case 7:
                lenght_array_tokens = 3;
                arg= array_tokens[2];
                arg[strlen(arg)-1] = '\0';
                q7(statisticscollection->StatisticsHash,driverscollection->DriversHash,q7_collection,atoi(array_tokens[1]),arg,i+1);
                break;
            case 8:
                lenght_array_tokens = 3;
                arg= array_tokens[2];
                arg[strlen(arg)-1] = '\0';
                if (!strcmp(array_tokens[1],"F")){
                    q8(ridescollection->RidesHash,driverscollection->DriversHash,userscollection->UsersHash,statisticscollection->sorted_Q8_feminino_array,statisticscollection->length_feminino, atoi(arg), i + 1);
                }else{
                    q8(ridescollection->RidesHash,driverscollection->DriversHash,userscollection->UsersHash,statisticscollection->sorted_Q8_masculino_array,statisticscollection->length_masculino, atoi(arg), i + 1);
                }
                break;
            case 9:
                lenght_array_tokens = 3;
                arg= array_tokens[2];
                arg[strlen(arg)-1] = '\0';
                q9(ridescollection->RidesHash,statisticscollection->sorted_Q9_array,statisticscollection->length_Q9, array_tokens[1], arg, i + 1);
                break;
            default:
                printf("Error! operator is not correct");
        }
        i++;
        free_array_tokens(array_tokens,lenght_array_tokens);
    }
    free(line);
    // Close the file
    fclose(file);  
}
