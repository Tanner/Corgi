CC = gcc
CFLAGS = -pedantic -Wall -Werror -std=c99
RELEASE_FLAGS = -02
DEBUG_FLAGS = -g -DDEBUG

PROGRAM_NAME = corgi

O_FILES = sim.o memory.o alu.o
H_FILES = sim.h memory.h types.h alu.h debug.h

run : build-release
	./$(PROGRAM_NAME)

run-debug: build-debug
	./$(PROGRAM_NAME)

run-gdb : build-debug
	gdb ./$(PROGRAM_NAME)

run-valgrind : build-debug
	valgrind --leak-check=yes --show-reachable=no --tool=memcheck ./$(PROGRAM_NAME)

build-release : CFLAGS += $(RELEASE_FLAGS)
build-release : $(O_FILES) $(H_FILES)
	$(CC) $(CFLAGS) $(O_FILES) -o $(PROGRAM_NAME)

build-debug : CFLAGS += $(DEBUG_FLAGS)
build-debug : clean $(O_FILES) $(H_FILES)
	$(CC) $(CFLAGS) $(O_FILES) -o $(PROGRAM_NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f *.o $(PROGRAM_NAME)