#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grammar.h"

TreeNode* createParseTree(Rule* grammar, TokenList* tokenStream) {
	//create stack
	//create tree root
	//push start symbol program on to stack

	//try applying all rules for program
	bool pass = false;
	for(int i = 0; i < NUM_RULES; i++) 
		if(strcmp(grammar[i].lhs, "PROGRAM") == 0)
			pass = pass || applyRule(grammar, i, tokenStream, tokenStream, stack);
	
	//check pass flag
		//if true, return tree root
		//if false, deallocate stack and treem report erroneous code
	if(pass)
		return root;
	else {
		printf("Parsing failed: Syntax error\n");
		return NULL;
	}
}

bool applyRule(Rule* grammar, int rule_index, TokenList* tokenStream, TokenList* curr_ptr, Stack* stack) {
	//pop top of stack
	//push grammar[rule_index].rhs in reverse order
	//add children to parse tree
	//set flag pass to false
	bool pass = false;
	// if a terminal, try consuming
		//if success continue with new top of stack, may also be terminal
		//else return false
	// if stack empty AND input completely read return true
	//loop over grammar and try applying all possible rules on top of stack, at each point ORing result with flag
		// return true if flag is set at any point

	//remove children from tree
	//pop grammar[rule_index].rhs in sequential order
	//push grammar[rule_index].lhs on stack
	//return false

}