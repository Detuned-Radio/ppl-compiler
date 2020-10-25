#include "Tree.h"
treeNode* createNode(char name[],char sym[],bool isLeaf,typeExp t,char lexemes[],int line_no,Rule r,int depth){
  treeNode* temp=(treeNode*)malloc(sizeof(treeNode));
  strcpy(temp->name,name);
  strcpy(temp->sym,sym);
  temp->isLeaf=isLeaf;
  temp->t=t;
  strcpy(temp->lexemes,lexemes);
  temp->line_no=line_no;
  temp->r=r;
  temp->depth=depth;
  temp->parent=NULL;
  temp->left=NULL;
  temp->right=NULL;
  temp->child=NULL;
  return temp;
}
