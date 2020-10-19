#ifndef GRAMMAR_H
#define GRAMMAR_H
#define SYMBOL_LEN 30

typedef struct SymList {
	char val[SYMBOL_LEN];
	struct SymList* next;
} SymList;

typedef struct Rule {
	char lhs[SYMBOL_LEN];
	SymList* rhs;
} Rule;

Rule* readGrammar(char* grammar_path, int num_rules);
void addRule(Rule* grammar, int index, char* ruleBuffer);
void printGrammar(Rule* grammar, int num_rules);

#endif