#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "trie.h"

void readFileAndInsertTree(Trie *trie);
void printLetters();

int main() {
    Trie* root = doTrienode('\0');
    readFileAndInsertTree(root);
    int input;

    while (true){
        printf( "Enter a value :");
        scanf("%d", &input);
        if (input==0){
            print_search(root, "last");
            break;
        }
        if (input==1){
            char * pref;
            pref = find_longest_prefix(root, "b");
            printf("Encontrado: %s\n", pref);
            break;
        }
        if (input==3){
            searchOnTrie(root, "soon");
            break;
        }

    }
    //liberando espaço de memória alocado
    free_trienode(root);
    return 0;
}

void readFileAndInsertTree(Trie *trie) {
    FILE *arq;
    char buffer[BUFSIZ] ;
    char delimiters[]="\"\\//[]}{* \n,.'-:;|#<>@#$%ˆ*&*()_@?!1234567890\t\r\n\v\f\0";

    arq = fopen("../input/texto.txt", "r") ;
    int count_lines = 0;
    while(fgets(buffer, BUFSIZ, arq) != NULL && count_lines <10000) {
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
        printf("\v\vArquivo preenchido com: %i linhas\n",count_lines);
    }
    fclose(arq);
}

void printLetters(){
    int a, b;
    a = 90-65;
    for (int i = 65; i <= 90; ++i) {
        printf("%c:%i ", (char) i, i);
    }
    printf("\n");
    b = 122-97;
    for (int i = 97; i <= 122; ++i) {
        printf("%c:%i ", (char) i, i);
    }
    printf("\nTotal de letras: %i", a+b);
}