#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <glib.h>
#include <sys/time.h>
#include <unistd.h>
#include "batch.h"
#include "interativo.h"



int main (int argc,char **argv){

   if (argc == 1){
      interativo();
   }else{
      batch(argc,argv);
   }

   return 0;
}
  