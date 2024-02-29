#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <glib.h>
#include "parse.h"
#include "users.h"
#include "helpers.h"
#include "statistics.h"
#include "valid.h"
#include "free.h"


UsersCollection *build_Users(const char *filename) {
    // Allocate memory for the UsersCollection struct
    UsersCollection *collection = malloc(sizeof(UsersCollection));
    // Allocate an array of Users
    User *users = malloc(sizeof(User));
    int users_capacity=1;
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

        char* account_status = array_tokens[6];
        account_status[strlen(account_status)-1] = '\0';

        if (strlen(array_tokens[0])>0 && strlen(array_tokens[1])>0 && strlen(array_tokens[2])>0 
        && strlen(array_tokens[5])>0 && date_valid(array_tokens[3])&& date_valid(array_tokens[4])){

            if (num_valid_rows == users_capacity) {
                users_capacity *= 2;
                users = realloc(users, users_capacity * sizeof(User));
            }    

            // Store the values in the User struct
            users[num_valid_rows] = (User){
                .username = strdup(array_tokens[0]),
                .name = strdup(array_tokens[1]),
                .gender = strdup(array_tokens[2]),
                .birth_date_number=data_number(array_tokens[3]),
                .account_creation = data_number(array_tokens[4]),
                .account_status = strdup(account_status)
            };
            toLower_string(users[num_valid_rows].account_status);
            num_valid_rows++;
        }
        free_array_tokens(array_tokens,7);
    }
    free(line);
    // Close the file   
    fclose(file);  

    collection->num_valid_rows=num_valid_rows;
    collection->users=users;
    return collection;
}

void create_UsersHash(UsersCollection *collection) {
    // Create the hashtable
    collection->UsersHash = g_hash_table_new(g_str_hash, g_str_equal);

    // Add the User structs to the hashtable
    for (int i = 0; i < collection->num_valid_rows; i++) {
        User *user = &(collection->users[i]);
        g_hash_table_insert(collection->UsersHash, user->username, user);
    }
}

void sortUsersArray(UsersCollection* userscollection,GHashTable* StatisticsHash) {
    int count = 0;
    Q3** sortedUsers = malloc(sizeof(Q3*) * userscollection->num_valid_rows);

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, userscollection->UsersHash);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        User* current_driver = (User*) value;
        char *users_account_status = get_users_account_status(userscollection->UsersHash,current_driver->username);
        
        if (!(strcmp(users_account_status,"active")) && g_hash_table_contains(StatisticsHash,current_driver->username)){
            // Create a new driver struct with only the desired values
            Q3* filtered_driver = malloc(sizeof(Q3));
            filtered_driver->username = current_driver->username;
            filtered_driver->distanciaTotal = get_StatisticsUsers_distanciaTotal(StatisticsHash,current_driver->username);
            filtered_driver->finalDate_number = get_StatisticsUsers_finalDate_number(StatisticsHash,current_driver->username);

            // Add the filtered driver to the array
            sortedUsers[count++] = filtered_driver;
        }
        free(users_account_status);
    }

    // Sort the array by the driver's name
    qsort(sortedUsers, count, sizeof(Q3*), sort_Users_array);

    // Assign the sorted array to the userscollection
    userscollection->sorted_Users_array = sortedUsers;
    userscollection->lenght_sorted_Users_array=count;
}

char* get_users_username(GHashTable* UsersHash,char *id){
    User* user = g_hash_table_lookup(UsersHash, id);
    char *username = strdup(user->username);
    return username;
} 

char* get_users_name(GHashTable* UsersHash,char *id){
    User* user = g_hash_table_lookup(UsersHash, id);
    char *name = strdup(user->name);
    return name;
} 

char* get_users_gender(GHashTable* UsersHash,char *id){
    User* user = g_hash_table_lookup(UsersHash, id);
    char *gender = strdup(user->gender);
    return gender;
} 

int get_users_birth_date_number(GHashTable* UsersHash,char *id){
    User* user = g_hash_table_lookup(UsersHash, id);
    int birth_date_number = user->birth_date_number;
    return birth_date_number;
} 

int get_users_account_creation(GHashTable* UsersHash,char *id){
    User* user = g_hash_table_lookup(UsersHash, id);
    int account_creation = user->account_creation;
    return account_creation;
} 

char* get_users_account_status(GHashTable* UsersHash,char *id){
    User* user = g_hash_table_lookup(UsersHash, id);
    char *account_status = strdup(user->account_status);
    return account_status;
} 

int users_contains(GHashTable* UsersHash,char *id){
    int valor=0;
    if (g_hash_table_contains(UsersHash, id)) valor=1;        
    return valor;
}