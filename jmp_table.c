#include <stdio.h>
#include <stdlib.h>
#include "jmp_table.h"
Node* while_root = NULL;
Node* if_root = NULL;

Node* new_node(int inst_nb)
{
    Node* stackNode = (Node*) malloc(sizeof(Node));
    stackNode->inst_nb = inst_nb;
    stackNode->next = NULL;
    return stackNode;
}

int is_empty(root) {
    return !root;
}

void push_while_start(int inst_nb) {
	Node* stackNode = new_node(inst_nb);
    stackNode->next = while_root;
    while_root = stackNode;
}

int pop_while_start() {
	if (is_empty(while_root)) {
    	fprintf(stderr, "Cannot pop body start, the stack is empty\n");
		exit(1);
    }
    Node* temp = while_root;
    while_root = while_root->next;
    int popped = temp->inst_nb;
    free(temp);
 
    return popped;
}

void push_if_start(int inst_nb) {
	Node* stackNode = new_node(inst_nb);
    stackNode->next = if_root;
    if_root = stackNode;
}

int pop_if_start() {
	if (is_empty(if_root)) {
    	fprintf(stderr, "Cannot pop body start, the stack is empty\n");
		exit(1);
    }
    Node* temp = if_root;
    if_root = if_root->next;
    int popped = temp->inst_nb;
    free(temp);
 
    return popped;
}
