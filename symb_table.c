#include <stdio.h>
#include "symb_table.h"
#define MAX_SYMB 200

typedef struct Symbol {
    char* name;
    int addr;
    int scope;
} Symbol;

Symbol symb_table[MAX_SYMB];
int top_index = 0;
int scope = -1;

void push_symb(char* name) {
	Symbol symb = {name, top_index, scope};
	/*printf("pushed: ");
	print_symb(symb);*/
	symb_table[top_index] = symb;
	top_index++;
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
