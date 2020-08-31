#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie {
    //cada nó tem um vetor dinamico com todas as letras do alfabeto escolhido
    //começando da raiz
    //se for nó-folha ele armazenará a palavra completa.
    char data;
    Trie* children[LETTERS];
    int isLeaf;
    int occurences;
    char* completeWord;
};

Trie* doTrienode(char data) {
    // cria o nó e aloca memória
    Trie* node = (Trie*) calloc (1, sizeof(Trie));
    for (int i=0; i < LETTERS; i++)
        node->children[i] = NULL;
    node->isLeaf = 0;
    node->data = data;
    node->occurences = 0;
    return node;
}

void freeMemoryTree(Trie* node) {
    for(int i=0; i < LETTERS; i++) {
        if (node->children[i] != NULL) {
            freeMemoryTree(node->children[i]);
        }
        else {
            continue;
        }
    }
    free(node->completeWord);
    free(node);
}

Trie* insertOnTrie(Trie* root, char* word) {
    // para inserir localiza a posição de cada letra no alfabeto
    Trie* temp = root;
    int letterNumber;
    int indexOnTree;

    for (int i=0; word[i] != '\0'; i++) {
        letterNumber = (int) word[i];
        if (letterNumber >= (int)'A' && letterNumber <= (int)'Z'){
            indexOnTree = (int) word[i] - 'A';
        } else{
            indexOnTree = (int) word[i] - 'a' + 26;
        }

        if (temp->children[indexOnTree] == NULL) {
            // se o index da primeira letra da palavra a ser inserida for nulo, é criado um novo nó com seus filhos para receberem os posteriores ponteiros
            temp->children[indexOnTree] = doTrienode(word[i]);
            temp->occurences += 1;
        }
        else {
            // faz nada, pois já tem o nó.
            temp->occurences += 1;
        }
        temp = temp->children[indexOnTree];
    }
    temp->isLeaf = 1;
    if(temp->occurences <= 0){
        temp->occurences +=1;
        temp->completeWord = (char*) malloc(strlen(word) * sizeof(char));
        strcpy(temp->completeWord, word);
    }else{
        temp->occurences +=1;
    }
    return root;
}

int searchOnTrie(Trie* root, const char* word)
{
    Trie* temp = root;
    int letterNumber;
    int indexOnTree;

    for(int i=0; word[i]!='\0'; i++)
    {
        letterNumber = (int) word[i];
        if (letterNumber>=ASCINF && letterNumber <=ASCSUP){
            indexOnTree = (int) word[i] - 'A';
        } else{
            indexOnTree = (int) word[i] - 'a';
        }
        if (temp->children[indexOnTree] == NULL){
            return 0;
        }
        temp = temp->children[indexOnTree];
    }
    if (temp != NULL && temp->isLeaf == 1){

        printf("Ocorrencias: %i\n", temp->occurences);
        printf("Palavra: %s\n", temp->completeWord);
        return 1;
    }

    return 0;
}

char* shiftPrefix(const char* prefix) {
    char *newPrefix;
    newPrefix = malloc(strlen(prefix)-1);
    for (int i = 1; prefix[i]!='\0'; i++) {
        newPrefix[i-1]=prefix[i];
    }
    return newPrefix;
}

int searchPrefixOnTrie(Trie* root, const char* prefix){
    Trie* tempRoot = root;
    int letterNumber;
    int indexOnTree;
    char *prefixTemp;

    for (int i=0; prefix[i]; i++) {

        letterNumber = (int) prefix[i];
        if (letterNumber>=ASCINF && letterNumber <=ASCSUP){
            indexOnTree = (int) prefix[i] - 'A';
        } else{
            indexOnTree = (int) prefix[i] - 'a' + 26;
        }
        if (tempRoot->children[indexOnTree]) {
            tempRoot = tempRoot->children[indexOnTree];
            printf("%c", tempRoot->data);

        }
    }
    printf("\nDATA: %s\n", tempRoot->completeWord);
       //printf("%c", tempRoot->data);

//    if(tempRoot != NULL && tempRoot->isLeaf){
//        printf("Ocorrencias: %i\n", tempRoot->occurences);
//        printf("Palavra: %s\n", tempRoot->completeWord);
//        return 1;
//    }
    return 0;
}


int check_divergence(Trie* root, char* word) {
    // Checks if there is branching at the last character of word
    // and returns the largest position in the word where branching occurs
    Trie* temp = root;
    int wordLength = strlen(word);
    if (wordLength == 0)
        return 0;
    int lastIdx = 0;
    int letterNumber;
    int indexOnTree;

    for (int i=0; i < wordLength; i++) {
        letterNumber = (int) word[i];
        if (letterNumber>=ASCINF && letterNumber <=ASCSUP){
            indexOnTree = (int) word[i] - 'A';
        } else{
            indexOnTree = (int) word[i] - 'a';
        }
        if (temp->children[indexOnTree]) {
            //Se existe um nó filho,
            // será checado se existem outros abaixo

            for (int j=0; j < LETTERS; j++) {
                if (temp->children[j]) {
                    // se entrar aqui achou mais um filho
                    lastIdx = i + 1;
                    printf("intro:%c",temp->data);


                }

            }
            // faz a busca para o proximo nó
            temp = temp->children[indexOnTree];
            printf("palavra: %c\n",temp->data);
            printf("palavra{}: %s\n",temp->completeWord);
        }
    }
    return lastIdx;
}

char* find_longest_prefix(Trie* root, char* word) {
    // busca pelo prefixo
    if (!word || word[0] == '\0')
        return NULL;
    int len;
    len = strlen(word);

    // We initially set the longest prefix as the word itself,
    // and try to back-tracking from the deepst position to
    // a point of divergence, if it exists
    char* longest_prefix = (char*) calloc (len + 1, sizeof(char));
    for (int i=0; word[i] != '\0'; i++)
        longest_prefix[i] = word[i];
    longest_prefix[len] = '\0';

    // If there is no branching from the root, this
    // means that we're matching the original string!
    // This is not what we want!
    int branch_idx  = check_divergence(root, longest_prefix) - 1;
    if (branch_idx >= 0) {
        // There is branching, We must update the position
        // to the longest match and update the longest prefix
        // by the branch index length
        longest_prefix[branch_idx] = '\0';
        longest_prefix = (char*) realloc (longest_prefix, (branch_idx + 1) * sizeof(char));
    }

    return longest_prefix;
}

int nodeIsLeaf(Trie* root, char* word) {
    Trie* temp = root;
    int letterNumber;
    int indexOnTree;
    for (int i=0; word[i]; i++) {

        letterNumber = (int) word[i];
        if (letterNumber>=ASCINF && letterNumber <=ASCSUP){
            indexOnTree = (int) word[i] - 'A';
        } else{
            indexOnTree = (int) word[i] - 'a' + 26;
        }
        if (temp->children[indexOnTree]) {
            temp = temp->children[indexOnTree];
        }
    }
    return temp->isLeaf;
}

Trie* delete_trie(Trie* root, char* word) {
    // Will try to delete the word sequence from the Trie only it
    // ends up in a leaf node
    if (!root)
        return NULL;
    if (!word || word[0] == '\0')
        return root;
    // If the node corresponding to the match is not a leaf node,
    // we stop
    if (!nodeIsLeaf(root, word)) {
        return root;
    }
    Trie* temp = root;
    // Find the longest prefix string that is not the current word
    char* longest_prefix = find_longest_prefix(root, word);
    //printf("Longest Prefix = %s\n", longest_prefix);
    if (longest_prefix[0] == '\0') {
        free(longest_prefix);
        return root;
    }
    // Keep track of position in the Trie
    int i;
    int letterNumber;
    int indexOnTree;
    for (i=0; longest_prefix[i] != '\0'; i++) {

        letterNumber = (int) longest_prefix[i];
        if (letterNumber>=ASCINF && letterNumber <=ASCSUP){
            indexOnTree = (int) longest_prefix[i] - 'A';
        } else{
            indexOnTree = (int) longest_prefix[i] - 'a';
        }

        if (temp->children[indexOnTree] != NULL) {
            // Keep moving to the deepest node in the common prefix
            temp = temp->children[indexOnTree];
        }
        else {
            // There is no such node. Simply return.
            free(longest_prefix);
            return root;
        }
    }
    // Now, we have reached the deepest common node between
    // the two strings. We need to delete the sequence
    // corresponding to word
    int len = strlen(word);
    for (; i < len; i++) {
        letterNumber = (int) word[i];
        if (letterNumber>=ASCINF && letterNumber <=ASCSUP){
            indexOnTree = (int) word[i] - 'A';
        } else{
            indexOnTree = (int) word[i] - 'a';
        }

        if (temp->children[indexOnTree]) {
            // Delete the remaining sequence
            Trie* rm_node = temp->children[indexOnTree];
            temp->children[indexOnTree] = NULL;
            freeMemoryTree(rm_node);
        }
    }
    free(longest_prefix);
    return root;
}

void print_trie(Trie* root) {
    // Prints the nodes of the trie
    if (!root)
        return;
    Trie* temp = root;
    printf("%c -> ", temp->data);
    for (int i=0; i < LETTERS; i++) {
        print_trie(temp->children[i]);
    }
}

void print_search(Trie* root, char* word) {
    printf("Searching for %s: ", word);
    if (searchOnTrie(root, word) == 0)
        printf("Not Found\n");
    else
        printf("Found!\n");
}
