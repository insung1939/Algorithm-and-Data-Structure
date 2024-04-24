#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

// Define the structure of a TrieNode
typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];  // Array of pointers to child nodes
    bool isEndOfWord;  // Flag to mark the end of a word
} TrieNode;

// Define the structure of a ListNode
typedef struct ListNode {
    char word[100];  // Word stored in the node
    struct ListNode *next;  // Pointer to the next node
} ListNode;

// Function to create a new TrieNode
TrieNode *getNode(void) {
    TrieNode *pNode = (TrieNode *)malloc(sizeof(TrieNode));  // Allocate memory for the node
    if (!pNode) {
        fprintf(stderr, "Memory allocation failed\n");  // Print error message if allocation fails
        exit(EXIT_FAILURE);  // Terminate program
    }
    pNode->isEndOfWord = false;  // Initialize isEndOfWord flag to false
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        pNode->children[i] = NULL;  // Initialize all child pointers to NULL
    }
    return pNode;  // Return the newly created node
}

// Function to create a new ListNode
ListNode *createNode(const char *word) {
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));  // Allocate memory for the node
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");  // Print error message if allocation fails
        exit(EXIT_FAILURE);  // Terminate program
    }
    strcpy(newNode->word, word);  // Copy the word to the node
    newNode->next = NULL;  // Initialize next pointer to NULL
    return newNode;  // Return the newly created node
}

// Function to insert a word into the Trie
void insert(TrieNode *root, const char *key) {
    TrieNode *pCrawl = root;
    for (int level = 0; level < strlen(key); level++) {
        int index = key[level] - 'a';  // Calculate the index of the current character
        if (index < 0 || index >= ALPHABET_SIZE) {
            fprintf(stderr, "Invalid character '%c' in key \"%s\"\n", key[level], key);
            continue;  // Skip invalid characters
        }
        if (!pCrawl->children[index])  // If the child node doesn't exist
            pCrawl->children[index] = getNode();  // Create a new node
        pCrawl = pCrawl->children[index];  // Move to the next node
    }
    pCrawl->isEndOfWord = true;  // Mark the end of the word
}

// Function to print all words in the Trie starting with a given prefix
void printWords(TrieNode *root, char *wordArray, int pos, ListNode *listHead) {
    if (root->isEndOfWord) {  // If the current node marks the end of a word
        wordArray[pos] = '\0';  // Terminate the word
        ListNode *newNode = createNode(wordArray);  // Create a new ListNode
        newNode->next = listHead->next;  // Insert the new node at the beginning of the list
        listHead->next = newNode;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {  // If the child node exists
            wordArray[pos] = i + 'a';  // Append the character to the word
            printWords(root->children[i], wordArray, pos + 1, listHead);  // Recursively print words
        }
    }
}

// Function to predict words starting with a given prefix
void predict(TrieNode *root, const char *prefix, ListNode *listHead) {
    TrieNode *pCrawl = root;
    for (int level = 0; level < strlen(prefix); level++) {
        int index = prefix[level] - 'a';  // Calculate the index of the current character
        if (!pCrawl->children[index]) {  // If no words match the prefix
            printf("No word found with the prefix '%s'\n", prefix);
            return;
        }
        pCrawl = pCrawl->children[index];  // Move to the next node
    }
    char wordArray[100];
    strcpy(wordArray, prefix);  // Copy the prefix to the word array
    printWords(pCrawl, wordArray, strlen(prefix), listHead);  // Print words starting with the prefix
}

// Function to free memory allocated for the Trie
void freeTrie(TrieNode *root) {
    if (!root) return;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            freeTrie(root->children[i]);  // Recursively free memory for child nodes
    free(root);  // Free memory for the current node
}

// Function to insert a word into the Trie, filtering out non-alphabet characters
void insertFiltered(TrieNode *root, const char *key) {
    TrieNode *pCrawl = root;
    for (int level = 0; level < strlen(key); level++) {
        if (key[level] >= 'a' && key[level] <= 'z') {  // Check if the character is a lowercase alphabet
            int index = key[level] - 'a';  // Calculate the index of the current character
            if (!pCrawl->children[index])  // If the child node doesn't exist
                pCrawl->children[index] = getNode();  // Create a new node
            pCrawl = pCrawl->children[index];  // Move to the next node
        }
    }
    pCrawl->isEndOfWord = true;  // Mark the end of the word
}

// Function to load words from a file into the Trie
void loadWordsFromFile(TrieNode *root, const char *filename) {
    FILE *file = fopen(filename, "r");  // Open the file in read mode
    if (!file) {
        perror("Failed to open the file");  // Print error message if file opening fails
        exit(EXIT_FAILURE);  // Terminate program
    }
    char word[100];
    while (fscanf(file, "%s", word) == 1) {  // Read words from the file
        insertFiltered(root, word);  // Insert each word into the Trie
    }
    fclose(file);  // Close the file
}

// Function to display the contents of a linked list
void displayList(ListNode *listHead) {
    ListNode *current = listHead->next;
    while (current) {
        printf("%s\n", current->word);
        current = current->next;
    }
}

int main() {
    TrieNode *root = getNode();  // Create the root node of the Trie
    loadWordsFromFile(root, "dp-words.txt");  // Load words from file into the Trie

    char prefix[100];
    printf("Enter a prefix to predict words: ");
    scanf("%s", prefix);

    if (strlen(prefix) <= 2) {
        printf("Prefix must be longer than 2 characters.\n");
        printf("[]");
        freeTrie(root);
        return 0;
    }

    ListNode *listHead = createNode("");  // Create a dummy head node for the linked list

    printf("Predictions for '%s':\n", prefix);
    predict(root, prefix, listHead);  // Predict words starting with the given prefix

    printf("\nReported Predictions:\n");
    displayList(listHead);  // Display the predicted words using the linked list

    // Free memory allocated for the Trie and linked list
    freeTrie(root);
    free(listHead);

    return 0;
}
