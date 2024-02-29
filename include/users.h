#ifndef USERS_H
#define USERS_H

#include <glib.h>
#include "parse.h"
#include "q.h"

typedef struct {
    int birth_date_number;
    int account_creation;
    char *username;
    char *name;
    char *gender;
    char *account_status;
} User;

typedef struct {
    int lenght_sorted_Users_array;
    int num_valid_rows;
    Q3** sorted_Users_array;
    User *users;
    GHashTable *UsersHash;
} UsersCollection;

UsersCollection *build_Users(const char *filename);

void create_UsersHash(UsersCollection *collection);

void sortUsersArray(UsersCollection* userscollection,GHashTable* StatisticsHash);

char* get_users_username(GHashTable* UsersHash,char *id);
char* get_users_name(GHashTable* UsersHash,char *id);
char* get_users_gender(GHashTable* UsersHash,char *id);
int get_users_birth_date_number(GHashTable* UsersHash,char *id);
int get_users_account_creation(GHashTable* UsersHash,char *id);
char* get_users_account_status(GHashTable* UsersHash,char *id);
int users_contains(GHashTable* UsersHash,char *id);

#endif