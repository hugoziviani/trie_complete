//
// Created by Hugo Ziviani on 8/31/20.
//
#include "linkedList.h"

struct node {
    int occurrences;
    char* word;
    struct node * next;
};

struct list {
    Node * head;
};

Node *createNode(int occurrences, char *word);

Node *createNode(int occurrences, char *word) {
    Node * newNode = malloc(sizeof(Node));
    if (!newNode) {
        return NULL;
    }
    newNode->occurrences = occurrences;
    newNode->word = word;
    //TODO ALOCAR MEMORIA AQUI !!! se der pau
    newNode->next = NULL;
    return newNode;
}

List * makeList(){
    List * newList = malloc(sizeof(List));
    if (!newList) {
        return NULL;
    }
    newList->head = NULL;
    return newList;
}

void printList(List * list) {
    //reverseList(list);
    Node * current = list->head;
    if(list->head == NULL)
        return;

    for(; current != NULL; current = current->next) {
        printf("%s (%d)\n",current->word, current->occurrences);
    }
}

void push(List *list, int occurrence, char *word) {
    Node * current = NULL;
    if(list->head == NULL){
        list->head = createNode(occurrence, word);
    }
    else {
        current = list->head;
        while (current->next!=NULL){
            current = current->next;
        }
        current->next = createNode(occurrence, word);
    }
}

void delete(int data, List * list){
    Node * current = list->head;
    Node * previous = current;
    while(current != NULL){
        if(current->occurrences == data){
            previous->next = current->next;
            if(current == list->head)
                list->head = current->next;
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

void reverseList(List * list){
    Node * reversed = NULL;
    Node * current = list->head;
    Node * temp = NULL;
    while(current != NULL){
        temp = current;
        current = current->next;
        temp->next = reversed;
        reversed = temp;
    }
    list->head = reversed;
}

void dealocateMemory(List * list){
    Node * current = list->head;
    Node * next = current;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
    printf("\nMemória desalocada para lista de prefixos\n");
}

void sortList(List *list){
    int occurrencesMemory;
    char *word;
    Node *current;
    Node *nextNode;

    for(current = list->head; current != NULL; current = current->next){
        for(nextNode = current->next; nextNode != NULL; nextNode = nextNode->next){
            if(nextNode->occurrences < current->occurrences){
                occurrencesMemory = current->occurrences;
                word = current->word;
                //word = (char*) malloc(strlen(current->word) * sizeof(char));

                current->occurrences = nextNode->occurrences;
                current->word = nextNode->word;
                nextNode->occurrences = occurrencesMemory;
                nextNode->word = word;
            }
        }
    }
}
