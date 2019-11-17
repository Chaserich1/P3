//Chase Richards
//CMPSCI 4280 P3
//Filename: semantics.cpp

#include "semantics.h"
#include <iostream>

const int maxStack = 100;
Token stack[maxStack];

int varCount = 0;
int startingScope = 0;

void stacker(){
   for(int i = 0; i <= maxStack; i++){
      stack[i].stringToken = "";
   }
}

void push(Token tkn){
   if(varCount >= maxStack){
      cout << "Error: Stack is at its max size" << endl;
      exit(EXIT_FAILURE);
   }else{
      for(int i = startingScope; i < varCount; i++){
         if(stack[i].stringToken == tkn.stringToken){
            cout << "Error: var already declared" << endl;
            exit(EXIT_FAILURE);
         }
      }
      stack[varCount] = tkn;
      varCount++;
   }
}

void pop(int startingScope){
   for(int i = varCount; i > startingScope; i--){
      varCount--;
      stack[i].stringToken == "";
   }
}

int find(Token tkn){
   for(int i = varCount; i >= startingScope; i--){
      cout << startingScope << " " << varCount << endl;
      if(stack[i].stringToken == tkn.stringToken){
         int TOS = varCount - 1 - i;
         return TOS;
      }
   }
   return -1;
}

bool duplicateCheck(Token tkn){
   for(int i = varCount - 1; i > -1; i--){
      if(stack[i].stringToken == tkn.stringToken){
         return true;
      }
   }
   return false;
}

void semantics(Node* node, int counter){
   if(node == nullptr){
      return;
   }
   
   if(node -> nonTerminal == "<program>"){
      int varsCounter = 0;
      if(node -> firstChild != nullptr){
         semantics(node -> firstChild, varsCounter);
      }
      if(node -> secondChild != nullptr){
         semantics(node -> secondChild, varsCounter);
      }
   }else if(node -> nonTerminal == "<block>"){
         int varsCounter = 0;
         startingScope = varCount;
         if(node -> firstChild != nullptr){
            semantics(node -> firstChild, varsCounter);
         }
         if(node -> secondChild != nullptr){
            semantics(node->secondChild, varsCounter);
         }
         
         pop(startingScope);
   }else if(node -> nonTerminal == "<vars>"){
      int TOS = find(node -> firstToken);
      startingScope = varCount;
      if(TOS == -1 || TOS > counter){
         push(node -> firstToken);
         counter++;
      }else if(TOS < counter){
         cout << "Error: token already declared in current scope" << endl;
         exit(EXIT_FAILURE);
      }
      if(node -> firstChild != nullptr){
         semantics(node -> firstChild, counter);
      }
   }else if(node -> nonTerminal == "<expr>"){
      if(node -> firstToken.identiToken == PlusTk){
         if(node -> firstChild != nullptr){
            semantics(node -> firstChild, counter);
         }
         if(node -> secondChild != nullptr){
            semantics(node -> secondChild, counter);
         }
      }else if(node -> firstChild != nullptr){
         semantics(node -> firstChild, counter);
      }
   }else if(node -> nonTerminal == "<A>"){
      if(node -> firstToken.identiToken == MinusTk){
         if(node -> firstChild != nullptr){
            semantics(node -> firstChild, counter);
         }
         if(node -> secondChild != nullptr){
            semantics(node -> secondChild, counter);
         }
      }else if(node -> firstChild != nullptr){
         semantics(node -> firstChild, counter);
      }
   }else if(node -> nonTerminal == "<N>"){
      if(node -> firstToken.identiToken == DivideTk || node -> firstToken.identiToken == MultiplicationTk){
         if(node -> firstChild != nullptr){
            semantics(node -> firstChild, counter);
         }
         if(node -> secondChild != nullptr){
            semantics(node -> secondChild, counter);
         }
      }else if(node -> firstChild != nullptr){
         semantics(node -> firstChild, counter);
      }
   }else if(node -> nonTerminal == "<in>"){
      if(!duplicateCheck(node -> firstToken)){
         cout << "Error: token not yet declared in current scope" << endl;
         exit(EXIT_FAILURE);
      }
   }else if(node -> nonTerminal == "<assign>"){
      if(!duplicateCheck(node -> firstToken)){
         cout << "Error: token not yet declared in current scope" << endl;
         exit(EXIT_FAILURE);
      }
      if(node -> firstChild != nullptr){
         semantics(node -> firstChild, counter);
      }
   }else{
      if(node -> firstChild != nullptr){
         semantics(node -> firstChild, counter);
      }
      if(node -> secondChild != nullptr){
         semantics(node -> secondChild, counter);
      }
      if(node -> thirdChild != nullptr){
         semantics(node -> thirdChild, counter);
      }
      if(node -> fourthChild != nullptr){
         semantics(node -> fourthChild, counter);
      }
   }
}
