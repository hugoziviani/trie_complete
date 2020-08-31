#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "trie.h"

void readFileAndInsertTree(Trie *trie);
void printLetters();
char* reverseCopy(char*, const char*, int num);

int main() {
    Trie* root = doTrienode('\0');
    readFileAndInsertTree(root);
    int input;

    while (true){
        printf( "Enter a value :");
        scanf("%d", &input);
        if (input==0){
            searchPrefixOnTrie(root, "sh");
            break;
        }
        if (input==1){
            char *pref = "Olaaaaaaaaaaaaaaa";
            char *dest = (char *) malloc(strlen(pref));
            searchPrefixOnTrie(root, "she");
            //printf("Encontrado: %s\n", pref);
            break;
        }
        if (input==3){
            searchOnTrie(root, "shelf");
            break;
        }
        if (input==4){
            printLetters();
        }
    }
    //liberando espaço de memória alocado
    freeMemoryTree(root);
    return 0;
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

char* reverseCopy(char* destination, const char* prefix, int num) {
    char *newPrefix;
    newPrefix = malloc(strlen(prefix)-1);
    for (int i = 1; prefix[i]!='\0'; i++) {
        newPrefix[i-1]=prefix[i];
    }
    return newPrefix;
}