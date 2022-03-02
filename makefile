GRM=source.y
LEX=source.lex
BIN=lexer.exe

CC=gcc
CFLAGS=-Wall -g

OBJ=y.tab.o lex.yy.o

all: $(BIN)

%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

y.tab.c: $(GRM)
	yacc -d -v $<

lex.yy.c: $(LEX)
	lex $<

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

clean:
	rm $(OBJ) y.tab.c y.tab.h lex.yy.c y.output
