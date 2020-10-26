#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexer.h"

char* getTokenName(char str[], bool checkNonTerminals) {
  if(checkNonTerminals) {
    if(strcmp(str, "program") == 0)
      return "program";
    if(strcmp(str, "programbody") == 0)
      return "programbody";
    if(strcmp(str, "declaration_list") == 0)
      return "declaration_list";
    if(strcmp(str, "assignment_list") == 0)
      return "assignment_list";
    if(strcmp(str, "declaration_stmt") == 0)
      return "declaration_stmt";
    if(strcmp(str, "assignment_stmt") == 0)
      return "assignment_stmt";
    if(strcmp(str, "prim_declaration_stmt") == 0)
      return "prim_declaration_stmt";
    if(strcmp(str, "rectarr_declaration_stmt") == 0)
      return "rectarr_declaration_stmt";
    if(strcmp(str, "jaggarr_declaration_stmt") == 0)
      return "jaggarr_declaration_stmt";
    if(strcmp(str, "prim_type") == 0)
      return "prim_type";
    if(strcmp(str, "id_list") == 0)
      return "id_list";
    if(strcmp(str, "range_list") == 0)
      return "range_list";
    if(strcmp(str, "range") == 0)
      return "range";
    if(strcmp(str, "range_val") == 0)
      return "range_val";
    if(strcmp(str, "jaggarr2d_declaration_stmt") == 0)
      return "jaggarr2d_declaration_stmt";
    if(strcmp(str, "jaggarr3d_declaration_stmt") == 0)
      return "jaggarr3d_declaration_stmt";
    if(strcmp(str, "jaggarr2d_init_list") == 0)
      return "jaggarr2d_init_list";
    if(strcmp(str, "jaggaarr2d_init_stmt") == 0)
      return "jaggaarr2d_init_stmt";
    if(strcmp(str, "jaggarr2d_val_list") == 0)
      return "jaggarr2d_val_list";
    if(strcmp(str, "jaggarr3d_init_list") == 0)
      return "jaggarr3d_init_list";
    if(strcmp(str, "jaggarr3d_init_stmt") == 0)
      return "jaggarr3d_init_stmt";
    if(strcmp(str, "jaggarr3d_row_list") == 0)
      return "jaggarr3d_row_list";
    if(strcmp(str, "jaggarr3d_val_list") == 0)
      return "jaggarr3d_val_list";
    if(strcmp(str, "expression") == 0)
      return "expression";
    if(strcmp(str, "bool_expression") == 0)
      return "bool_expression";
    if(strcmp(str, "term") == 0)
      return "term";
    if(strcmp(str, "factor") == 0)
      return "factor";
    if(strcmp(str, "index_list") == 0)
      return "index_list";
    if(strcmp(str, "index") == 0)
      return "index";
    if(strcmp(str, "bool_term") == 0)
      return "bool_term";
  }

  if(strlen(str)==1){
    if(str[0]=='+')
      return "TK_PLUS";
    if(str[0]=='-')
      return "TK_MINUS";
    if(str[0]=='/')
      return "TK_DIV";
    if(str[0]=='*')
      return "TK_STAR";
    if(str[0]==';')
      return "TK_SEMICOLON";
    if(str[0]==':')
      return "TK_COLON";
    if(str[0]=='(')
      return "BR_OP";
    if(str[0]==')')
      return "BR_CL";
    if(str[0]=='[')
      return "SQ_OP";
    if(str[0]==']')
      return "SQ_CL";
    if(str[0]=='{')
      return "CR_OP";
    if(str[0]=='}')
      return "CR_CL";
    if(str[0]=='=')
      return "TK_EQUALS";
  }

  if(strcmp(str,"program")==0)
    return "TK_PROGRAM"; 
  if(strcmp(str,"integer")==0)
    return "TK_INTEGER";
  if(strcmp(str,"real")==0)
    return "TK_REAL";
  if(strcmp(str,"boolean")==0)
    return "TK_BOOLEAN";
  if(strcmp(str,"array")==0)
    return "TK_ARRAY";
  if(strcmp(str,"jagged")==0)
    return "TK_JAGGED";
  if(strcmp(str,"declare")==0)
    return "TK_DECLARE";
  if(strcmp(str,"list")==0)
    return "TK_LIST";
  if(strcmp(str,"of")==0)
    return "TK_OF";
  if(strcmp(str,"variables")==0)
    return "TK_VARIABLES";
  if(strcmp(str,"size")==0)
    return "TK_SIZE";
  if(strcmp(str,"values")==0)
    return "TK_VALUES";

  if(strcmp(str,"&&&")==0)
    return "TK_AND";
  if(strcmp(str,"|||")==0)
    return "TK_OR";
  if(strcmp(str,"..")==0)
    return "TK_DOTDOT";

  if(strcmp(str,"R1")==0)
    return "TK_ROW"; 

  if(str[0] > 47 && str[0] < 58)
    return "TK_CONSTANT";

  return "TK_ID";
}


TokenList* tokeniseSourcecode(FILE *fptr){
  TokenList* head;
  int line_no=1;
  head = (TokenList*)malloc(sizeof(TokenList));
  TokenList *temp = head;
  while(1){
    fscanf(fptr, "%[^ \n]", temp -> lexeme);
    char break_char = fgetc(fptr);

    temp -> line_no = line_no;

    if(strlen(temp -> lexeme) == 0) {
      if(break_char == '\n')
        line_no++;
      continue;
    }

    temp -> token = getTokenName(temp -> lexeme, 0);

    if(feof(fptr))
      return head;
    
    temp -> next = (TokenList*) malloc(sizeof(TokenList));
    temp = temp -> next;

    if(break_char == '\n') 
      line_no++;
  }
}

int main(){
    FILE* fptr=fopen("test.txt","r");
    TokenList *head=tokeniseSourcecode(fptr);
    fclose(fptr);
    int c = 0;

    while(head != NULL){
      printf("%d %s %s\n", head -> line_no, head -> lexeme, head -> token);
      head = head -> next;
      c++;
    }
    printf("Length of token stream: %d\n",c);

    //printf("%s",cd);
}
