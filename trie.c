#include "trie.h"


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
    int i;
    for (i=0; i < LETTERS; i++)
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
    int i;
    for (i=0; word[i] != '\0'; i++) {
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

void searchUntilLeaf(Trie *root, List* occurrencesList) {
    if (!root)
        return;
    Trie* temp = root;
    if (temp->isLeaf && temp->completeWord != NULL){
        //printf("%s (%i)\n", temp->completeWord, temp->occurences);
        push(occurrencesList, temp->occurences, temp->completeWord);
    }
    int i;
    for (i=0; i < LETTERS; i++) {
        searchUntilLeaf(temp->children[i], occurrencesList);
    }

}

int searchPrefixOnTrie(Trie *root, char *prefix, List *occurrencesList) {
    Trie* tempRoot = root;
    int letterNumber;
    int indexOnTree;
    if(strcmp(prefix,"")==0)return 0;
    int i;
    for (i=0; prefix[i]!='\0'; i++) {
        letterNumber = (int) prefix[i];
        if (letterNumber >= ASCINF && letterNumber <= ASCSUP){
            indexOnTree = (int) prefix[i] - 'A';
        } else{
            indexOnTree = (int) prefix[i] - 'a' + 26;
        }
        if (tempRoot->children[indexOnTree] == NULL){
            return 0;
        }
        if (tempRoot->children[indexOnTree]) {
            tempRoot = tempRoot->children[indexOnTree];
        }
    }
    searchUntilLeaf(tempRoot, occurrencesList);
    return 0;
}
