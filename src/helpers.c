#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"
#include "q.h"

#define data_base 2022*10000 + 10*100 + 9

int idade (int birth_date_number){
    int anos = (data_base-birth_date_number)/10000; 
    return anos;
}

int data_number (char *data){
    int dia, ano, mes; 
    sscanf(data,"%d/%d/%d",&dia,&mes,&ano);
    int data_number = dia + mes*100 + ano*10000;
    return data_number;
}

FILE* cria_documento(int n){
    FILE *out;
    char nome[60];
    sprintf(nome,"Resultados/command%d_output.txt",n);
    out = fopen(nome, "w");
    return out;
}


int sort_Drivers_array(const void *x, const void *y){
    Q2 *q2_x = *(Q2 **)x;
    Q2 *q2_y = *(Q2 **)y;
    int driver1=atoi(q2_x->id);
    int driver2=atoi(q2_y->id);

    int trunc_1 = (int)(q2_x->avaliacaoMedia * 1000);
    int trunc_2 = (int)(q2_y->avaliacaoMedia * 1000);


    if (trunc_1 > trunc_2) {
        return -1;
    } else if (trunc_1 < trunc_2) {
        return 1;
    } else if (q2_x->finalDate_number > q2_y->finalDate_number) {
        return -1;
    } else if (q2_x->finalDate_number < q2_y->finalDate_number) {
        return 1;
    } else if (driver1 < driver2) {
        return -1;
    } else if (driver1 > driver2) {
        return 1;
    } else {
        return 0;
    }
}

int sort_Users_array(const void *x, const void *y){
    Q3 *q3_x = *(Q3 **)x;
    Q3 *q3_y = *(Q3 **)y;

    if (q3_x->distanciaTotal > q3_y->distanciaTotal) {
        return -1;
    } else if (q3_x->distanciaTotal < q3_y->distanciaTotal) {
        return 1;
    } else if (q3_x->finalDate_number > q3_y->finalDate_number) {
        return -1;
    } else if (q3_x->finalDate_number < q3_y->finalDate_number) {
        return 1;
    } else if (strcmp(q3_x->username,q3_y->username) < 0) {
        return -1;
    } else if (strcmp(q3_x->username,q3_y->username) > 0) {
        return 1;
    } else {
        return 0;
    }
}

int sort_Statistics_Q5_6(const void *x, const void *y){
    Q5_6 *q5_6_x = *(Q5_6 **)x;
    Q5_6 *q5_6_y = *(Q5_6 **)y;
    if (q5_6_x->data > q5_6_y->data) {
        return 1;
    } else if (q5_6_x->data == q5_6_y->data) {
        return 0;
    } else {
        return -1;
    }
}

int sort_arrayDriversCity_Q7(const void *x, const void *y){
    Driver_Q7 *q7_x = *(Driver_Q7 **)x;
    Driver_Q7 *q7_y = *(Driver_Q7 **)y;
    int driver1=atoi(q7_x->id);
    int driver2=atoi(q7_y->id);

    int trunc_1 = (int)(q7_x->avaliacaoMedia * 1000);
    int trunc_2 = (int)(q7_y->avaliacaoMedia * 1000);

    if (trunc_1 > trunc_2) {
        return -1;
    } else if (trunc_1 < trunc_2) {
        return 1;
    } else if (driver1 > driver2) {
        return -1;
    } else if (driver1 < driver2) {
        return 1;
    } else {
        return 0;
    }
}

int sort_Statistics_Q8(const void *x, const void *y){
    Q8 *q8_x = *(Q8 **)x;
    Q8 *q8_y = *(Q8 **)y;
    int id_ride1 = atoi(q8_x->id_ride);
    int id_ride2 = atoi(q8_y->id_ride);

    if (q8_x->conta_driver > q8_y->conta_driver) {
        return 1;
    } else if (q8_x->conta_driver < q8_y->conta_driver) {
        return -1;
    } else if (q8_x->conta_user > q8_y->conta_user) {
        return 1;
    } else if (q8_x->conta_user < q8_y->conta_user) {
        return -1;
    } else if (id_ride1 > id_ride2) {
        return 1;
    } else if (id_ride1 < id_ride2) {
        return -1;
    } else {
        return 0;
    }
}

int sort_Statistics_Q9(const void *x, const void *y){
    Q9 *q9_x = *(Q9 **)x;
    Q9 *q9_y = *(Q9 **)y;

    int idx, idy; //Porque os id das rides sao strings
    if (q9_y->distance<q9_x->distance){
        return -1;
    }else{
        if (q9_y->distance==q9_x->distance){
            if (q9_y->date_ride<q9_x->date_ride){
                return -1;
            }else{
                if (q9_y->date_ride==q9_x->date_ride){
                    idy=atoi(q9_y->id_ride);
                    idx=atoi(q9_x->id_ride);
                    if (idy<idx){
                        return -1;
                    }else{
                        if (idy==idx){
                            return 0;
                        }else{
                            return 1;
                        }
                    }
                }else{
                    return 1;
                }
            }
        }else{
            return 1;
        }
    } 
}

int number_lines(){
    char parar[8];
    int parar_numero;
    printf("\n");
    printf("Introduza o numero de linhas que pretende ver: ");
    scanf("%s",parar);
    printf("\n");
    parar_numero=atoi(parar);
    return parar_numero;
}