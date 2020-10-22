#ifndef LEXER_H
#define LEXER_H

typedef struct TokenList {
  int line_no;
  char lexemes[10];
  char tokens[10];
  struct TokenList* next;
} TokenList;

int check_kword(char str[]);
TokenList* tokenizer(FILE *fptr);

#endif