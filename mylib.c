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
        if(n==0) {                                                      /*in case scan of paid tax*/
			break;
		}
        first = 0;
    } while( *endptr || n < from || n > to);
    return n;
}

date_t read_date(void)
{
    char input_buffer[128];
    int i, day, month, year;
    long int date = 0;
    char list_of_months[][4] =
        { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
        "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    printf("  1)Specify the year(in format YYYY): ");
    year = input_number_in_range(1970,2100);
    if(year == 0) {                                                     /*in case scan of unpaid tax*/
        return 0;
    }
    printf("  3)Specify the month: ");
    month = 0;
    while (!month) {
        myfgets(input_buffer, 12);
        for (i = 0; i < 12; i++) {
            if (!strncmp(input_buffer,list_of_months[i],3)) {
                month = (i + 1);
                break;
            } else {
                month = 0;
            }
        }
        if (month == 0) {
            printf("Invalid input, try again!\n");
        }
    }

    printf("  3)Specify the day: ");
    day = input_number_in_range(1,31);
    date = year * 10000 + month * 100 + day;

    return date;
}

int prnt_manual(int argc,char **argv){
    if(argc > 1 && !(strcmp(argv[1] ,"-h")) ) {
        printf("____________________________\n"
               "          Manual\n"
               "____________________________\n"
               "1)Set names of companies separated by \"Enter\"\n"
               "2)Set taxes of companies separated by \"Enter\""
               "3)Specify dates of payment and last dates( \"0\", if the tax has not been paid)\n"
               "  - Year(in YYYY format)\n"
               "  - Month (with hight letter)\n"
               "  - day\n"
               "4)Set date to check companies with max debts in the same way\n"
               "5)Program print companies(<5)with biggest taxes in alphabetical sequention\n");
    }
    return 0;
}
