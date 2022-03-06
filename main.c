#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"

char* allocateHeapChar (char value)
{
    char* data = (char*) calloc(1, sizeof(char));
    *data = value;
    return data;
}
int* allocateHeapInt (int value)
{
    int* data = (int*) calloc(1, sizeof(int));
    *data = value;
    return data;
}

double* allocateHeapDouble (double value)
{
    double* data = (double*) calloc(1, sizeof(double));
    *data = value;
    return data;
}
/*
  @return
*/
// int power(int base, int pwr){
//   int prod;
//   if
//   if(pwr < 0){
    
//   }
//   for(int i = 0 ; i<pwr ; i++){
    
//   }  
// }
int isOperator (char value) {
  switch(value){
    case '^' :  return 3 ;
    case '*' :  
    case '/' :  return 2;
    case '+' :  
    case '-' :  return 1;
    default : return 0;
    }
}

int PostfixCalculation (char *syns,int len) {
  // prod = product from num1 and num2 calculation(+, -, *, /, ^)
  int i = 0;
  void* num1;
  void* num2;
  double prod;
  void* ans;
  char *tok;
  
  tok = strtok(syns," ");
  
  STACK_T* numStack  = stackCreate(100000);
  while(tok != NULL) {
    if(isdigit(*tok)) {
      stackPush(numStack, allocateHeapInt(atoi(tok)));
    }
    else if(isalpha(*tok)){
      stackPop(numStack, &num1);
      stackPop(numStack, &num2);
      switch(*tok){
        case '^' :  prod = pow(*( int *)num1, *( int *)num2); break;
        case '*' :  prod = *( int *)num1 * *( int *)num2; break;
        case '/' :  prod = *( int *)num1 / *( int *)num2; break;
        case '+' :  prod = *( int *)num1 + *( int *)num2; break;
        case '-' :  prod = *( int *)num1 - *( int *)num2; break;
      }
      stackPush(numStack, allocateHeapDouble(prod));
    }
    tok = strtok(syns, " ");
  }
  stackPop(numStack,&ans);
  printf("%lf\n",*( double *)ans);
  return 1;
}

int main(void) {
  char syntax[100000];
  char syntaxFormat[100000];
  
  int i = 0;
  int cnt = 0, beftmp=0;
  fgets(syntax,10000,stdin);
  int len = strlen(syntax);
  
  STACK_T* operatorStack  = stackCreate(100000);
  while (i<len) {
    int tmp = isOperator(syntax[i]);    
    if (syntax[i++] == ' ') {
      continue;
    }
    
    if (syntax[i] == '(') {
      stackPush(operatorStack,allocateHeapChar(syntax[i]));
    }

    else if (syntax[i] == ')') {
      void *op;
      syntaxFormat[cnt++] = ' ';
      while(1) {
        
        stackPop(operatorStack,&op);
        
        if (*( char*) op == '(') {
          break;
        }
        else {
          syntaxFormat[cnt++] = *( char*) op;
          syntaxFormat[cnt++] = ' ';
        }
      }
    }
      
    else if (tmp) {
      syntaxFormat[cnt++] = ' ';
      if (tmp > beftmp) {
        printf("%c Pushed\n", syntax[i]);
        stackPush(operatorStack,allocateHeapChar(syntax[i]));
        beftmp = tmp;
      }
      else {  
        void* op;
        while(stackTopPrio(operatorStack) >= tmp && stackTopPrio(operatorStack)!= 0) {  
          stackPop(operatorStack, &op);
          printf("%c is popped!\n",*( char*) op);
          syntaxFormat[cnt++] = *( char*) op;
          syntaxFormat[cnt++] = ' ';
        }
        stackPush(operatorStack, allocateHeapChar(syntax[i]));
        printf("%c Pushed\n", syntax[i]);
        beftmp = tmp;
      }    
    }
      
    else {
      syntaxFormat[cnt++] = syntax[i];
    }
    i++;
  }

  while(stackSize(operatorStack)){
    void* op;
    syntaxFormat[cnt++] = ' ';
    stackPop(operatorStack,&op);
    syntaxFormat[cnt++] = *( char*) op;
  }
  printf("%s", syntaxFormat);
  return 0;
}
// 12 + 3 / 6 ^ 9 * 8 / 199
// 12 + 3 / ( 9 * 9 - 9) + 5
// 