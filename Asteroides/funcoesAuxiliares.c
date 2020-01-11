#include <stdio.h>

void clean_stdin(void){ //Function that cleans the buffer for another input

    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}