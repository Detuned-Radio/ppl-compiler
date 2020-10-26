#include "Tree.H"
void declaration_statement(TreeNode* root)
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
