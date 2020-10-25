#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "stack.h"


void push(StackNode** head,TreeNode* data){

  StackNode *temp=(StackNode*)malloc(sizeof(StackNode));
  temp->data=data;
  temp->next=*head;
  (*head)=temp;
}

TreeNode* pop(StackNode** head){
  if(*head==NULL){
    return NULL;
  }
  StackNode* t=*head;
  TreeNode* temp=(*head)->data;
  *head=t->next;
  free(t);
  return temp;
}
