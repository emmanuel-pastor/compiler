#include <stdio.h>
#include "symb_table.h"

typedef struct Symbol {
    char* name;
    char* type;
    int addr;
    int scope;
} Symbol;

Symbol symb_table[200];
int top_index = 0;
int scope = -1;

void push_symb(char* name) {
	Symbol symb = {name, "int", top_index, scope};
	/*printf("pushed: ");
	print_symb(symb);*/
	symb_table[top_index] = symb;
	top_index++;
}

void pop_symb() {
	/*printf("poped: ");
	print_symb(symb_table[top_index-1]);*/
	Symbol nullSymb = {NULL, NULL, 0, 0};
	symb_table[top_index-1] = nullSymb;
	top_index--;
}

int exists_symb(char* name) {
	int found = 0;
	int i = 0;
	while(!found) {
		if(symb_table[i].name == name) {
			found = 1;
		}
		i++;
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
  while(symb.name != NULL) {
  	print_symb(symb);
  	symb = symb_table[i];
  	i++;
  }
}

void print_symb(Symbol symb) {
  	printf("{name=%s, type=%s, addr=%d, scope=%d}\n", symb.name, symb.type, symb.addr, symb.scope);
}
