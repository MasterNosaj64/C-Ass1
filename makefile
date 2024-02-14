CC = gcc
CC_FLAGS = -g -pedantic -Wall -W -std=c89

FILES = main.c menu.c
OUT_EXE = assign1

build: $(FILES)
	$(CC) $(CC_FLAGS) -o $(OUT_EXE) $(FILES) 

clean:
	rm -f *.o core *.exe *~ *.out *.stackdump

rebuild: clean build
