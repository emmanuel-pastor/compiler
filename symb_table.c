#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symb_table.h"
#define MAX_SYMB 240
#define NB_TEMP_ADDR 16

//TODO: Move temp addr out of symbol table
typedef struct Symbol {
    char* name;
    int addr;
    int scope;
} Symbol;

Symbol symb_table[MAX_SYMB];
int top_index = 0;
int scope = -1;
int temp_addr_table[NB_TEMP_ADDR];

int push_symb(char* name) {
    if (top_index >= MAX_SYMB) {
        fprintf(stderr, "The data memory is full (more than %d variables)\n", MAX_SYMB);
        exit(EXIT_FAILURE);
    }
	Symbol symb = {name, top_index, scope};
	symb_table[top_index] = symb;
	top_index++;
	return top_index-1;
}

void pop_symb() {
	Symbol nullSymb = {NULL, 0, 0};
	symb_table[top_index-1] = nullSymb;
	top_index--;
}

int exists_symb(char* name, int inAnyScope) {
	int found = 0;
	int i = top_index-1;

	while(!found && symb_table[i].name != NULL && i >= 0) {
		if((!strcmp(symb_table[i].name,name) && inAnyScope) || (!strcmp(symb_table[i].name,name) && !inAnyScope && symb_table[i].scope == scope)) {
			found = 1;
		}
		i--;
	}
	return found;
}

void incr_scope() {
	scope++;
}

void decr_scope() {
	int i = top_index-1;
	while(symb_table[i].scope == scope && i >= 0) {
		pop_symb();
		i--;
	}
	scope--;
}

int get_symb_addr(char* name) {
	int i = top_index-1;

	while(i >= 0) {
		if(!strcmp(symb_table[i].name,name)) {
			return symb_table[i].addr;
		}
		i--;
	}

	fprintf(stderr, "Could not resolve symbol \"%s\"\n", name);
	exit(EXIT_FAILURE);
}

int use_temp_addr() {
	for(int i=0; i < NB_TEMP_ADDR; i++) {
		if(temp_addr_table[i] == 0) {
			temp_addr_table[i] = 1;
			return i + MAX_SYMB;
		}
	}
	fprintf(stderr, "All temporary addresses are being used. Your code may contain an arithmetic expression which is too long.\n");
	exit(EXIT_FAILURE);
}
void free_temp_addr(int addr) {
	if(addr >= MAX_SYMB) {
		temp_addr_table[addr-MAX_SYMB] = 0;
	}
}

void free_all_temp_addr() {
	for(int i=0; i < NB_TEMP_ADDR; i++) {
		temp_addr_table[i] = 0;
	}
}

void print_symb(Symbol symb) {
    printf("{name=%s, addr=%d, scope=%d}\n", symb.name, symb.addr, symb.scope);
}

void print_symb_table() {
  Symbol symb = symb_table[0];
  int i = 1;
  while(symb.name != NULL && i < MAX_SYMB) {
  	print_symb(symb);
  	symb = symb_table[i];
  	i++;
  }
}
