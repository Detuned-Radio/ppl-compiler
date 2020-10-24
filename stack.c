#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "stack.h"




void push(TreeNode** head,int data){
  TreeNode *temp=(TreeNode*)malloc(sizeof(TreeNode));
  temp->data=data;
  temp->next=(*head);
  (*head)=temp;
}

TreeNode* pop(TreeNode** head){
  if(*head==NULL){
    return *head;
  }
  TreeNode* temp=*head;
  *head=(*head)->next;
  return temp;

}
