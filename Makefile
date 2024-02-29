DATAFILE= data
SRCFILE= src
INCLUDEFILE= include
CFLAGS= -c `pkg-config --cflags glib-2.0` -Wall -I$(INCLUDEFILE) -g
LFLAGS= `pkg-config --libs glib-2.0` 


all: programa-principal

programa-principal: main.o parse.o users.o drivers.o rides.o statistics.o query_selector.o queries.o helpers.o valid.o free.o batch.o interativo.o
	gcc main.o parse.o users.o drivers.o rides.o statistics.o query_selector.o queries.o helpers.o valid.o free.o batch.o interativo.o $(LFLAGS) -o programa-principal

main.o: $(SRCFILE)/main.c
	@mkdir -p Resultados
	gcc $(SRCFILE)/main.c $(CFLAGS)

parse.o: $(SRCFILE)/parse.c 
	gcc $(SRCFILE)/parse.c $(CFLAGS)

users.o: $(SRCFILE)/users.c 
	gcc $(SRCFILE)/users.c $(CFLAGS)

drivers.o: $(SRCFILE)/drivers.c 
	gcc $(SRCFILE)/drivers.c $(CFLAGS)

rides.o: $(SRCFILE)/rides.c 
	gcc $(SRCFILE)/rides.c $(CFLAGS)

statistics.o: $(SRCFILE)/statistics.c 
	gcc $(SRCFILE)/statistics.c $(CFLAGS)

query_selector.o: $(SRCFILE)/query_selector.c 
	gcc $(SRCFILE)/query_selector.c $(CFLAGS)

queries.o: $(SRCFILE)/queries.c 
	gcc $(SRCFILE)/queries.c $(CFLAGS)

helpers.o: $(SRCFILE)/helpers.c 
	gcc $(SRCFILE)/helpers.c $(CFLAGS)

valid.o: $(SRCFILE)/valid.c 
	gcc $(SRCFILE)/valid.c $(CFLAGS)

free.o: $(SRCFILE)/free.c 
	gcc $(SRCFILE)/free.c $(CFLAGS)

batch.o: $(SRCFILE)/batch.c 
	gcc $(SRCFILE)/batch.c $(CFLAGS)

interativo.o: $(SRCFILE)/interativo.c 
	gcc $(SRCFILE)/interativo.c $(CFLAGS)

clean: 
	rm -rf Resultados
	rm *.o *programa-principal
