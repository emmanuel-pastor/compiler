#ifdef SYMB_TABLE_H
#define SYMB_TABLE_H
typedef struct Symbol {
    char* name;
    int addr;
    int scope;
} Symbol;
void push_symb(char* name);
void pop_symb();
int exists_symb(char* name);
void incr_scope();
void decr_scope();
void print_symb_table();
void print_symb(Symbol symb);
#endif
