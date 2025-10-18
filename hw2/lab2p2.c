#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


/* ====== YOU MUST IMPLEMENT THESE ====== */
short get_binary_op(char *bin){
/* Convert a 16-char '0'/'1' string into a short (16-bit).
   Assumption: input is exactly 16 chars (no spaces). */
   short sum = 0;
   if (bin[0] == '1') sum -= pow(2,15);
   for(int i = 1; i<16; i++){
        if (bin[i] == '1') sum += pow(2,15-i);
   }
   return sum;
}
void convert_to_binary(short acc, char *bin){
/* Write the binary form of 'acc' as a 16-character string into 'bin'.
   'bin' must have space for 17 chars including '\0'. */
   short rem = acc;
   if (rem < 0) rem = rem * -1;
   printf("Remainder: %d\n", rem);
   printf("Actual: %d\n", acc);
   bin[16] = '\0';
   bin[0] = '0';
   for(int i = 1; i < 16; i++){
        if (rem - pow(2,15-i) >= 0){
            bin[i]='1';
            rem = rem - pow(2,15-i);
            
        }
        else bin[i] = '0';
    }
    //if neg convert to twos complement
    if(acc < 0){
        
        for(int i = 0; i<16; i++){
            if (bin[i] == '0') bin[i] = '1';
            else bin[i] = '0';
        }
        for(int i = 15; i>=0; i--){
            if (bin[i] == '1') bin[i] = '0';
            else {
                bin[i] = '1';
                break;
            } 
        }
    }
   
   
}
void print_memory(short *acc){
/* Print: MEMORY STORE: BB0 BB1
   where bytes are read from the address of *acc upward
   (lowest address first, highest address second), each as two hex digits.
   Example format: "MEMORY STORE: 0B 00"  */
/* HINT:
   unsigned char *p = (unsigned char *)acc;
   // Print p[0], then p[1], as two-digit hex:
   // printf("MEMORY STORE: %02x %02x\n", p[0], p[1]);
*/

    unsigned char *p = (unsigned char *)acc;
    // Print p[0], then p[1], as two-digit hex:
    printf("MEMORY STORE: %.2hx %.2hx\n", p[1], p[0]);
}


void print_results(short acc){
/* Print RESULT lines in all modes:
   - RESULT (B): use convert_to_binary() for a 16-bit, zero-padded string
   - RESULT (O): zero-padded octal for full 16-bit range
   - RESULT (H): 0x + 4 hex digits
   - RESULT (D): signed decimal from 'acc' */

   char bin[17];

   convert_to_binary(acc, bin);

   printf("RESULT (B): %s\n", bin);
   printf("RESULT (O): %.6ho\n", acc);
   printf("RESULT (H): 0x%.4hx\n", acc);
   printf("RESULT (D): %d\n", acc);
   
}


/* ====== INTERNAL: validate exactly 16 bits of '0'/'1' ====== */
static int is_valid_bin16(const char *s) {
    if (strlen(s) != 16) return 0;
    for (int i = 0; i < 16; ++i) {
        if (s[i] != '0' && s[i] != '1') return 0;
    }
    return 1;
}

/* ====== DO NOT CHANGE main() ====== */
int main(void) {
    char str_a[17], str_b[17];

    while (1) {
        printf("First binary is \n");
        if (scanf("%s", str_a) != 1) return 0;

        printf("Second binary is \n");
        if (scanf("%s", str_b) != 1) return 0;

        if (!is_valid_bin16(str_a) || !is_valid_bin16(str_b)) {
            printf("Inputs are not valid, please try again\n");
            continue;
        }
        break;
    }

    // Parse operands as 16-bit (student function)
    short a = get_binary_op(str_a);
    short b = get_binary_op(str_b);

    // Accumulator: mimic native short addition (wrap as needed)
    short acc = (short)(a + b);

    // Print all representations from the 16-bit accumulator
    print_results(acc);

    // Print actual byte layout of the accumulator in memory (machine-dependent)
    print_memory(&acc);

    return 0;
}
