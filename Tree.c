#include "Tree.h"

TreeNode* createNode(char* sym, char lexeme[LEXEME_LEN], int line_no, Rule* r, bool isLeaf) {
  TreeNode* newNode = (TreeNode*) malloc(sizeof(TreeNode));
  newNode -> sym = sym;
  strcpy(newNode -> lexeme, lexeme);  
  newNode -> line_no = line_no;
  newNode -> r = r;
  newNode -> isLeaf = isLeaf;
  newNode -> parent = NULL;
  newNode -> leftChild = NULL;
  newNode -> rightChild = NULL;
  newNode -> leftSib = NULL;
  newNode -> rightSib = NULL;
  return newNode;
}

TreeNode* addChild(TreeNode* parent, TreeNode* child){
  if(parent -> rightChild) {
    parent -> rightChild -> rightSib = child;
    child -> leftSib = parent -> rightChild;
  }
  parent -> rightChild = child;
  child -> parent = parent;
  child -> depth = parent -> depth + 1;
  return p;
}

void deleteAllChildren(TreeNode* p) {
    TreeNode* temp = p -> leftChild;
    TreeNode* extra = temp;
    while(temp != NULL) {
        temp = temp -> right;
        free(extra);
        extra = temp;
    }
    p -> leftchild = NULL;
    p -> rightChild = NULL;
}
