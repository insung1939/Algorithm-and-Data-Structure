#include "trie.h"
#include <stdio.h>
#include <stdlib.h>

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
