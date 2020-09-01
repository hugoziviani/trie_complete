#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


#include "trie.h"
#include "linkedList.h"

void readFileAndInsertTree(Trie *trie);
void printLetters();
void statistics(clock_t t1, clock_t t2, char* timeSpentId);


int main() {
    Trie* root = doTrienode('\0');
    clock_t t1, t2;
    t1= clock();
    readFileAndInsertTree(root);
    t2= clock();
    statistics(t1, t2, "Reading file and inserting on Trie");
    char inputUser [100];
    int input;

    while (true){
        printf("\nEntre com o sufixo ou digite 0 para sair:\n");
        scanf("%s", inputUser);
        input = strcmp(inputUser, "0");

        if (input == 0){
            //liberando espaço de memória alocado
            freeMemoryTree(root);
            return EXIT_SUCCESS;
        } else {
            List * elements = makeList();
            searchPrefixOnTrie(root, inputUser, elements);
            sortList(elements);
            reverseList(elements);
            printList(elements);
            dealocateMemory(elements);
        }
    }
}

void readFileAndInsertTree(Trie *trie) {
    FILE *arq;
    char buffer[BUFSIZ] ;
    char delimiters[]="\"\\//[]}{* \n,.'-:;|#<>@#$%ˆ*&*()_@?!1234567890\t\r\n\v\f\0";

    arq = fopen("../input/texto.txt", "r") ;
    int count_lines = 0;
    while(fgets(buffer, BUFSIZ, arq) != NULL) {
        char * wordToken = strtok(buffer, delimiters);
        while(wordToken != NULL ) {
            //printf("%s|", wordToken);
            insertOnTrie(trie, (char *) wordToken);
            //Inserir aqui cada palavra na árvore
            wordToken = strtok(NULL, delimiters);
        }
        //printf("\n");
        count_lines ++;
    }
    if(count_lines>0){
        printf("Arvore preenchida preenchido com: %i linhas\n",count_lines);
    }
    fclose(arq);
}

void printLetters(){
    int a, b;
    int countA=0;
    int countB=0;
    a = 90-65;
    for (int i = 65; i <= 90; ++i) {
        printf("%c:%i ", (char) i, i);
        countA+=1;
    }
    printf("\n");
    b = 122-97;
    for (int i = 97; i <= 122; ++i) {
        printf("%c:%i ", (char) i, i);
        countB+=1;
    }
    printf("\nTotal de letras Maiusculas: %i",countA);
    printf("\nTotal de letras Minusculas: %i",countB);
}

void statistics(clock_t t1, clock_t t2, char* timeSpentId){
    clock_t t;
    t = t2 - t1;
    double timeTaken = ((double)t)/CLOCKS_PER_SEC;
    printf("%s: %.4f segundos\n",timeSpentId, timeTaken);
}
