/*#ifndef LEXER_H
#define LEXER_H*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
  int data;
} TreeNode;

typedef struct t{
  TreeNode* data;
  struct t* next;
} StackNode;


void createStack(StackNode** head);
void push(StackNode** head,TreeNode* data);
TreeNode* pop(StackNode** head);
