#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "grammar.h"
#include "lexer.h"
#include "stack.h"
#include "Tree.h"
#include "parser.h"

void declaration_statement(TreeNode* root)
{
    TreeNode* temp=root->rightChild->leftSib;
    temp=temp->leftChild;
    while(temp->leftChild != temp->rightChild)
    {
        store(temp->leftChild);
        temp=temp->rightChild;
    }
    store(temp);
}


void store(TreeNode* tr ){

  if(tr->leftChild->sym == "PRIM_DECLARATION_STMT"){
    tr->tag = 0; //setting tag to prim
    TreeNode* temp=node->leftChild;
    if(temp->rightChild->leftChild->lexeme == "integer")
      temp->t->t = 0;
    if(temp->rightChild->leftChild->lexeme == "real")
      temp->t->t = 1;
    if(temp->rightChild->leftChild->lexeme == "boolean")
      temp->t->t = 2;
  }

  if(tr->leftChild->sym == "RECTARR_DECLARATION_STMT"){
    tr->tag = 1;  // setting tag to rect
    populate_rect(tr->leftChild);
  }

}

void populate_rect(TreeNode* tr){
  TreeNode* temp = tr->leftChild;
  while(temp->sym != "RANGE_LIST")
    temp = temp->rightSib;

//code to calculate number of dimensions = n
  TreeNode* temp2 = temp;
  while(temp2->leftChild != temp2->rightChild){
      tr->t->dimensions++;
      temp2 = temp2->rightChild;
  }
  tr->t->dimensions++;
  int n = tr->t->dimensions;

  // allocating memory to n ranges
  tr->t->range = (int **)malloc(sizeof(int *) * n);
  for(int i = 0 ; i<n ; i++){
    tr->t->range[i] = (int *)malloc(sizeof(int)*2);
  }

  // assigning values to ranges
  int x = 0;
  while(temp->leftChild != temp->rightChild){
      tr->t->range[x][0] = temp->leftChild->leftChild->rightSib;  //range list --> range --> second child gives first subscript of range
      tr->t->range[x][1] = temp->leftChild->leftChild->rightSib->rightSib->rightSib;  //range list --> range --> second child gives second subscript of range
      temp = temp->rightChild;
      x++;
  }
  tr->t->range[x][0] = temp->leftChild->leftChild->rightSib;
  tr->t->range[x][1] = temp->leftChild->leftChild->rightSib->rightSib->rightSib;

}
