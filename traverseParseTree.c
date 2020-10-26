#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "grammar.h"
#include "lexer.h"
#include "stack.h"
#include "Tree.h"
#include "parser.h"

void declaration_statement(TreeNode* root, TypeExpTable t)
{
    TreeNode* temp=root->rightChild->leftSib;
    temp=temp->leftChild;
    while(!temp.isTerminal)
    {
        store(temp->leftChild);
        temp=temp->rightChild;
    }
    store(temp);
}
