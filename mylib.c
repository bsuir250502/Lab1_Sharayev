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

int input_number_in_range(int from, int to, int include_zero)
{
    int n;
    char *endptr;
    char input_buffer[128];
    int first = 1;
    do {
        if(!first){
            printf("Please enter number between %d and %d\n", from, to);
        }
        myfgets(input_buffer, 128);
        n = strtol(input_buffer, &endptr, 10);
        if(n==0 && include_zero) {                                                      /*in case scan of paid tax*/
			break;
		}
        first = 0;
    } while( *endptr || n < from || n > to);
    return n;
}

int prnt_manual(int argc,char **argv){
    if(argc > 1 && !(strcmp(argv[1] ,"-h")) ) {
        printf("____________________________\n"
               "          Manual\n"
               "____________________________\n"
               "1)Set names of companies separated by \"Enter\"\n"
               "2)Set taxes of companies separated by \"Enter\"\n"
               "3)Specify dates of payment and last dates( \"0\", if the tax has not been paid)\n"
               "  - Year(in YYYY format)\n"
               "  - Month (with hight letter)\n"
               "  - day\n"
               "4)Set date to check companies with max debts in the same way\n"
               "5)Program print companies(<5)with biggest taxes in alphabetical sequention\n");
    }
    return 0;
}
