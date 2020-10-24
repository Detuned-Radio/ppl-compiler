#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct t{
  int data;
  struct t* next;
} TreeNode;

void push(TreeNode** head,int data);
TreeNode* pop(TreeNode** head);
