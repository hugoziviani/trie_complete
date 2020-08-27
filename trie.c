#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie {
    // The Trie Node Structure
    // Each node has LETTERS children, starting from the root
    // and a flag to check if it's a leaf node
    char data; // Storing for printing purposes only
    Trie* children[LETTERS];
    int is_leaf;
};

Trie* make_trienode(char data) {
    // Allocate memory for a Trie
    Trie* node = (Trie*) calloc (1, sizeof(Trie));
    for (int i=0; i < LETTERS; i++)
        node->children[i] = NULL;
    node->is_leaf = 0;
    node->data = data;
    return node;
}

void free_trienode(Trie* node) {
    // Free the trienode sequence
    for(int i=0; i < LETTERS; i++) {
        if (node->children[i] != NULL) {
            free_trienode(node->children[i]);
        }
        else {
            continue;
        }
    }
    free(node);
}

Trie* insert_trie(Trie* root, char* word) {
    printf("inserting");
    // Inserts the word onto the Trie
    // ASSUMPTION: The word only has lower case characters
    Trie* temp = root;

    for (int i=0; word[i] != '\0'; i++) {
        // Get the relative position in the alphabet list
        int idx = (int) word[i] - 'a';
        if (temp->children[idx] == NULL) {
            // If the corresponding child doesn't exist,
            // simply create that child!
            temp->children[idx] = make_trienode(word[i]);
        }
        else {
            // Do nothing. The node already exists
        }
        // Go down a level, to the child referenced by idx
        // since we have a prefix match
        temp = temp->children[idx];
    }
    // At the end of the word, mark this node as the leaf node
    temp->is_leaf = 1;
    return root;
}

int search_trie(Trie* root, char* word)
{
    // Searches for word in the Trie
    Trie* temp = root;

    for(int i=0; word[i]!='\0'; i++)
    {
        int position = word[i] - 'a';
        if (temp->children[position] == NULL)
            return 0;
        temp = temp->children[position];
    }
    if (temp != NULL && temp->is_leaf == 1)
        return 1;
    return 0;
}

int check_divergence(Trie* root, char* word) {
    // Checks if there is branching at the last character of word
    // and returns the largest position in the word where branching occurs
    Trie* temp = root;
    int len = strlen(word);
    if (len == 0)
        return 0;
    // We will return the largest index where branching occurs
    int last_index = 0;
    for (int i=0; i < len; i++) {
        int position = word[i] - 'a';
        if (temp->children[position]) {
            // If a child exists at that position
            // we will check if there exists any other child
            // so that branching occurs
            for (int j=0; j < LETTERS; j++) {
                if (j != position && temp->children[j]) {
                    // We've found another child! This is a branch.
                    // Update the branch position
                    last_index = i + 1;
                    break;
                }
            }
            // Go to the next child in the sequence
            temp = temp->children[position];
        }
    }
    return last_index;
}

char* find_longest_prefix(Trie* root, char* word) {
    // Finds the longest common prefix substring of word
    // in the Trie
    if (!word || word[0] == '\0')
        return NULL;
    // Length of the longest prefix
    int len = strlen(word);

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

int is_leaf_node(Trie* root, char* word) {
    // Checks if the prefix match of word and root
    // is a leaf node
    Trie* temp = root;
    for (int i=0; word[i]; i++) {
        int position = (int) word[i] - 'a';
        if (temp->children[position]) {
            temp = temp->children[position];
        }
    }
    return temp->is_leaf;
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
    if (!is_leaf_node(root, word)) {
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
    for (i=0; longest_prefix[i] != '\0'; i++) {
        int position = (int) longest_prefix[i] - 'a';
        if (temp->children[position] != NULL) {
            // Keep moving to the deepest node in the common prefix
            temp = temp->children[position];
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
        int position = (int) word[i] - 'a';
        if (temp->children[position]) {
            // Delete the remaining sequence
            Trie* rm_node = temp->children[position];
            temp->children[position] = NULL;
            free_trienode(rm_node);
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
    if (search_trie(root, word) == 0)
        printf("Not Found\n");
    else
        printf("Found!\n");
}

int usage() {
    // Driver program for the Trie Data Structure Operations
    Trie* root = make_trienode('\0');
    root = insert_trie(root, "hello");
    root = insert_trie(root, "hi");
    root = insert_trie(root, "teabag");
    root = insert_trie(root, "teacan");
    print_search(root, "tea");
    print_search(root, "teabag");
    print_search(root, "teacan");
    print_search(root, "hi");
    print_search(root, "hey");
    print_search(root, "hello");
    print_trie(root);
    printf("\n");
    root = delete_trie(root, "hello");
    printf("After deleting 'hello'...\n");
    print_trie(root);
    printf("\n");
    root = delete_trie(root, "teacan");
    printf("After deleting 'teacan'...\n");
    print_trie(root);
    printf("\n");
    free_trienode(root);
    return 0;
}