#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node {
    char *data;
    struct Node *next;
};

struct Linkedlist {
    struct Node *head;
    struct Node *tail;
};

void insertAtBeginning(struct Linkedlist* LL, char ele[]){
    //create new node
    
    struct Node* new = malloc(sizeof(struct Node)); //Question: Why does this need to be pointer? What is malloc doing that the declaration is not
    new->data = ele;
    new->next = LL->head;

    LL->head = new; //Check This

    if(!(LL->tail)){
       LL->tail = new;
    }
}

void insertAtTheEnd(struct Linkedlist* LL, char ele[]){
    //create new node
    struct Node* new = malloc(sizeof(struct Node));
    new->data = ele;
    LL->tail->next = new;

    LL->tail = new;

    if(!(LL->head)){
        LL->head = new;
    }
}

void deleteNode(struct Linkedlist* LL, char ele[]){
    //Check if list is empty
    if(LL->head == LL->tail) return;
    
    struct Node* prev;
    struct Node* cur = LL->head;
    while(true){
        //If match delete
        if(cur != NULL && strcmp(cur->data, ele) == 0){
            //Head Case
            if(!prev){
                LL->head = cur->next;
            }
            else {
                prev->next = cur->next;
            }

            //tail case
            if(!cur->next){
                LL->tail = prev;
            }

            free(cur);
            return;
        }

        //Iterate Through List
        prev = cur;
        cur = cur->next;

        //At end break
        if(!cur) break;
    }

    printf("Could not find node %s\n", ele);
}

int findNode (struct Linkedlist* LL, char ele[]){
    //Check if list is empty
    if(LL->head == LL->tail) return -1;
    
    int count = 0;
    struct Node* cur = LL->head;
    while(true){
        if(!cur) break;

        if(strcmp(cur->data, ele) == 0){
            return count;
        }

        cur = cur->next;
        count++;
    }
    return -1;
}

void displayLinkedList(struct Linkedlist* LL){
    //Check if list is empty
    if(LL->head == LL->tail) return;

    struct Node* cur= LL->head;
    while(true){
        printf("%s", cur->data);
        if(LL->tail == cur) break;
        printf(", ");
        cur = cur->next;
    }
    printf("\n");
}

int main(int argc, char *argv[]){


    if(argc < 2){
        printf("ERROR: The program must read at least an argument.\n");
        return 0;
    }
    //Create new list and setup
    struct Linkedlist list;
    char* cur;
    for(int i = 1; i < argc; i++){
         cur = argv[i];
        if(findNode(&list, cur) > -1){
            deleteNode(&list, cur);
            continue;
        }

        if(isupper(*cur)) insertAtBeginning(&list, cur);
        else insertAtTheEnd(&list, cur); 
    }

    printf("The list:- ");
    displayLinkedList(&list);

    return 0;
}