EX1 	 	=ex1
#EX1_ARGS 	=-i foo -o copy_foo -i ex1.o -v
EX1_ARGS 	=
EX2 	 	=ex2
EX2_ARGS 	=
EX3 	 	=ex3
EX3_ARGS 	=
CC		 	=gcc
CFLAGS		=-Wall -Werror --pedantic -std=c11
LDFLAGS		=
SOURCES_EX1		=ex1.c my_string.c
SOURCES_EX2		=ex2.c
SOURCES_EX3		=ex3.c
HEADERS_EX1		=my_string.h
HEADERS_EX2		=
HEADERS_EX3		=
OBJECTS_EX1 		=$(SOURCES_EX1:.c=.o)
OBJECTS_EX2		=$(SOURCES_EX2:.c=.o)
OBJECTS_EX3		=$(SOURCES_EX3:.c=.o)
SOURCES 		=$(wildcard *.c)
HEADERS			=$(wildcard *.h)
OBJECTS 		=$(SOURCES:.c=.o) $(HEADERS:.h=.o)
EXES			=$(EX1) $(EX2) $(EX3)

all: $(EX1) $(EX2) $(EX3)
	./$(EX1) $(EX1_ARGS)
	./$(EX2) $(EX2_ARGS)
	./$(EX3) $(EX3_ARGS)

1: $(EX1)
	./$(EX1) $(EX1_ARGS)

2: $(EX2)
	./$(EX2) $(EX2_ARGS)

3: $(EX3)
	./$(EX3) $(EX3_ARGS)

valgrind_all: $(EX1)
	valgrind --leak-check=full -v ./$(EX1) $(EX1_ARGS)
	valgrind --leak-check=full -v ./$(EX2) $(EX2_ARGS)
	valgrind --leak-check=full -v ./$(EX3) $(EX3_ARGS)

valgrind_1: $(EX1)
	valgrind --leak-check=full -v ./$(EX1) $(EX1_ARGS)

valgrind_2: $(EX2)
	valgrind --leak-check=full -v ./$(EX2) $(EX2_ARGS)

valgrind_3: $(EX3)
	valgrind --leak-check=full -v ./$(EX3) $(EX3_ARGS)



$(EX1): $(OBJECTS_EX1)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(EX1)

$(EX2): $(OBJECTS_EX2)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(EX2)

$(EX3): $(OBJECTS_EX3)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(EX3)

ex1.o: $(SOURCES_EX1) $(HEADERS_EX1)
	$(CC) $(CFLAGS) -c -o ex1.o ex1.c


.PHONY: clean
clean:
	-rm $(EXES) $(OBJECTS)

#prepare: $(SOURCES) $(HEADERS)
#	python3 prepare_file.py $(SOURCES) $(HEADERS) makefile test.txt ex3test.txt
