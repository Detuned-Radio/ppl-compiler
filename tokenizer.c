#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct n{
  int line_no;
  char lexemes[10];
  char tokens[10];
  struct n* next;
}node;

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
      printf("%d %s\n",head->line_no,head->lexemes);
      head=head->next;
      c++;
    }
    printf("%d",c);

    //printf("%s",cd);
  }
