/*
Group No.26
Arshit Modi      2018A7PS0191P
Devanshu         2018A7PS0194P
Guntaas Singh    2018A7PS0269P
Siddarth Agrawal 2018A7PS0359P
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "grammar.h"
#include "lexer.h"
#include "stack.h"
#include "Tree.h"
#include "parser.h"
#include "traverseParseTree.h"


int main(int argc, char* argv[]) {
	if(argc != 4) {
		printf("Usage: ./grammartest <path to grammar txt> <number of rules> <path to source code>\n");
		return 0;
	}
	char* grammar_path = argv[1];
	int num_rules = atoi(argv[2]);
	Rule* grammar = readGrammar(grammar_path, num_rules);
	// printGrammar(grammar, num_rules);

	FILE* fptr=fopen(argv[3], "r");
    TokenList* tokenStream=tokeniseSourcecode(fptr);
    fclose(fptr);
    // printTokenStream(tokenStream);

    TreeNode* root = createParseTree(grammar, tokenStream);
    printf("parse tree is created successfully\n");

    printParseTree(root, grammar);

    traverseParseTree(root);
}
