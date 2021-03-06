#ifndef UNTITLED_TRIE_H
#define UNTITLED_TRIE_H

#define LETTERS 52
#define ASCINF 65
#define ASCSUP 90

#include "linkedList.h"
#include <string.h>
#include<stdio.h>
#include<stdlib.h>




typedef struct Trie Trie;
Trie* doTrienode(char data);
void freeMemoryTree(Trie* node);
Trie* insertOnTrie(Trie* root, char* word);
int searchOnTrie(Trie* root, const char* word);
int searchPrefixOnTrie(Trie *root, const char *prefix, List *occurrencesList);


int check_divergence(Trie* root, char* word);
char* find_longest_prefix(Trie* root, char* word);
int nodeIsLeaf(Trie* root, char* word);
Trie* delete_trie(Trie* root, char* word);
void printTrie(Trie* root);
void print_search(Trie* root, char* word);


#endif //UNTITLED_TRIE_H