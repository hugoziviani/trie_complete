#ifndef UNTITLED_TRIE_H
#define UNTITLED_TRIE_H
// The number of children for each node
// We will construct a LETTERS-ary tree and make it
// a Trie
// Since we have 26 english letters, we need
// 26 children per node
#define LETTERS 52
#define ASCINF 65
#define ASCSUP 90

typedef struct Trie Trie;
Trie* doTrienode(char data);
void freeMemoryTree(Trie* node);
Trie* insertOnTrie(Trie* root, char* word);
int searchOnTrie(Trie* root, const char* word);
int searchPrefixOnTrie(Trie* root, const char* prefix);


int check_divergence(Trie* root, char* word);
char* find_longest_prefix(Trie* root, char* word);
int nodeIsLeaf(Trie* root, char* word);
Trie* delete_trie(Trie* root, char* word);
void print_trie(Trie* root);
void print_search(Trie* root, char* word);


#endif //UNTITLED_TRIE_H
