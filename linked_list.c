#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include <assert.h>

// Function to create a new ListNode
ListNode *createNode(const char *word) {
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    assert(newNode != NULL);  // Ensure memory allocation was successful
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->word, word);
    newNode->next = NULL;
    return newNode;
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
