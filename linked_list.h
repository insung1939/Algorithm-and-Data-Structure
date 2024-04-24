#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// Define the structure of a ListNode
typedef struct ListNode {
    char word[100];  // Word stored in the node
    struct ListNode *next;  // Pointer to the next node
} ListNode;

// Function to create a new ListNode
ListNode *createNode(const char *word);

// Function to display the contents of a linked list
void displayList(ListNode *listHead);

// Function to free memory allocated for the linked list
void freeList(ListNode *listHead);

#endif
