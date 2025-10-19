#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

int main(int argc, char *argv[]) {
   if(argc < 2){
        printf("ERROR: The program must read at least an argument.\n");
        return 0;
    }
    //Create new list and setup
    struct Linkedlist list;
    char* cur;
    for(int i = 1; i < argc; i++){
         cur = argv[i];
        if(findNode(list, cur) > -1){
            deleteNode(&list, cur);
            continue;
        }

        if(isupper(*cur)) insertAtBeginning(&list, cur);
        else insertAtTheEnd(&list, cur); 
    }

    printf("The list:- ");
    displayLinkedList(list);

    return 0;
}