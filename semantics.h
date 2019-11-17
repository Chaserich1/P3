//Chase Richards
//CMSPCI 4280 P3
//Filename: semantics.h

#ifndef SEMANTICS_H
#define SEMANTICS_H

#include "node.h"
#include "token.h"

void stacker();
void push(Token tkn);
void pop(int scope);
int search(Token tkn);
bool varCheck(Token tkn);
void semantics(Node* node, int counter);

#endif
