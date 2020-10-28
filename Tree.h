#ifndef TREE_H
#define TREE_H

typedef struct TreeNode TreeNode;
typedef struct TypeExpTable TypeExpTable;
typedef struct prim_t prim_t;
typedef struct rect_t rect_t;
typedef struct jagg2_t jagg2_t;
typedef struct jagg3_t jagg3_t;
typedef union TypeExp TypeExp;
typedef enum typeExpTag {prim, rect, jagg2, jagg3} typeExpTag;
typedef enum primType {integer, real, boolean} primType;
typedef enum statDynTag {na, stat, dyn} statDynTag;

struct prim_t {
  primType primitiveType;
};
struct rect_t {
  int dimensions;
  int** range; // [][2]
};
struct jagg2_t {
  int range0[2];
  int* range1; //[]
};
struct jagg3_t {
  int range0[2]; 
  int** range1; //[][]
};

union TypeExp {
  prim_t p;
  rect_t r;
  jagg2_t j2;
  jagg3_t j3;
};

struct TypeExpTable {
  char identifier[LEXEME_LEN];
  typeExpTag tag;
  statDynTag statDyn;
  TypeExp t;
  TypeExpTable* next;
};

struct TreeNode {
  char* sym;
  char lexeme[LEXEME_LEN];
  int line_no;
  Rule* r;
  typeExpTag tag;
  TypeExp t;
  bool isTerminal;
  int depth;
  TreeNode* parent;
  TreeNode* leftSib;
  TreeNode* rightSib;
  TreeNode* leftChild;
  TreeNode* rightChild;
};

TreeNode* createNode(char* sym, bool isTerminal);
void addChild(TreeNode* parent, TreeNode* child);
void deleteAllChildren(TreeNode* parent);

#endif
