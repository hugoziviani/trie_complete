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
    reverse(list);
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

void reverse(List * list){
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
    printf("Memória desalocada para lista de prefixos\n");
}


void sort(List *list){
    int occurrencesMemory;
    char *word;
    Node *temp1;
    Node *temp2;

    for(temp1 = list->head; temp1 != NULL; temp1 = temp1->next){
        for(temp2 = temp1->next; temp2 != NULL; temp2 = temp2->next){
            if(temp2->occurrences < temp1->occurrences){
                occurrencesMemory = temp1->occurrences;
                //word = (char*) malloc(strlen(temp1->word) * sizeof(char));
                word = temp1->word;
                temp1->occurrences = temp2->occurrences;
                temp2->occurrences = occurrencesMemory;
                temp2->word = word;
            }
        }
    }
}
