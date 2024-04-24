#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TrieNode *getNode(void) {
    TrieNode *pNode = malloc(sizeof(TrieNode));
    if (pNode) {
        pNode->isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            pNode->children[i] = NULL;
        }
    }
    return pNode;
}

void insert(TrieNode *root, const char *key) {
    TrieNode *pCrawl = root;
    for (int level = 0; level < strlen(key); level++) {
        int index = key[level] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
        pCrawl = pCrawl->children[index];
    }
    pCrawl->isEndOfWord = true;
}

void printWords(TrieNode *root, char *wordArray, int pos) {
    if (root->isEndOfWord) {
        wordArray[pos] = '\0';
        printf("%s\n", wordArray);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            wordArray[pos] = i + 'a';
            printWords(root->children[i], wordArray, pos + 1);
        }
    }
}

void predict(TrieNode *root, const char *prefix) {
    TrieNode *pCrawl = root;
    for (int level = 0; level < strlen(prefix); level++) {
        int index = prefix[level] - 'a';
        if (!pCrawl->children[index]) {
            printf("No word found with the prefix '%s'\n", prefix);
            return;
        }
        pCrawl = pCrawl->children[index];
    }
    char wordArray[100];
    strcpy(wordArray, prefix);
    printWords(pCrawl, wordArray, strlen(prefix));
}

void freeTrie(TrieNode *root) {
    if (!root) return;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            freeTrie(root->children[i]);
    free(root);
}
