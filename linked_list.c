#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

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

// Function to display the contents of a linked list
void displayList(ListNode *listHead) {
    ListNode *current = listHead->next;
    while (current) {
        printf("%s\n", current->word);
        current = current->next;
    }
}

// Function to free memory allocated for the linked list
void freeList(ListNode *listHead) {
    ListNode *current = listHead->next;
    while (current) {
        ListNode *temp = current;
        current = current->next;
        free(temp);  // Free memory for the current node
    }
    free(listHead);  // Free memory for the head node
}
