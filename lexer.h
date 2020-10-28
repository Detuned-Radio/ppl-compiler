#ifndef LEXER_H
#define LEXER_H
#define LEXEME_LEN 25

typedef struct TokenList {
  int line_no;
  char lexeme[LEXEME_LEN];
  char* token;	// pointer to string literal
  struct TokenList* next;
} TokenList;

char* getTokenName(char str[], bool checkNonTerminals, bool* isTerminal);
TokenList* tokeniseSourcecode(FILE *fptr);
void printTokenStream(TokenList* head);
#endif