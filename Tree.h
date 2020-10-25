#ifndef TREE_H
#define TREE_H

typedef struct _treeNode treeNode;
typedef struct _typeExpTable typeExpTable;
typedef struct type_prim prim;
typedef struct type_rect rect;
typedef struct type_jagg2 jagg2;
typedef struct type_jagg3 jagg3;
typedef _typeExp typeExp;
typedef enum type1{prim,rect,jagg}type1;
typedef enum type2{integer,real,boolean}type2;

struct type_prim{
  type2 t;
};
struct type_rect{
  int dimensions;
  int range[][2];

};
struct type_jagg2 {
  int range1[2];
  int range2[];
};
struct type_jagg3{
  int range1[2];
  int range2[][];
};

union _typeExp{
    prim p;
    rect r;
    jagg2 j2;
    jagg3 j3;
};
struct _typeExpTable{
  char name[20];
  bool isArray;
  type1 rect_jagg;
  char stat_dyn[16];
  typeExp t;
};

struct _treeNode{
char name[20];
char sym[SYMBOL_LEN];
bool isLeaf;
typeExp t;
char lexemes[13];
int line_no;
Rule r;
int depth;
treeNode* parent;
treeNode* left;
treeNode* right;
treeNode* child;
};

treeNode* createNode(char name[],char sym[],bool isLeaf,typeExp t,char lexemes[],int line_no,Rule r,int depth);

#endif
