#include "Tree.H"
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
