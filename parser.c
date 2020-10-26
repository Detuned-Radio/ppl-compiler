#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "grammar.h"
#include "lexer.h"
#include "stack.h"
#include "Tree.h"
#include "parser.h"

TreeNode* createParseTree(Rule* grammar, TokenList* tokenStream) {
	//create stack
	Stack* st = createStack();
	//create tree root
	TreeNode* root = createNode(tokenStream -> token, false);
	root -> depth = 0;
	//push start symbol program on to stack
	printf("Pushed %s\n", root -> sym);
	push(st, root);
	//try applying all rules for program
	bool pass = false;
	for(int i = 0; i < NUM_RULES; i++) {
		if(strcmp(grammar[i].lhs, "PROGRAM") == 0) {
			root -> r = &grammar[i];
			printf("Apply rule %d\n", i+1);
			pass = applyRule(grammar, i, tokenStream, tokenStream, st);
			if(pass)
				return root;
			root -> r = NULL;
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
	SymList* ruleNode = grammar[rule_index].rhs;
	while(ruleNode) {
		TreeNode* newNode = createNode(ruleNode -> val, ruleNode -> isTerminal);
		printf("Added %s to %s\n", newNode -> sym, lhs -> sym);
		addChild(lhs, newNode);
		ruleNode = ruleNode -> next;
	}
	//push grammar[rule_index].rhs in reverse order
	int push_count = 0;
	TreeNode* currNode = lhs -> rightChild;
	while(currNode) {
		printf("Pushed %s\n", currNode -> sym);
		push(st, currNode);
		push_count++;
		currNode = currNode -> leftSib;
	}
	//set flag pass to false
	bool pass = false;
	bool terminalPass = true;
	// if a terminal, try consuming
		//if success continue with new top of stack, may also be terminal
		//else return false
	Stack* flushSt = createStack();
	while(!isEmpty(st) && top(st) -> isTerminal) {
		if(curr_ptr -> token == top(st) -> sym) {
			push_count--;
			printf("Popped %s (%s) [%d]\n", top(st) -> sym, curr_ptr -> lexeme, push_count);
			TreeNode* poppedStackNode = pop(st);
			push(flushSt, poppedStackNode);
			curr_ptr = curr_ptr -> next;
		}
		else {
			printf("Match failed. st: %s, tokenStream: %s\n", top(st) -> sym, curr_ptr -> token);
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
			if(grammar[i].lhs == top(st) -> sym) {
				top(st) -> r = &grammar[i];
				printf("Applied rule %d\n", i+1);
				bool res = applyRule(grammar, i, tokenStream, curr_ptr, st);
				if(res) {
					return true;
				}
				printf("Rule %d failed\n", i+1);
				top(st) -> r = NULL;
			}
		}
	}
	
	while(!isEmpty(flushSt)) {
		TreeNode* poppedStackNode = pop(flushSt);
		push(st, poppedStackNode);
		push_count++;
	}
	//pop grammar[rule_index].rhs in sequential order
	while(push_count > 0) {
		pop(st);
		push_count--;
	}
	//remove children from tree
	deleteAllChildren(lhs);
	//push grammar[rule_index].lhs on stack
	push(st, lhs);
	//return false
	return false;
}

int main(int argc, char* argv[]) {
	if(argc != 4) {
		printf("Usage: ./grammartest <path to grammar txt> <number of rules> <path to source code>\n");
		return 0;
	}
	char* grammar_path = argv[1];
	int num_rules = atoi(argv[2]);
	Rule* grammar = readGrammar(grammar_path, num_rules);
	printGrammar(grammar, num_rules);
	
	FILE* fptr=fopen("test.txt","r");
    TokenList* tokenStream=tokeniseSourcecode(fptr);
    fclose(fptr);

    TreeNode* root = createParseTree(grammar, tokenStream);

    printf("parse tree is created successfully\n");
}