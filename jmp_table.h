#ifndef JMP_TABLE_H
#define JMP_TABLE_H
typedef struct Node {
    int inst_nb;
    struct Node* next;
} Node;

void push_while_start(int inst_nb);
int pop_while_start();
void push_if_start(int inst_nb);
int pop_if_start();
#endif
