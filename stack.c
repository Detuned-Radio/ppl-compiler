#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "grammar.h"
#include "lexer.h"
#include "stack.h"

Stack* createStack(void) {
  Stack* st = malloc(sizeof(Stack));
  st -> top = NULL;
  st -> size = 0;
  return st;
}

void push(Stack* st, TreeNode* data){
  StackNode* newNode = (StackNode*) malloc(sizeof(StackNode));
  temp -> data = data;
  temp -> next = st -> top;
  st -> top = temp;
  (st -> size)++;
}

TreeNode* pop(Stack* st){
  if(st -> top == NULL){
    return NULL;
  }
  StackNode* poppedNode = st -> top;
  TreeNode* poppedData = poppedNode -> data;
  st -> top = poppedNode -> next;
  (st -> size)--;
  free(poppedNode);
  return poppedData;
}

bool isEmpty(Stack* st) {
  return (st -> size == 0);
}

int main(void) {
  Stack* st = createStack();
  for(int i = 0; i < 10; i++)
    push(st, i+1);
  while(!isEmpty(st)) {
    printf("%d\n", pop(st));
  }
  return 0;
}