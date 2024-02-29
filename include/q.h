#ifndef Q_H
#define Q_H

#include <glib.h>

typedef struct {
    int finalDate_number;
    double avaliacaoMedia;
    char *id;
} Q2;

typedef struct {
    int distanciaTotal;
    int finalDate_number;
    char *username;
} Q3;

typedef struct{
    int data;
    int distance;
    double preco;
    char *city;
} Q5_6;

typedef struct {
    int nViagens;
    double avaliacaoMedia;
    char *id;
} Driver_Q7;

typedef struct {
    GHashTable* driversHash_Q7; // hash of driver_Q7 pointers 
} City_Q7;

typedef struct {
    GHashTable* citysHash_Q7; // hash of city_Q7 pointers
} Q7_collection;

typedef struct{
    int idade_menor; //Porque a outra idade esta necessariamente acima
    int conta_driver; 
    int conta_user; 
    char* id_ride;
}Q8;

typedef struct{
    int date_ride;
    int distance;
    char* id_ride;
}Q9;

void q1(GHashTable* UsersHash, GHashTable* DriversHash,GHashTable* StatisticsHash, char *id, int n);
void q2(int top_number,GHashTable* DriversHash, Q2** sorted_Drivers_array,int n);
void q3(int top_number,GHashTable* UsersHash,Q3** sorted_Users_array, int n);
void q4(GHashTable* StatisticsHash, char* city, int n);
void q5(Q5_6** sorted_Q5_array,int numRides,char* data1, char* data2,int n);
void q6(GHashTable* StatisticsHash,Q5_6** sorted_Q5_6_array,int numRides,char* city, char* data1, char* data2,int n);
void q7(GHashTable* StatisticsHash,GHashTable* DriversHash,Q7_collection *q7_collection,int top_number,char *city,int n);
void q8(GHashTable* RidesHash,GHashTable* DriversHash,GHashTable* UsersHash,Q8** sorted_Q8_array,int length, int ida,int n);
void q9(GHashTable* RidesHash,Q9** sorted_Q9_array,int length,char* data1, char* data2,int n);
#endif