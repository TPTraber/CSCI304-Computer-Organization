#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void cipher(char* string){
    char* start = string;
    char* cur = string;
    char* end = string;
    
    while(*start != '\0'){
        //Skip through word to find end
        if (isalnum(*cur)) {
            cur++;
            continue;
        }

        //Mark end with pointer
        end = cur;

        //Iterate back printing out word untill start
        cur--;
        while(cur != start){
            printf("%c", toupper(*cur));
            cur--;
        }
        printf("%c", toupper(*cur));

        //Print non-alphanumeric characters till end or new word found
        cur = end;
        while(!isalnum(*cur) && *cur !=  '\0'){
            if(*cur == '_') printf(" ");
            else printf("%c", *cur);
            cur++;
        }

        //Set start of new word or end
        start = cur;
        
        //Go back to top of loop
    }
    printf("\n");
}

int main(void) {

    while(true){
        printf("Enter a message (use underscores for spaces, type 'quit' to exit):");
        char input[100];
        scanf("%s", input);

        if(strcmp(input, "quit") == 0) break;
        printf("\n");

        printf("Encoded message: ");
        cipher(input); 

        printf("\n");
        
    }
    return 0;
}