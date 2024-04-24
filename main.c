#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
} TrieNode;

TrieNode *getNode(void) {
    TrieNode *pNode = (TrieNode *)malloc(sizeof(TrieNode));
    if (!pNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    pNode->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        pNode->children[i] = NULL;
    }
    return pNode;
}

void insert(TrieNode *root, const char *key) {
    TrieNode *pCrawl = root;
    for (int level = 0; level < strlen(key); level++) {
        int index = key[level] - 'a';
        if (index < 0 || index >= ALPHABET_SIZE) {
            fprintf(stderr, "Invalid character '%c' in key \"%s\"\n", key[level], key);
            continue;
        }
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

void loadWordsFromFile(TrieNode *root, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open the file");
        exit(EXIT_FAILURE);
    }
    char word[100];
    while (fscanf(file, "%s", word) == 1) {
        insert(root, word);
    }
    fclose(file);
}

int main() {
    TrieNode *root = getNode();
    loadWordsFromFile(root, "dp-words.txt");

    char prefix[100];
    printf("Enter a prefix to predict words: ");
    scanf("%s", prefix);

    printf("Predictions for '%s':\n", prefix);
    predict(root, prefix);

    freeTrie(root);
    return 0;
}
