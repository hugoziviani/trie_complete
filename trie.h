#ifndef TRIE_H
#define TRIE_H

#define LETTERS 52
#define ASCINF 65
#define ASCSUP 90

#include "linkedList.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Trie Trie;
Trie* doTrienode(char data);
void freeMemoryTree(Trie* node);
Trie* insertOnTrie(Trie* root, char* word);
int searchOnTrie(Trie* root, const char* word);
int searchPrefixOnTrie(Trie *root, char *prefix, List *occurrencesList);

#endif