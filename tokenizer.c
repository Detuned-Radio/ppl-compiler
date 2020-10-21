#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct n{
  int line_no;
  char lexemes[10];
  char tokens[10];
  struct n* next;
}node;

int check_kword(char str[]){
  if(strlen(str)==1){
    if(str[0]=='+' || str[0]=='-' || str[0]=='/' || str[0]=='*' || str[0]==';' || str[0]==':' || str[0]=='[' || str[0]==']' || str[0]=='{' || str[0]=='}')
    return 1;
    return 0;
  }
  if(strcmp(str,"integer")==0)
  return 1;
  if(strcmp(str,"real")==0)
  return 1;
  if(strcmp(str,"boolean")==0)
  return 1;
  if(strcmp(str,"arrays")==0)
  return 1;
  if(strcmp(str,"jagged")==0)
  return 1;
  if(strcmp(str,"rect")==0)
  return 1;
  if(strcmp(str,"declare")==0)
  return 1;
  if(strcmp(str,"list")==0)
  return 1;
  if(strcmp(str,"of")==0)
  return 1;
  if(strcmp(str,"variables")==0)
  return 1;
  if(strcmp(str,"size")==0)
  return 1;
  if(strcmp(str,"values")==0)
  return 1;
  if(strcmp(str,"&&&")==0)
  return 1;
  if(strcmp(str,"|||")==0)
  return 1;
  if(strcmp(str,"..")==0)
  return 1;
  return 0;
}
node* tokenizer(FILE *fptr){
  //char temp[20];

  node* head;
  int l_no=1;
  head=(node *)malloc(sizeof(node));
  node *temp=head;
  while(1){
    fscanf(fptr,"%[^ \n]",temp->lexemes);
    fgetc(fptr);
    temp->line_no=l_no;
    if(temp->lexemes[0]==' ')
    continue;
    if(temp->lexemes[0]==';')
    l_no++;
    if(check_kword(temp->lexemes)){
      strcpy(temp->tokens,temp->lexemes);
    }
    else{
      if(temp->lexemes[0]>47 && temp->lexemes[0]<58)
      strcpy(temp->tokens,"constant");
      else
      strcpy(temp->tokens,"var");
    }
    if(feof(fptr)){
      return head;
    }
    temp->next=(node *)malloc(sizeof(node));
    temp=temp->next;

  }
}
  int main(){
    FILE* fptr=fopen("test.txt","r");
    node *head=tokenizer(fptr);
    fclose(fptr);
    int c=0;

    while(head!=NULL){
      printf("%d %s %s\n",head->line_no,head->lexemes,head->tokens);
      head=head->next;
      c++;
    }
    printf("%d",c);

    //printf("%s",cd);
  }
