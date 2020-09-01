#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "trie.h"
#include "linkedList.h"

void readFileAndInsertTree(Trie *trie, char *path);
void statistics(clock_t t1, clock_t t2, char *timeSpentId, char *pathToSave);


int main(int numargs, char *arg[]) {
    if (numargs != 4) {
        printf ("Numero de argumentos errado...\n");
        printf ("Ex1: ./trie <path/to/text> -interactive\n");
        printf ("   *para o modo iterativo (-i/-iteractive)\n");
        printf ("Ex2: ./trie <path/to/text> -exp\n");
        printf ("   *para o modo autônomo\n");
        return EXIT_FAILURE;
    }
    if (strcmp (arg[2], "-iteractive") == 0  || strcmp (arg[2], "-i") == 0) {
        printf ("Você está no Modo ITERATIVO\n");
        char *path = arg[1];
        char *outputPath = arg[3];

        Trie* root = doTrienode('\0');
        clock_t timeBegin, timeEnd;
        timeBegin= clock();
        readFileAndInsertTree(root, path);
        timeEnd= clock();
        statistics(timeBegin, timeEnd, "Lendo os arquivos e inserir na Trie", outputPath);

        char inputUser[20];
        int input;

        while (true){
            printf( "Digite o prefixo desejado:\n");
            scanf("%s", inputUser);
            input = strcmp(inputUser, "0");
            char *bkpIn = inputUser;
            if (input == 0) {
                //liberando espaço de memória alocado
                freeMemoryTree(root);
                return EXIT_SUCCESS;
            }else if(input > 0) {
                timeBegin = clock();
                List * elements = makeList();
                searchPrefix(root, inputUser, elements);
                sortList(elements);
                reverseList(elements);
                printList(elements);
                dealocateMemory(elements);
                timeEnd = clock();
                char *msg = malloc(100);
                strcat(msg, "O prefixo '");
                strcat(msg, bkpIn);
                strcat(msg,"' gastou ");
                statistics(timeBegin, timeEnd, msg, outputPath);
            }else {
                printf("\nTente um sufixo, ou ZERO p/ sair.\n");
            }
        }
    }
    else if (strcmp (arg[2], "-exp") == 0  || strcmp (arg[2], "-e") == 0){
        printf ("Você está no Modo EXPERIMENTAL\n");

        char *path = arg[1];
        char *outputPath = arg[3];

        Trie* root = doTrienode('\0');
        clock_t timeBegin, timeEnd;
        timeBegin= clock();
        readFileAndInsertTree(root, path);
        timeEnd= clock();
        statistics(timeBegin, timeEnd, "Para ler o arquivo, tratar e inserir na arvore: ", outputPath);

        List * elements = makeList();
        int i;
        for (i = 0; i < ALPHABET_SIZE; i++) {
            char str[BUFSIZ];
            sprintf(str, "%c", i + 65);
            timeBegin= clock();
            searchPrefixOnTrie(root, str, elements);
            timeEnd= clock();
            statistics(timeBegin, timeEnd, str, outputPath);
        }
        printf("\n");
        for (i = 0; i < 26; i++) {
            char str[12];
            sprintf(str, "%c", i + 97);
            timeBegin= clock();
            searchPrefixOnTrie(root, str, elements);
            timeEnd= clock();
            statistics(timeBegin, timeEnd, str, outputPath);
        }
    }
    return EXIT_SUCCESS;
}

void readFileAndInsertTree(Trie *trie, char *path) {
    FILE *arq;
    char buffer[BUFSIZ] ;
    char delimiters[]="\"\\//[]}{* \n,.'-:;|#<>@#$%ˆ*&*()_@?!1234567890\t\r\n\v\f\0";
    arq = fopen(path, "r") ;
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

void statistics(clock_t t1, clock_t t2, char *timeSpentId, char *pathToSave) {
    clock_t t;
    t = t2 - t1;
    double timeTaken = ((double)t)/CLOCKS_PER_SEC;
    if (pathToSave){
        FILE *fPtr;
        fPtr = fopen(pathToSave, "a");
        if (fPtr==NULL){
            printf("\nNao sera possivel gravar as estatisticas\n");
            return;
        }
        fprintf(fPtr, "%s: %.4f segundos\n",timeSpentId, timeTaken);
        fclose(fPtr);

    }else{
        printf("%s: %.4f segundos\n",timeSpentId, timeTaken);
    }

}