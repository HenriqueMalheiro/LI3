#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h>
#include <string.h>

int date_valid(char *data){
    if (strlen(data)!=10){
        return 0;        
    }
    int i=0;
    while(i<10){
        if (i!=2 && i!=5){
            if(!isdigit(data[i])){
                return 0;
            }
        }else{
            if(data[i]!='/'){
                return 0;
            }
        } 
        i++;
    }

    int dia, ano, mes; 
    sscanf(data,"%d/%d/%d",&dia,&mes,&ano);
    if(dia>0 && dia<32 && mes>0 && mes<13){
        return 1;
    }else{
        return 0;
    } 
}


void toLower_string(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        str[i] = tolower(str[i]);
    }
}

int is_decimal_string(char *str){
    int tamanho = strlen(str);
    for (int i = 0; i < tamanho; i++) {
        if (!isdigit(str[i])){
            if (str[i]!='.') {
                return 0;
            }else{
                if (tamanho-(i+1)>1) return 0;
            }
        }
    }
    return 1;
}

int is_int_string(char *str){
    for (int i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}