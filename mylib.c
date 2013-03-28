#include "mylib.h"

char *myfgets(char *str, int num)
{
    if (!(fgets(str, num, stdin))) {
        return 0;
    } else {
        str[strlen(str) - 1] = '\0';
    }
    return str;
}

int input_number_in_range(int from, int to)
{
    int n;
    char *endptr;
    char input_buffer[128];
    int first = 1;
    do {
        if(!first){
            printf("Please enter number between %d and %d", from, to);
        }
        myfgets(input_buffer, 128);
        n = strtol(input_buffer, &endptr, 10);
        first = 0;
    } while( *endptr || n <= from || n >= to );
    return n;
}
