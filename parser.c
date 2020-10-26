#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grammar.h"
#include "stack.h"
#include "tree.h"

TreeNode* createParseTree(Rule* grammar, TokenList* tokenStream) {
	//create stack
	Stack* st = createStack();
	//create tree root
	TreeNode* root = createNode("program", "PROGRAM", ...);
	//push start symbol program on to stack
	push(st, root);
	//try applying all rules for program
	bool pass = false;
	for(int i = 0; i < NUM_RULES; i++) {
		if(strcmp(grammar[i].lhs, "PROGRAM") == 0) {
			pass = applyRule(grammar, i, tokenStream, tokenStream, st);
			if(pass)
				return root;
		}
	}
	
	//check pass flag
		//if true, return tree root
		//if false, deallocate stack and tree report erroneous code
	printf("Parsing failed: Syntax error\n");
	return NULL;
}

bool applyRule(Rule* grammar, int rule_index, TokenList* tokenStream, TokenList* curr_ptr, Stack* st) {
	//pop top of stack
	TreeNode* lhs = pop(st);
	//add children to parse tree
	SymList* ruleNode = grammar[rule_index].rhsHead;
	while(ruleNode) {
		TreeNode* newNode = createNode(...ruleNode...);
		addChild(lhs, newNode);
		ruleNode = ruleNode -> next;
	}
	//push grammar[rule_index].rhs in reverse order
	int push_count = 0;
	TreeNode* currNode = root -> rightChild;
	while(currNode) {
		push(st, currNode);
		push_count++;
		currNode = currNode -> leftSibling;
	}
	//set flag pass to false
	bool pass = false;
	bool terminalPass = true;
	// if a terminal, try consuming
		//if success continue with new top of stack, may also be terminal
		//else return false
	while(!isEmpty(st) && top(st) -> isTerminal && push_count > 0) {
		if(strcmp(curr_ptr -> token, top(st) -> token) == 0) {
			pop(st);
			push_count--;
			curr_ptr = curr_ptr -> next;
		}
		else {
			terminalPass = false;
			break;
		}
	}
	if(terminalPass) {
		// if stack empty AND input completely read return true
		if(isEmpty(st) && curr_ptr == NULL)
			return true;
		//loop over grammar and try applying all possible rules
			// return true if flag is set at any point
		for(int i = 0; i < NUM_RULES; i++) {
			if(strcmp(grammar[i].lhs, top(st) -> token) == 0) {
				res = applyRule(grammar, i, tokenStream, curr_ptr, st);
				if(res) {
					return true;
				}
			}
		}
	}
	
	// every rule for non-terminal failed

	//pop grammar[rule_index].rhs in sequential order
	while(push_count--) {
		pop(st);
	}
	//remove children from tree
	deleteAllChildren(lhs);

	
	//push grammar[rule_index].lhs on stack
	push(st, lhs);
	//return false
	return false;
}

createNode(...)
addChild(TreeNode*, ...)
deleteChild(...)