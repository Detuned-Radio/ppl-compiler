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
    processRectDecStmt(decStmt -> leftChild); //pending: variable 
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

void traverseAsgList(TreeNode* root, TypeExpTable* table) {
  TreeNode* programBody = root -> rightChild -> leftSib;
  TreeNode* asgList = programBody -> rightChild;
  while(asgList -> leftChild != asgList -> rightChild)
  {
      processAsgStmt(asgList -> leftChild);  // process decStmt
      asgList = asgList -> rightChild; //move to next decListNode
  }
  processAsgStmt(asgList -> leftChild); //process last decStmt
}

void processAsgStmt(TreeNode* asgStmt){
  processExpression(asgStmt -> rightChild -> leftSib);
  getTypeExp(asgStmt -> leftChild);
  TypeExp lhs = asgStmt -> leftChild -> t;
  typeExpTag lhsTag = asgStmt -> leftChild -> tag;
  TypeExp rhs = asgStmt -> rightChild -> leftSib -> t;
  typeExpTag rhsTag = asgStmt -> rightChild -> leftSib -> tag;
  if(lhsTag == 0 && equalTypeExp(lhs, lhsTag, rhs, rhsTag)) {
    asgStmt -> t = lhs;
    asgStmt -> tag = lhsTag;
  } else {
    printf("ERROR: ASSIGNMENT\n");
  }
}

void processExpression(TreeNode* expr) {
  if(expr -> leftChild == NULL) {
    if(expr -> sym == "CONSTANT") {
      expr -> tag = 0;
      expr -> t -> p -> primitiveType = 0;
      return;
    }
    if(expr -> sym == "ID") {
      getTypeExp(expr);
      return;
    }
  }
  if(expr -> rightChild -> sym == "SQ_CL") {
    processArrayVariable(expr);
    return;
  }
  if(expr -> leftChild == expr -> rightChild) {
    processExpression(expr -> leftChild);
    expr -> t = expr -> leftChild -> t;
    expr -> tag = expr -> leftChild -> tag;
    return;
  }
  processExpression(expr -> leftChild);
  processExpression(expr -> rightChild);
  TypeExp lhs = expr -> leftChild -> t;
  typeExpTag lhsTag = expr -> leftChild -> tag;
  TypeExp rhs = expr -> rightChild -> leftSib -> t;
  typeExpTag rhsTag = aexpr -> rightChild -> leftSib -> tag;
  char* operator = expr -> leftChild -> rightSib;
  if(checkOperands(lhs, lhsTag, sym, rhs, rhsTag)) {
    expr -> t = expr -> leftChild -> t;
    expr -> tag = expr -> leftChild -> tag;
    return;
  } else {
    printf("ERROR");
  }
}

void processArrayVariable(TreeNode* arrVar) {
  getTypeExp(arrVar -> leftChild);
  TypeExp arr = arrVar -> leftChild -> t;
  typeExpTag arrTag = arrVar - >leftChild -> tag;
  TreeNode* indexList = arrVar -> rightChild -> leftSib;
  if(arrTag == 1) {
    int dimensions = arr -> r -> dimensions;
    while(indexList -> leftChild != indexList -> rightChild) {
      if(dimensions <= 0)
        break;
      dimensions--;
      int index = atoi(indexList -> leftChild -> leftChild -> lexeme);
      if(index >= arr -> r -> range[dimensions][0] && index <= arr -> r -> range[dimensions][1]) {
        arrVar -> tag = 0;
        arrVar -> t -> p -> primitiveType = 0;
        return;
      } else {
        printf("ERROR");
      }
    }
  } else if(arrTag == 2) {

  } else if(arrTag == 3) {
    
  }
}


getTypeExp
equalTypeExp
checkOperands