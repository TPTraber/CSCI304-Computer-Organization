#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure
struct Node {
    char data[100];
    struct Node* next;
};

// Linked list structure
struct Linkedlist {
    struct Node* head;
};

// Function prototypes
void insertAtBeginning(struct Linkedlist* LL, char ele[]);
void insertAtTheEnd(struct Linkedlist* LL, char ele[]);
void deleteNode(struct Linkedlist* LL, char ele[]);
int findNode(struct Linkedlist LL, char ele[]);
void displayLinkedList(struct Linkedlist LL);

// Create a new node helper
struct Node* createNode(char ele[]) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->data, ele);
    newNode->next = NULL;
    return newNode;
}

// Insert at the beginning
void insertAtBeginning(struct Linkedlist* LL, char ele[]) {
    struct Node* newNode = createNode(ele);
    newNode->next = LL->head;
    LL->head = newNode;
}

// Insert at the end
void insertAtTheEnd(struct Linkedlist* LL, char ele[]) {
    struct Node* newNode = createNode(ele);
    if (LL->head == NULL) {
        LL->head = newNode;
        return;
    }
    struct Node* temp = LL->head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
}

// Delete a node by element
void deleteNode(struct Linkedlist* LL, char ele[]) {
    struct Node *temp = LL->head, *prev = NULL;
    while (temp != NULL && strcmp(temp->data, ele) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Element '%s' not found.\n", ele);
        return;
    }
    if (prev == NULL)
        LL->head = temp->next; // deleting first node
    else
        prev->next = temp->next;
    free(temp);
    printf("Deleted '%s' successfully.\n", ele);
}

// Find a node by element, returning its index (0-based)
int findNode(struct Linkedlist LL, char ele[]) {
    struct Node* temp = LL.head;
    int index = 0;
    while (temp != NULL) {
        if (strcmp(temp->data, ele) == 0)
            return index;
        temp = temp->next;
        index++;
    }
    return -1; // Not found
}

// Display the linked list
void displayLinkedList(struct Linkedlist LL) {
    struct Node* temp = LL.head;
    if (temp == NULL) {
        printf("[Empty List]\n");
        return;
    }
    printf("Linked List: ");
    while (temp != NULL) {
        printf("%s -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Test the functions
int main() {
    struct Linkedlist LL;
    LL.head = NULL;

    insertAtBeginning(&LL, "banana");
    insertAtBeginning(&LL, "apple");
    insertAtTheEnd(&LL, "cherry");
    insertAtTheEnd(&LL, "date");

    displayLinkedList(LL);

    printf("Position of 'cherry': %d\n", findNode(LL, "cherry"));
    printf("Position of 'mango': %d\n", findNode(LL, "mango"));

    deleteNode(&LL, "apple");
    deleteNode(&LL, "mango"); // not in list

    displayLinkedList(LL);

    return 0;
}
