//
// Created by Hugo Ziviani on 8/31/20.
//

#ifndef UNTITLED_LINKEDLIST_H
#define UNTITLED_LINKEDLIST_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node Node;

typedef struct list List;

List * makeList();
void push(List *list, int occurrence, char *word);
void delete(int data, List * list);
void printList(List * list);
void reverseList(List * list);
void dealocateMemory(List * list);

void sortList(List *list);

#endif //UNTITLED_LINKEDLIST_H
