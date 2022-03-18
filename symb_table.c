#include <stdio.h>
#include <stdlib.h>
#include "symb_table.h"
#define MAX_SYMB 200
#define TEMP_ADDR1 201
#define TEMP_ADDR2 202

typedef struct Symbol {
    char* name;
    int addr;
    int scope;
} Symbol;

Symbol symb_table[MAX_SYMB];
int top_index = 0;
int scope = -1;
int tempAddr1Busy = 0;
int tempAddr2Busy = 0;

int push_symb(char* name) {
	Symbol symb = {name, top_index, scope};
	/*printf("pushed: ");
	print_symb(symb);*/
	symb_table[top_index] = symb;
	top_index++;
	return top_index-1;
}

void pop_symb() {
	/*printf("poped: ");
	print_symb(symb_table[top_index-1]);*/
	Symbol nullSymb = {NULL, 0, 0};
	symb_table[top_index-1] = nullSymb;
	top_index--;
}

int exists_symb(char* name, int inAnyScope) {
	int found = 0;
	int i = top_index-1;

	while(!found && symb_table[i].name != NULL && i >= 0) {
		if(!strcmp(symb_table[i].name,name) && inAnyScope || !strcmp(symb_table[i].name,name) && !inAnyScope && symb_table[i].scope == scope) {
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
	exit(1);
}

int use_temp_addr() {
	if(!tempAddr1Busy) {
		tempAddr1Busy = 1;
		return TEMP_ADDR1;
	}
	tempAddr2Busy = 1;
	return TEMP_ADDR2;
}
void free_all_temp_addr() {
	tempAddr1Busy = 0;
	tempAddr2Busy = 0;
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

void print_symb(Symbol symb) {
  	printf("{name=%s, addr=%d, scope=%d}\n", symb.name, symb.addr, symb.scope);
}
