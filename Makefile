CC = gcc
CFLAGS = -pedantic -Wall -Werror
RELEASE_FLAGS = -02
DEBUG_FLAGS = -g -DDEBUG

PROGRAM_NAME = corgi

O_FILES = sim.o memory.o
H_FILES = memory.h types.h

run : build-release
	./$(PROGRAM_NAME)

run-gdb : build-debug
	gdb ./$(PROGRAM_NAME)

run-valgrind : build-debug
	valgrind --leak-check=yes --show-reachable=yes --tool=memcheck ./$(PROGRAM_NAME)

build-release : CFLAGS += $(RELEASE_FLAGS)
build-release : $(O_FILES) $(H_FILES)
	$(CC) $(CFLAGS) $(O_FILES) -o $(PROGRAM_NAME)

build-debug : CFLAGS += $(DEBUG_FLAGS)
build-debug : $(O_FILES) $(H_FILES)
	$(CC) $(CFLAGS) $(O_FILES) -o $(PROGRAM_NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm *.o $(PROGRAM_NAME)