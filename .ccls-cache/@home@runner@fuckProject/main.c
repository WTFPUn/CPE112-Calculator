#include <stdio.h>
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
  pwr() is power function 
  return powered value(base power by pwn)
*/
double pwr(int base,int pwn) {
  double out=1;
  for(int i = 0; i < pwn; i++) {
    out *= base;
  }
  return out;
}


/*
  Check the char value 
    If operator return priority
    If not operator(operant) return 0
*/
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

// Calculate postfix
int PostfixCalculation (char *syns) {
  // Initial value, and allocate stack
  // prod = product from num1 and num2 calculation(+, -, *, /, ^)
  int i = 0;
  void* num1;
  void* num2;
  double prod;
  void* ans;
  char *tok;
  STACK_T* numStack  = stackCreate(100000);

  // Set value in array split by space(" ")
  tok = strtok(syns, " ");

  // Loop until tok is not value
  while(tok != NULL) {

    // If it number push it to numStack
    if(isdigit(*tok)) {
      stackPush(numStack, allocateHeapDouble(atoi(tok)));
    }
      
    // If it operator Pop two value from numStack then keep them to num1 and num2 and calulate with current tok
    else{
      stackPop(numStack, &num1);
      stackPop(numStack, &num2);
      switch(*tok){
        case '^' :  prod = pwr(*( double *)num2, *( double *)num1); 
                    break;
        case '*' :  prod = *( double *)num2 * *( double *)num1; 
                    break;
        case '/' :  prod = *( double *)num2 / *( double *)num1; 
                    break;
        case '+' :  prod = *( double *)num2 + *( double *)num1; 
                    break;
        case '-' :  prod = *( double *)num2 - *( double *)num1; 
                    break;
      }
      // Push result back to numStack to calculate
      stackPush(numStack, allocateHeapDouble(prod));
    }
    tok = strtok(NULL, " ");
  }

  // Pop final reult from numStack to see Answer 
  stackPop(numStack,&ans);
  printf("Answer = %lf\n",*( double *)ans);

  // deallocate numStack
  stackDestroy(numStack);
  return 1;
}


int main(void) {
  do{
    //char END[]="END";
    // initial value
    char syntax[100000];
    char syntaxFormat[100000];
    int i = 0;
    int cnt = 0, beftmp=0;
    printf("Please Input your Infix : \n");
    fgets(syntax,10000,stdin);
    
    // If type END program will be Terminated
    // \n Because When we input with fgets it contain '\n' inside
    if(!strcmp(syntax,"END\n")){
      printf("Goodbye!");
      break;
    }
  
    // Initial length of syntax
    int len = strlen(syntax);  

    // Initial Stack to stack operator
    STACK_T* operatorStack  = stackCreate(100000);

    // loop until end of array
    while (i<len) {
      // initial temp to collect operator priority and check this char is operator
      int tmp = isOperator(syntax[i]);
      int j=1;
      // if it space then skip 
      if (syntax[i] == ' ') {
        i++;
        continue;
      }

      // if it '(' stack them
      if (syntax[i] == '(') {
        stackPush(operatorStack,allocateHeapChar(syntax[i]));
      }

      //  if it ')' add space and then pop operator in operatorStack to syntaxFormat until ')' was found 
      else if (syntax[i] == ')') {
        void *op;
        syntaxFormat[cnt++] = ' ';
        while(1) {
          stackPop(operatorStack, &op);        
          if (*( char*) op == '(') {
            break;
          }
          else {
            syntaxFormat[cnt++] = *( char*) op;
            syntaxFormat[cnt++] = ' ';
          }
        }
      }
      // if it operator add space first and then comparewith top of operator stack(before temp)
      else if (tmp) {        
        while(1){
          if (syntax[i+j] == ' ') {
            j++;
            continue;
          }
          if(isOperator(syntax[i+j])){
            printf("Invalid Expression");
            memset(syntax,'\0',len);
            memset(syntaxFormat,'\0',cnt);
            stackDestroy(operatorStack);
            i = len; // Break From Main Loop
            break;
          }
          else if(!isOperator(syntax[i+j])){
            break;
          }
        }
        syntaxFormat[cnt++] = ' ';

        // if temp priority > beforetemp push them! and set before temp priority to current temp priotrity
        if (tmp > beftmp) {
          stackPush(operatorStack,allocateHeapChar(syntax[i]));
          beftmp = tmp;
        }

        // if temp priority <= beforetemp  pop top operator in operatorStack to syntaxFormat(do it until top is > temp priority)  
        else {  
          void* op;
          while(stackTopPrio(operatorStack) >= tmp && stackTopPrio(operatorStack)!= 0) {  
            stackPop(operatorStack, &op);
            syntaxFormat[cnt++] = *( char*) op;
            syntaxFormat[cnt++] = ' ';
          }
          stackPush(operatorStack, allocateHeapChar(syntax[i]));
          beftmp = tmp;
        }    
      }

      // This case is char in this array is operant then put it in syntaxFormat
      else {
        syntaxFormat[cnt++] = syntax[i];
      }
      i++;
    }

    // Pop all the remaining operator in the stack and put them to syntaxFormat
    while(stackSize(operatorStack)){
      void* op;
      syntaxFormat[cnt++] = ' ';
      stackPop(operatorStack,&op);
      syntaxFormat[cnt++] = *( char*)op;
    }  

    // print it to test infix to postfix
    printf("%s\n", syntaxFormat);

    // send first adress of syntaxFormat to start calculate postfix and print result
    PostfixCalculation(&syntaxFormat[0]);

    // set all value in array to null, and deallocate stack
    memset(syntax,'\0',len);
    memset(syntaxFormat,'\0',cnt);
    stackDestroy(operatorStack);
  }while(1);
  return 0;
}
// 12 + 3 / 6 ^ 9 * 8 / 199
// 12 + 3 / ( 9 * 9 - 9) + 5
// 