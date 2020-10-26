#include "Tree.h"

treeNode* createNode(char sym[], typeExp t, char lexemes[], int line_no, Rule r){
  treeNode* temp=(treeNode*)malloc(sizeof(treeNode));
  strcpy(temp->sym,sym);
  temp->isLeaf= true;
  temp->t=t;
  strcpy(temp->lexemes,lexemes);
  temp->line_no=line_no;
  temp->r=r;
  temp->depth= 0;
  temp->parent=NULL;
  temp->left=NULL;
  temp->right=NULL;
  temp->child=NULL;
  return temp;
}

treeNode* addChild(treeNode* p, treeNode* c){
  treeNode* t = p->child;
  while(t!= NULL){
    t = t->right;
  }
  t = c;
  t->parent = p;
  t->depth = p->depth+1;
}

void deleteAllChildren(treeNode* p)
{
    treeNode* temp= p->child;
    treeNode* extra=temp;
    while(temp!=NULL)
    {
        temp=temp->right;
        free(extra);
        extra=temp;
    }
    p->child=NULL;
}
