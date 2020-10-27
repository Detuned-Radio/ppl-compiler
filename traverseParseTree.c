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
    processJagg2DDecStmt(decStmt -> leftChild);
  } else if(decStmt -> leftChild -> leftChild -> sym == "JAGGARR3D_DECLARATION_STMT") {
    decStmt -> leftChild -> tag = 3;  // setting tag to jagg3
    processJagg3DDecStmt(decStmt -> leftChild);
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