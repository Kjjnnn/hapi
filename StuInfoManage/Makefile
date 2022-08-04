CC=gcc
BIN=all
OBJ=main.o tools.o headmaster.o teacher.o student.o
FLAG=-Wall -Werror -DDEBUG
STD=-std=gnu99
LD=-lm

all : $(OBJ)
	$(CC) -o $(BIN) $(OBJ) $(LD)

main.o:main.c tools.h
	$(CC) $(STD) $(FLAG) -c main.c

tools.o:tools.c tools.h teacher.h student.h headmaster.h
	$(CC) $(STD) $(FLAG) -c tools.c

teacher.o:teacher.c teacher.h tools.h
	$(CC) $(STD) $(FLAG) -c teacher.c

student.o:student.c student.h tools.h
	$(CC) $(STD) $(FLAG) -c student.c

headmaster.o:headmaster.c headmaster.h tools.h
	$(CC) $(STD) $(FLAG) -c headmaster.c

clean:
	rm -rf $(BIN) $(OBJ)
