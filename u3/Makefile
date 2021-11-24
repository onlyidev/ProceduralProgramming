CC=gcc
FILES=main.c
STD=c89
EXEC=main

TEST_IN=reads
TEST_OUT=out

main: $(FILES)
	gcc -std=$(STD) -g -ansi -Wall -pedantic $(FILES) -o $(EXEC)	

build:
	gcc -std=$(STD) -g -O2 -ansi -Wall -pedantic $(FILES) -o $(EXEC)	

test: main
	-./main $(TEST_IN) $(TEST_OUT) && bash ./invariants.sh $(TEST_IN) $(TEST_OUT) && diff $(TEST_IN) $(TEST_OUT)
