#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
} TrieNode;

TrieNode *getNode(void);
void insert(TrieNode *root, const char *key);
void printWords(TrieNode *root, char *wordArray, int pos);
void predict(TrieNode *root, const char *prefix);
void freeTrie(TrieNode *root);

#endif
