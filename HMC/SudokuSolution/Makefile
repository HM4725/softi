.SUFFIXES: .c .o

CC = gcc

SRC=./src/
INC=./include/
BIN=./bin/

CFLAGS+= -g -Wall -I $(INC)

SRCS:= \
	$(SRC)main.c \
	$(SRC)sudoku.c \
	$(SRC)heap.c

OBJS:= $(SRCS:.c=.o)
TARGET=$(BIN)sudokuSolve

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm $(TARGET) $(OBJS)
