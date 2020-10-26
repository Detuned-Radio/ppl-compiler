#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "grammar.h"
#include "lexer.h"
#define RULE_BUFF_SIZE 200
#define SYM_BUFF_SIZE 30

void addRule(Rule* grammar, int index, char* ruleBuffer) {
	int blen = strlen(ruleBuffer);
	char symbolBuffer[SYM_BUFF_SIZE];
	sscanf(ruleBuffer, "%s", symbolBuffer);
	grammar[index].lhs = getTokenName(symbolBuffer, true);
	int bptr = strlen(symbolBuffer) + 1;
	SymList* prev = NULL;
	SymList* curr = NULL;
	while(bptr < blen) {
		curr = (SymList*) malloc(sizeof(SymList));
		sscanf(ruleBuffer + bptr, "%s", symbolBuffer);
		curr -> val = getTokenName(symbolBuffer, true);
		bptr += (int) strlen(symbolBuffer) + 1;
		curr -> next = NULL;
		if(prev)
			prev -> next = curr;
		else
			grammar[index].rhs = curr;
		prev = curr;
	}
	return;
}

Rule* readGrammar(char* grammar_path, int num_rules) {
	FILE* fptr = fopen(grammar_path, "r");
	Rule* grammar = (Rule*) malloc(sizeof(Rule) * num_rules);
	char ruleBuffer[RULE_BUFF_SIZE];
	for(int i = 0; i < num_rules; i++) {
		fgets(ruleBuffer, RULE_BUFF_SIZE, fptr);
		addRule(grammar, i, ruleBuffer);
	}
	fclose(fptr);
	return grammar;
}

void printGrammar(Rule* grammar, int num_rules) {
	for(int i = 0; i < num_rules; i++) {
		printf("%d: %s --> ", i+1, grammar[i].lhs);
		SymList* rptr = grammar[i].rhs;
		while(rptr) {
			printf("%s ", rptr -> val);
			rptr = rptr -> next;
		}
		printf("\n");
	}
	return;
}

int main(int argc, char** argv) {
	if(argc != 3) {
		printf("Usage: ./grammartest <path to grammar txt> <number of rules>\n");
		return 0;
	}
	char* grammar_path = argv[1];
	int num_rules = atoi(argv[2]);
	Rule* grammar = readGrammar(grammar_path, num_rules);
	printGrammar(grammar, num_rules);
	return 0;
}