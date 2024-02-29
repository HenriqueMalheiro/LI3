#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <glib.h>
#include "statistics.h"
#include "users.h"
#include "drivers.h"
#include "rides.h"
#include "helpers.h"
#include <sys/time.h>


void q1(GHashTable* UsersHash, GHashTable* DriversHash,GHashTable* StatisticsHash, char* id, int n){

    if (n==-1){
        if (((users_contains(UsersHash,id)==1) || (drivers_contains(DriversHash,id)==1)) 
        && statistics_contains(StatisticsHash,id)){
            if (!(isdigit(id[0]))){
                char *users_account_status = get_users_account_status(UsersHash,id);
                if (!(strcmp(users_account_status,"active"))){
                    char *users_name = get_users_name(UsersHash,id);
                    char *users_gender = get_users_gender(UsersHash,id);
                    printf("%s;%s;%i;%.3f;%i;%.3f\n\n",users_name,users_gender,idade(get_users_birth_date_number(UsersHash,id)),
                    get_StatisticsUsers_avaliacaoMedia(StatisticsHash,id),get_StatisticsUsers_nViagens(StatisticsHash,id),
                    get_StatisticsUsers_totalGasto(StatisticsHash,id));
                    free(users_name);
                    free(users_gender);
                }
                free(users_account_status);
            }else{
                char *drivers_account_status = get_drivers_account_status(DriversHash,id);
                if (!(strcmp(drivers_account_status,"active"))){
                    char *drivers_name = get_drivers_name(DriversHash,id);
                    char *drivers_gender = get_drivers_gender(DriversHash,id);
                    printf("%s;%s;%i;%.3f;%i;%.3f\n\n",drivers_name,drivers_gender,idade(get_drivers_birth_date_number(DriversHash,id)),
                    get_statisticsDrivers_avaliacaoMedia(StatisticsHash,id),get_statisticsDrivers_nViagens(StatisticsHash,id),
                    get_statisticsDrivers_totalAuferido(StatisticsHash,id));
                    free(drivers_name);
                    free(drivers_gender);
                }
                free(drivers_account_status);
            }
        }

    }else{
        FILE *out=cria_documento(n);
        if (((users_contains(UsersHash,id)==1) || (drivers_contains(DriversHash,id)==1)) 
        && statistics_contains(StatisticsHash,id)){
            if (!(isdigit(id[0]))){
                char *users_account_status = get_users_account_status(UsersHash,id);
                if (!(strcmp(users_account_status,"active"))){
                    char *users_name = get_users_name(UsersHash,id);
                    char *users_gender = get_users_gender(UsersHash,id);
                    fprintf(out,"%s;%s;%i;%.3f;%i;%.3f\n",users_name,users_gender,idade(get_users_birth_date_number(UsersHash,id)),
                    get_StatisticsUsers_avaliacaoMedia(StatisticsHash,id),get_StatisticsUsers_nViagens(StatisticsHash,id),
                    get_StatisticsUsers_totalGasto(StatisticsHash,id));
                    free(users_name);
                    free(users_gender);
                }
                free(users_account_status);
            }else{
                char *drivers_account_status = get_drivers_account_status(DriversHash,id);
                if (!(strcmp(drivers_account_status,"active"))){
                    char *drivers_name = get_drivers_name(DriversHash,id);
                    char *drivers_gender = get_drivers_gender(DriversHash,id);
                    fprintf(out,"%s;%s;%i;%.3f;%i;%.3f\n",drivers_name,drivers_gender,idade(get_drivers_birth_date_number(DriversHash,id)),
                    get_statisticsDrivers_avaliacaoMedia(StatisticsHash,id),get_statisticsDrivers_nViagens(StatisticsHash,id),
                    get_statisticsDrivers_totalAuferido(StatisticsHash,id));
                    free(drivers_name);
                    free(drivers_gender);
                }
                free(drivers_account_status);
            }
        }
        fclose(out);
    }
}


void q2(int top_number,GHashTable* DriversHash, Q2** sorted_Drivers_array,int n){

    if (n==-1){
        int numeroLinha=0;
        int parar_numero = number_lines();
        for (int i=0;i<top_number;i++){
            char* nome = get_drivers_name(DriversHash,sorted_Drivers_array[i]->id);
            if (numeroLinha<parar_numero){
                printf("%s;%s;%.3f\n",sorted_Drivers_array[i]->id,nome,sorted_Drivers_array[i]->avaliacaoMedia);
                numeroLinha++;
            }else{
                numeroLinha=0;
                parar_numero = number_lines();
                i--;
            }
            free(nome);
        }  
        printf("\n");  
    }else {
        FILE *out=cria_documento(n);
        for (int i=0;i<top_number;i++){
            char* nome = get_drivers_name(DriversHash,sorted_Drivers_array[i]->id);
            fprintf(out,"%s;%s;%.3f\n",sorted_Drivers_array[i]->id,nome,sorted_Drivers_array[i]->avaliacaoMedia);
            free(nome);
        }   
        fclose(out);
    }

} 


void q3(int top_number,GHashTable* UsersHash,Q3** sorted_Users_array, int n){

    if (n==-1){
        int numeroLinha=0;
        int parar_numero = number_lines();
        for (int i=0;i<top_number;i++){
            char* nome = get_users_name(UsersHash,sorted_Users_array[i]->username);
            if (numeroLinha<parar_numero){
                printf("%s;%s;%d\n",sorted_Users_array[i]->username,nome,sorted_Users_array[i]->distanciaTotal);
                numeroLinha++;
            }else{
                numeroLinha=0;
                parar_numero = number_lines();
                i--;
            } 
            free(nome);
        }  
        printf("\n");
    }else{
        FILE *out=cria_documento(n);
        for (int i=0;i<top_number;i++){
            char* nome = get_users_name(UsersHash,sorted_Users_array[i]->username);
            fprintf(out,"%s;%s;%d\n",sorted_Users_array[i]->username,nome,sorted_Users_array[i]->distanciaTotal);
            free(nome);
        } 
        fclose(out);
    }
} 


void q4(GHashTable* StatisticsHash, char* city,int n){

    if (n==-1){
        if (statistics_contains(StatisticsHash,city)==1){
            printf("%.3f\n\n", get_StatisticsCity_precoMedio(StatisticsHash,city)); 
        } 
    }else{
        FILE *out=cria_documento(n);
        if (statistics_contains(StatisticsHash,city)==1){
            fprintf(out,"%.3f\n", get_StatisticsCity_precoMedio(StatisticsHash,city)); 
        }
        fclose(out);
    }
}

void q5(Q5_6** sorted_Q5_6_array,int numRides,char* data1, char* data2,int n){

    //Tranforma as datas em numero
    int d1,d2;
    d1=data_number(data1);
    d2=data_number(data2);

    int i=0;
    double soma,j=0,valor=0;
    while ((i<numRides)&&(sorted_Q5_6_array[i]->data<=d2)){
        if (sorted_Q5_6_array[i]->data>=d1){
            valor+=sorted_Q5_6_array[i]->preco;
            j++;
        }
        i++;
    }

    if (n==-1){
        if (valor !=0) {
            soma=valor/j;
            printf("%.3f\n\n",soma);
        }     
    }else{
        FILE *out=cria_documento(n);
        if (valor !=0) {
            soma=valor/j;
            fprintf(out,"%.3f\n",soma);
        }
        fclose(out);
    }
}  


void q6(GHashTable* StatisticsHash,Q5_6** sorted_Q5_6_array,int numRides,char* city, char* data1, char* data2,int n){

    //Tranforma as datas em numero
    int d1,d2;
    d1=data_number(data1);
    d2=data_number(data2);

    if (n==-1){
        int i=0;
        double soma,j=0,valor=0;
        if (statistics_contains(StatisticsHash,city)==1){
            while ((i<numRides)&&(sorted_Q5_6_array[i]->data<=d2)){ 
                if (sorted_Q5_6_array[i]->data>=d1){
                    if (!strcmp(sorted_Q5_6_array[i]->city,city)){
                        valor+=sorted_Q5_6_array[i]->distance;
                        j++;
                    }
                }
                i++;
            }
            if (valor !=0) {
                soma=valor/j;
                printf("%.3f\n\n",soma);
            }
        }
    }else{
        FILE *out=cria_documento(n);
        int i=0;
        double soma,j=0,valor=0;
        if (statistics_contains(StatisticsHash,city)==1){
            while ((i<numRides)&&(sorted_Q5_6_array[i]->data<=d2)){ 
                if (sorted_Q5_6_array[i]->data>=d1){
                    if (!strcmp(sorted_Q5_6_array[i]->city,city)){
                        valor+=sorted_Q5_6_array[i]->distance;
                        j++;
                    }
                }
                i++;
            }
            if (valor !=0) {
                soma=valor/j;
                fprintf(out,"%.3f\n",soma);
            }
        }
        fclose(out);
    }
}

void q7(GHashTable* StatisticsHash,GHashTable* DriversHash,Q7_collection *q7_collection,int top_number,char *city,int n){

    if (n==-1){
        int numeroLinha=0;
        int parar_numero = number_lines();
        if (statistics_contains(StatisticsHash,city)==1){

            City_Q7 *cityPointer = g_hash_table_lookup(q7_collection->citysHash_Q7, city);

            int num_drivers_city = g_hash_table_size(cityPointer->driversHash_Q7);
            int count = 0;

            Driver_Q7 **arrayDriversCity = malloc (sizeof(Driver_Q7*) * num_drivers_city);

            GHashTableIter iter;
            gpointer key, value;
            g_hash_table_iter_init(&iter, cityPointer->driversHash_Q7);

            while (g_hash_table_iter_next(&iter, &key, &value)) {
                Driver_Q7* driver_Q7 = (Driver_Q7*) value;
                char *account_status = get_drivers_account_status(DriversHash,driver_Q7->id);
                if (!strcmp(account_status,"active")) arrayDriversCity[count++] = driver_Q7;
                free(account_status);
            }

            qsort(arrayDriversCity,count,sizeof(Driver_Q7*),sort_arrayDriversCity_Q7);

            for (int i=0;i<top_number;i++){
                char* nome = get_drivers_name(DriversHash,arrayDriversCity[i]->id);
                if (numeroLinha<parar_numero){
                    printf("%s;%s;%.3f\n",arrayDriversCity[i]->id,nome,arrayDriversCity[i]->avaliacaoMedia);
                    numeroLinha++;
                }else{
                    numeroLinha=0;
                    parar_numero = number_lines();
                    i--;
                } 
                free(nome);
            }   
            
            free(arrayDriversCity);
        } 
        printf("\n");      
    }else{
        FILE *out=cria_documento(n);
        if (statistics_contains(StatisticsHash,city)==1){

            City_Q7 *cityPointer = g_hash_table_lookup(q7_collection->citysHash_Q7, city);

            int num_drivers_city = g_hash_table_size(cityPointer->driversHash_Q7);
            int count = 0;

            Driver_Q7 **arrayDriversCity = malloc (sizeof(Driver_Q7*) * num_drivers_city);

            GHashTableIter iter;
            gpointer key, value;
            g_hash_table_iter_init(&iter, cityPointer->driversHash_Q7);

            while (g_hash_table_iter_next(&iter, &key, &value)) {
                Driver_Q7* driver_Q7 = (Driver_Q7*) value;
                char *account_status = get_drivers_account_status(DriversHash,driver_Q7->id);
                if (!strcmp(account_status,"active")) arrayDriversCity[count++] = driver_Q7;
                free(account_status);
            }

            qsort(arrayDriversCity,count,sizeof(Driver_Q7*),sort_arrayDriversCity_Q7);

            for (int i=0;i<top_number;i++){
                char* nome = get_drivers_name(DriversHash,arrayDriversCity[i]->id);
                fprintf(out,"%s;%s;%.3f\n",arrayDriversCity[i]->id,nome,arrayDriversCity[i]->avaliacaoMedia);
                free(nome);
            }   
            free(arrayDriversCity);
        }
        fclose(out);
    }
}

void q8(GHashTable* RidesHash,GHashTable* DriversHash,GHashTable* UsersHash,Q8** sorted_Q8_array,int length, int ida,int n){

    if (n==-1){
        int numeroLinha=0;
        int parar_numero = number_lines();
        for(int i=0;i<length;i++){
            if((sorted_Q8_array[i]->idade_menor)>=ida){ 
                char *id_driver=get_rides_driver(RidesHash,sorted_Q8_array[i]->id_ride);
                char *id_user=get_rides_user(RidesHash,sorted_Q8_array[i]->id_ride);
                char *name_driver=get_drivers_name(DriversHash,id_driver);
                char *name_user=get_users_name(UsersHash,id_user);
                if (numeroLinha<parar_numero){
                    printf("%s;%s;%s;%s\n",id_driver,name_driver,id_user,name_user);
                    numeroLinha++;
                }else{
                    numeroLinha=0;
                    parar_numero = number_lines();
                    i--;
                } 
                free(id_driver);
                free(id_user);
                free(name_driver);
                free(name_user);
            }
        } 
        printf("\n");      
    }else{
        FILE *out=cria_documento(n);
        for(int i=0;i<length;i++){
            if((sorted_Q8_array[i]->idade_menor)>=ida){ 
                char *id_driver=get_rides_driver(RidesHash,sorted_Q8_array[i]->id_ride);
                char *id_user=get_rides_user(RidesHash,sorted_Q8_array[i]->id_ride);
                char *name_driver=get_drivers_name(DriversHash,id_driver);
                char *name_user=get_users_name(UsersHash,id_user);
                fprintf(out,"%s;%s;%s;%s\n",id_driver,name_driver,id_user,name_user);

                free(id_driver);
                free(id_user);
                free(name_driver);
                free(name_user);
            }
        }
        fclose(out); 
    }
}

void q9(GHashTable* RidesHash,Q9** sorted_Q9_array,int length,char* data1, char* data2,int n){

    //Tranforma as datas em numero
    int d1,d2;
    d1=data_number(data1);
    d2=data_number(data2);

    if (n==-1){
        int numeroLinha=0;
        int parar_numero = number_lines();
        for(int i=0;i<length;i++){
            if(sorted_Q9_array[i]->date_ride>=d1 && sorted_Q9_array[i]->date_ride<=d2){
                char* id_ride= sorted_Q9_array[i]->id_ride;
                char* date_char=get_rides_date(RidesHash,id_ride); 
                char* city= get_rides_city(RidesHash,id_ride);
                double tip = get_rides_tip(RidesHash,id_ride);
                if (numeroLinha<parar_numero){
                    printf("%s;%s;%d;%s;%.3f\n",sorted_Q9_array[i]->id_ride,date_char,sorted_Q9_array[i]->distance,city,tip);
                    numeroLinha++;
                }else{
                    numeroLinha=0;
                    parar_numero = number_lines();
                    i--;
                } 
                free(date_char);
                free(city);
            }
        } 
        printf("\n");     
    }else{
        FILE *out=cria_documento(n);
        for(int i=0;i<length;i++){
            if(sorted_Q9_array[i]->date_ride>=d1 && sorted_Q9_array[i]->date_ride<=d2){
                char* id_ride= sorted_Q9_array[i]->id_ride;
                char* date_char=get_rides_date(RidesHash,id_ride); 
                char* city= get_rides_city(RidesHash,id_ride);
                double tip = get_rides_tip(RidesHash,id_ride);
                fprintf(out,"%s;%s;%d;%s;%.3f\n",sorted_Q9_array[i]->id_ride,date_char,sorted_Q9_array[i]->distance,city,tip);
                free(date_char);
                free(city);
            }
        }
        fclose(out);
    }
}
