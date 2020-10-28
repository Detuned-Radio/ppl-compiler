#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "grammar.h"
#include "lexer.h"
#include "stack.h"
#include "Tree.h"
#include "parser.h"

void traverseParseTree()

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
    while(temp->sym != "TK_SIZE"){
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
    while(temp->sym != "TK_SIZE"){
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

      jaggDecStmt->t->j2->range1[x][a] = y;
      a++;
      temp2 = temp2->rightChild;

    }while(temp2->leftChild != temp2->rightChild);
    x++;
    init = init->rightChild;
  }while(init->leftChild != init->rightChild);
}


void propagateTypeExp(TreeNode* node) {
  // if identifier, add entry to TypeExpTable
  node -> t = node -> parent -> t;
  node -> tag = node -> parent -> tag;
  TreeNode* child = node -> leftChild;
  while(child) {
    propagateTypeExp(child);
    child = child -> rightSib;
  }
}

void populateTable(TreeNode* root , TypeExpTable* head){
  TypeExpTable* popu = head;
  Treenode* temp = root->rightChild->leftSib->leftChild; //DECLARATION_lIST
  do{
    TreeNode* iter = temp->leftChild->leftChild; //TYPE_DECLARATION_STMT
    if(iter->leftChild->rightSib->sym == "TK_LIST"){
      TreeNode* it = iter->rightChild->leftSib->leftChild; //id_list
      do{
        popu->identifier = strcpy(popu->identifier,it->leftChild->lexeme);
        popu->t = it->t;
        popu->next = (TypeExpTable*)malloc(sizeof(TypeExpTable));
        popu = popu->next;
        it = it->rightChild;
      }while(it->leftChild != it->rightChild)
    }
    else if(iter->leftChild->rightSib->sym == "ID"){
      popu->identifier = strcpy(popu->identifier,iter->leftChild->rightSib->lexeme);
      popu->t = iter->t;
      popu->next = (TypeExpTable*)malloc(sizeof(TypeExpTable));
      popu = popu->next;
    }
    temp = temp->rightChild;
  }while(temp->leftChild != temp->rightChild)
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
  if(isArrayVariable(expr)) {
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
  char* operator = expr -> leftChild -> rightSib -> sym;
  if(checkOperands(lhs, lhsTag, operator, rhs, rhsTag)) {
      if(operator == "TK_DIV") {
        // always evaluates to real
        expr -> tag = 0;
        expr -> t -> p -> primitiveType = 1; 
      } else {
        expr -> t = expr -> leftChild -> t;
        expr -> tag = expr -> leftChild -> tag;
      }
    return;
  } else {
    printf("ERROR");
  }
}

bool isArrayVariable(TreeNode* node) {
  if(node -> leftChild -> sym == "ID" &&
     node -> leftChild -> rightSib -> sym == "SQ_OP" &&
     node -> leftChild -> rightSib -> rightSib -> rightSib -> sym == "SQ_CL" &&
     node -> leftChild -> rightSib -> rightSib -> rightSib -> rightSib == NULL)
    return true;
  return false;
}

void processArrayVariable(TreeNode* arrVar) {
  getTypeExp(arrVar -> leftChild);
  TypeExp arr = arrVar -> leftChild -> t;
  typeExpTag arrTag = arrVar -> leftChild -> tag;
  TreeNode* indexList = arrVar -> rightChild -> leftSib;
  bool dynamic = false;
  if(arrTag == 1) {
    int dimensions = arr -> r -> dimensions;
    bool pass = true;
    while(indexList -> leftChild != indexList -> rightChild) {
      if(dimensions <= 0) {
        pass = false;
        break;
      }
      dimensions--;
      int index = atoi(indexList -> leftChild -> leftChild -> lexeme);
      bool isLiteral = true;
      if(index == 0) {
        for(int i = 0; i < strlen(indexList -> leftChild -> leftChild -> lexeme); i++) 
          if(!isdigit(indexList -> leftChild -> leftChild -> lexeme[i]))
            isLiteral = false;
      }
      if(isLiteral && (!(index >= arr -> r -> range[dimensions][0] && index <= arr -> r -> range[dimensions][1]))) {
        pass = false;
        break;
      }
    }
    if(pass) {
      arrVar -> tag = 0;
      arrVar -> t -> p -> primitiveType = 0;
    } else {
      printf("ERROR: Indexing error");
    }
  } else if(arrTag == 2) {
    int index0 = atoi(indexList -> leftChild -> leftChild -> lexeme);
    int index1 = atoi(indexList -> rightChild -> leftChild -> leftChild -> lexeme);
    if(indexList -> rightChild -> leftChild != indexList -> rightChild -> rightChild) {
      printf("ERROR: Indexing error (dimension mismatch)");
      return;
    }
    bool isLiteral0 = true;
    if(index0 == 0) {
      for(int i = 0; i < strlen(indexList -> leftChild -> leftChild -> lexeme); i++) 
        if(!isdigit(indexList -> leftChild -> leftChild -> lexeme[i]))
          isLiteral0 = false;
    }
    bool isLiteral1 = true;
    if(index1 == 0) {
      for(int i = 0; i < strlen(indexList -> rightChild -> leftChild -> leftChild -> lexeme); i++) 
        if(!isdigit(indexList -> rightChild -> leftChild -> leftChild -> lexeme[i]))
          isLiteral1 = false;
    }
    int low0 = arr -> j2 -> range0[0];
    int high0 = arr -> j2 -> range0[1];
    int size1 = arr -> j2 -> range1[index0 - low0];
    bool pass = (!isLiteral0 || ((index0 >= low0) && (index0 <= high0))) && 
                (!isLiteral1 || (index1 < size1));
    if(pass) {
      arrVar -> tag = 0;
      arrVar -> t -> p -> primitiveType = 0;
    } else {
      printf("ERROR: Indexing error")
    }

  } else if(arrTag == 3) {
    int index0 = atoi(indexList -> leftChild -> leftChild -> lexeme);
    int index1 = atoi(indexList -> rightChild -> leftChild -> leftChild -> lexeme);
    int index2 = atoi(indexList -> rightChild -> rightChild -> leftChild -> leftChild -> lexeme);
    if(indexList -> rightChild -> rightChild -> leftChild != indexList -> rightChild -> rightChild -> rightChild) {
      printf("ERROR: Indexing error (dimension mismatch)");
      return;
    }
    bool isLiteral0 = true;
    if(index0 == 0) {
      for(int i = 0; i < strlen(indexList -> leftChild -> leftChild -> lexeme); i++) 
        if(!isdigit(indexList -> leftChild -> leftChild -> lexeme[i]))
          isLiteral0 = false;
    }
    bool isLiteral1 = true;
    if(index1 == 0) {
      for(int i = 0; i < strlen(indexList -> rightChild -> leftChild -> leftChild -> lexeme); i++) 
        if(!isdigit(indexList -> rightChild -> leftChild -> leftChild -> lexeme[i]))
          isLiteral1 = false;
    }
    bool isLiteral2 = true;
    if(index2 == 0) {
      for(int i = 0; i < strlen(indexList -> rightChild -> rightChild -> leftChild -> leftChild -> lexeme); i++) 
        if(!isdigit(indexList -> rightChild -> rightChild -> leftChild -> leftChild -> lexeme[i]))
          isLiteral2 = false;
    }
    int low0 = arr -> j3 -> range0[0];
    int high0 = arr -> j3 -> range0[1];
    int size1 = arr -> j3 -> range1[index0][0];
    int size2 = arr -> j3 -> range1[index0][index1 + 1];
    bool pass = (!isLiteral0 || ((index0 >= low0) && (index0 <= high0))) && 
                (!isLiteral1 || (index1 < size1)) &&
                (!isLiteral2 || (index2 < size2));
    if(pass) {
      arrVar -> tag = 0;
      arrVar -> t -> p -> primitiveType = 0;
    } else {
      printf("ERROR: Indexing error")
    }
  }
}

void getTypeExp(TreeNode* id, TypeExpTable* table) {
  while(table) {
    if(strcmp(id -> lexeme, table -> identifier) == 0)
      break;
    table = table -> next;
  }
  if(table == NULL) {
    print("Type expression table entry missing for %s.", id -> lexeme);
    return;
  }
  id -> tag = table -> tag;
  id -> t = table -> t;
  return;
}

bool equalTypeExp(TypeExp a, typeExpTag atag, TypeExp b, typeExpTag btag) {
  if(atag != btag) return false;
  if(atag == 0) {
    return (a -> p -> primitiveType == b -> p -> primitiveType);
  } else if(atag == 1) {
    if(a -> r -> dimensions != b -> r -> dimensions)
      return false;
    for(int i = 0; i < a -> r -> dimensions; i++)
      for(int j = 0; j <= 1; j++)
        if(a -> r -> range[i][j] != b -> r -> range[i][j])
          return false;
    return true;
  } else if(atag == 2) {
    for(int j = 0; j <= 1; j++)
      if(a -> j2 -> range0[j] != b -> j2 -> range0[j])
        return false;
    for(int i = 0; i < ((a -> j2 -> range0)[1] - (a -> j2 -> range0)[0] + 1); i++)
      if(a -> j2 -> range1[i] != b -> j2 -> range1[i])
        return false;
    return true;
  } else {
    for(int j = 0; j <= 1; j++)
      if(a -> j3 -> range0[j] != b -> j3 -> range0[j])
        return false;
    for(int i = 0; i < ((a -> j3 -> range0)[1] - (a -> j3 -> range0)[0] + 1); i++)
      if(a -> j3 -> range1[i][0] != b -> j3 -> range1[i][0])
        return false;
      for(int j = 1; j <= range1[i][0]; j++)
        if(a -> j3 -> range1[i][j] != b -> j3 -> range1[i][j])
          return false;
      return true;
  }
}

bool checkOperands(TypeExp a, typeExpTag atag, char* op, TypeExp b, typeExpTag btag) {
  if(atag != btag)
    return false;
  // allow division of arrays?
  if(op == "TK_PLUS" || op == "TK_MINUS" || op == "TK_STAR") {
    if(atag == 0) {
      if(a -> p -> primitiveType == 0 || a -> p -> primitiveType == 1)
        return true;
      else {
        printf("ERROR: Cannot apply arithmetic opertors on booleans.");
        return false;
      }
    } else {
      if(equalTypeExp(a, atag, b, btag))
        return true;
      else {
        printf("ERROR: Size mismatch")
        return false;
      }
    }
  } else if(op == "TK_DIV") {
    if(atag == 0) {
      if(a -> p -> primitiveType == 0 || a -> p -> primitiveType == 1)
        return true;
      else {
        printf("ERROR: Cannot apply arithmetic opertors on booleans.");
        return false;
      }
    } else {
      printf("ERROR: Elementwise division (Arrays of real type) not supported.")
      return false;
    }
  } else if(op == "TK_AND" || op == "TK_OR") {
    if(atag == 0) {
      if(a -> p -> primitiveType == 2)
        return true;
      else {
        printf("ERROR: Cannot apply logical opertors on non-boolean types.");
        return false;
      }
    } else {
      printf("ERROR: Elementwise logical operations not supported.")
      return false;
    }
  } else {
    printf("ERROR: Invalid operator.\n");
  }
}
