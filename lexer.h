#ifndef LEXER_H
#define LEXER_H

typedef struct TokenList {
  int line_no;
  char lexemes[13];
  char tokens[10];
  struct TokenList* next;
} TokenList;

char* getTokenName(char str[]);
TokenList* tokenizer(FILE *fptr);

#endif