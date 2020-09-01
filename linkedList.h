#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node Node;
typedef struct list List;

List * makeList();
void push(List *list, int occurrence, char *word);
void printList(List * list);
void reverseList(List * list);
void dealocateMemory(List * list);

void sortList(List *list);

#endif