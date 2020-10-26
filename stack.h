#ifndef STACK_H
#define STACK_H
#include "Tree.h"

typedef struct StackNode {
  TreeNode* data;
  struct StackNode* next;
} StackNode;

typedef struct Stack {
	StackNode* top;
	int size;
} Stack;

Stack* createStack(void);
void push(Stack* st, TreeNode* data);
TreeNode* pop(Stack* st);
bool isEmpty(Stack* st);
#endif