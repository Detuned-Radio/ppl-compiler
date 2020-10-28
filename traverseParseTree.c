#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "grammar.h"
#include "lexer.h"
#include "stack.h"
#include "Tree.h"
#include "parser.h"

TypeExpTable* traverseDecList(TreeNode* root) {
    TreeNode* programBody = root -> rightChild -> leftSib;
    TreeNode* decList = programBody -> leftChild;
    while(decList -> leftChild != decList -> rightChild)
    {
        processDecStmt(decList -> leftChild);  // process decStmt
        decList = decList -> rightChild; //move to next decListNode
    }
    processDecStmt(decList -> leftChild); //process last decStmt
}

void processDecStmt(TreeNode* decStmt) {
  if(decStmt -> leftChild -> sym == "PRIM_DECLARATION_STMT") {
    decStmt -> leftChild -> tag = 0; //setting tag to prim
    processPrimDecStmt(decStmt -> leftChild);
  } else if(decStmt -> leftChild -> sym == "RECTARR_DECLARATION_STMT") {
    decStmt -> leftChild -> tag = 1;  // setting tag to rect
    processRectDecStmt(decStmt -> leftChild);
  } else if(decStmt -> leftChild -> leftChild -> sym == "JAGGARR2D_DECLARATION_STMT") {
    decStmt -> leftChild -> tag = 2;  // setting tag to jagg2
    processJagg2DDecStmt(decStmt-> leftChild->leftChild);
      decStmt-> leftChild->typeExp = decStmt-> leftChild->leftChild->TypeExp;
  } else if(decStmt -> leftChild -> leftChild -> sym == "JAGGARR3D_DECLARATION_STMT") {
    decStmt -> leftChild -> tag = 3;  // setting tag to jagg3
    processJagg3DDecStmt(decStmt -> leftChild->leftChild);
      decStmt-> leftChild->typeExp = decStmt-> leftChild->leftChild->TypeExp;

  }
  // copy to decStmt
  decStmt -> tag = decStmt -> leftChild -> tag;
  decStmt -> t = decStmt -> leftChild -> t;
  // propagate to descendants
  propagateTypeExp(decStmt -> leftChild);

}

void processPrimDecStmt(TreeNode* primDecStmt) {
  TreeNode* primTypeNode = primDecStmt -> rightChild -> leftSib -> leftChild;
  if(strcmp(primTypeNode -> lexeme, "integer") == 0)
    primDecStmt -> t -> p -> primitiveType = 0;
  if(strcmp(primTypeNode -> lexeme, "real") == 0)
    primDecStmt -> t -> p -> primitiveType = 1;
  if(strcmp(primTypeNode-> lexeme, "boolean") == 0)
    primDecStmt -> t -> p -> primitiveType = 2;
}

void processRectDecStmt(TreeNode* rectDecStmt){
  TreeNode* temp = rectDecStmt -> leftChild;
  while(temp -> sym != "RANGE_LIST")
    temp = temp -> rightSib;
  TreeNode* rangeList = temp;

//code to calculate number of dimensions = n
  int dimensions = 0;
  while(temp -> leftChild != temp -> rightChild){
      dimensions++;
      temp = temp -> rightChild;
  }
  dimensions++;
  rectDecStmt -> t -> r -> dimensions = dimensions;

  // allocating memory to n ranges
  rectDecStmt -> t -> r -> range = (int**) malloc(sizeof(int*) * dimensions);
  for(int i = 0 ; i<n ; i++){
    rectDecStmt -> t -> r -> range[i] = (int*) malloc(sizeof(int) * 2);
  }

  // assigning values to ranges
  int x = 0;
  while(rangeList-> leftChild != rangeList -> rightChild){
      rectDecStmt -> t -> r -> range[x][0] = rangeList -> leftChild -> leftChild -> rightSib;  //range list - ->  range - ->  second child gives first subscript of range
      rectDecStmt -> t -> r -> range[x][1] = rangeList -> leftChild -> leftChild -> rightSib -> rightSib -> rightSib;  //range list - ->  range - ->  second child gives second subscript of range
      rangeList = rangeList -> rightChild;
      x++;
  }
  rectDecStmt -> t -> r -> range[x][0] = rangeList -> leftChild -> leftChild -> rightSib;
  rectDecStmt -> t -> r -> range[x][1] = rangeList -> leftChild -> leftChild -> rightSib -> rightSib -> rightSib;

}

void processJagg2DDecStmt(TreeNode * jaggDecStmt){
   TreeNode * range = jaggDecStmt->leftChild;
   while(range->sym!= "RANGE")
    range = range->rightSib;

  jaggDecStmt->t->j2->range0[0] = range->leftChild -> rightSib;
  jaggDecStmt->t->j2->range0[1] =  range-> leftChild -> rightSib -> rightSib -> rightSib;

  int numRows = range0[1]-range0[0]+1;
  jaggDecStmt->t->j2->range1 = (int*) malloc(sizeof(int)* numRows);

  TreeNode* init=jaggDecStmt->rightChild; //init = JAGGARR2D_INIT_LIST
  int x = 0;
  do
  {
    TreeNode* temp=init->leftChild->leftChild;//temp = "R1"
    while(temp != "SIZE"){
      temp = temp->rightSib;
    }
    jaggDecStmt->t->j2->range1[x] = (atoi)temp->rightSib->lexeme;
    x++;
    init = init->rightChild;
  }while(init->leftChild != init->rightChild);
}

void processJagg3DDecStmt(TreeNode * jaggDecStmt){
  TreeNode * range = jaggDecStmt->leftChild;
  while(range->sym!= "RANGE")
   range = range->rightSib;

  jaggDecStmt->t->j3->range0[0] = range->leftChild -> rightSib;
  jaggDecStmt->t->j3->range0[1] =  range-> leftChild -> rightSib -> rightSib -> rightSib;

  int numRows = range0[1]-range0[0]+1;
  jaggDecStmt->t->j3->range1 = (int**) malloc(sizeof(int*) * numRows);

  TreeNode* init=jaggDecStmt->rightChild; //init = JAGGARR3D_INIT_LIST
  int x = 0;
  do
  {
    TreeNode* temp=init->leftChild->leftChild;//temp = "R1"
    while(temp != "SIZE"){
      temp = temp->rightSib;
    }
    jaggDecStmt->t->j2->range1[x] = (int*)malloc(sizeof(int)*((atoi)temp->rightSib->lexeme)+1); 
    jaggDecStmt->t->j2->range1[x][0] = ((atoi)temp->rightSib->lexeme); //size of row list stored at first place
    TreeNode* temp2 = temp->parent->rightChild->leftSib;  // temp2 = JAGGARR3D_ROW_LIST
    int y=0;
    int a=1;
    do
    {
      TreeNode* temp3=temp2->leftChild;//temp3 = JAGGARR3D_VAL_LIST
      do{
        y++;
        temp3=temp3->rightChild;
      }
      while(temp3->leftChild !=temp3->rightChild)

      jaggDecStmt->t->j2->range1[x][a];
      a++;
      temp2 = temp2->rightChild;

    }while(temp2->leftChild != temp2->rightChild)



    x++;
    init = init->rightChild;
  }while(init->leftChild != init->rightChild);
}


}

void propagateTypeExp(TreeNode* node) {
  // if identifier, add entry to TypeExpTable
  if(node -> sym == "ID") {

  }
  node -> t = node -> parent -> t;
  node -> tag = node -> parent -> tag;
  TreeNode* child = node -> leftChild;
  while(child) {
    propagateTypeExp(child);
    child = child -> rightSib;
  }
}
