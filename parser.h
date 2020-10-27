#ifndef PARSER_H
#define PARSER_H

TreeNode* createParseTree(Rule* grammar, TokenList* tokenStream);
bool applyRule(Rule* grammar, int rule_index, TokenList* tokenStream, TokenList* curr_ptr, Stack* st);
void printParseTree(TreeNode* root, Rule* grammar);

#endif