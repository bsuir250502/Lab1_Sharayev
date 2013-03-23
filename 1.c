#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#define N 5

typedef struct {
    char name[30];
    char tax[8];
    int last_date;
    int payment_date;
} companies;

// Function uses temporary structure to scan names before the string starting from the point, and then allocates memory
// for necessary number of names of type "struct companies" and rewrite data in allocated memory.
companies *scan_names(int max, int *n)
{
    int i, j;
    companies *comp;
    char arr[50][30];
    printf("Set names of companies:\n");
    for (i = 0; i < max; i++) {
        fgets(arr[i], 30, stdin);
        if (arr[i][0] == '.') 
        {
            break;
        }
    }
    *n = i;
    comp = (companies *) malloc(*n * sizeof(companies));

    for (i = 0; i < *n; i++) 
    {
        strncpy(comp[i].name, arr[i],30);
    }

    return comp;
}

int scan_tax(companies * comp, int n)
{
    int i, j;
    printf("Set taxes %d:\n", n);
    for (i = 0; i < n; i++) 
    {
        fgets(comp[i].tax, 8, stdin);
    }
    return 0;
}

int read_date(void)
{
    int i, month_number = 0;
    char date[12], list_of_months[][4] =
        { "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL",
"AUG", "SEP", "OCT", "NOV", "DEC" };
    while (!month_number) 
    {
        fgets(date, 12, stdin);
        for (i = 0; i < 12; i++)
        {
            if ((strstr(list_of_months[i], date)) != NULL) 
            {
                month_number = (i+1)*100;
                break;
            }
            else
            {
                month_number = 0;
            }
        }
        printf("Invalid input\n");
    }
	i=0;
	while(date[i] != ' ') i++;
	i++;

	month_number+=(date[i++]-48)*10;
	month_number+=(date[i++]-48);
	i++;
	month_number+=(date[i++]-48)*10000000;		// delicious solution
	month_number+=(date[i++]-48)*1000000;
	month_number+=(date[i++]-48)*100000;
	month_number+=(date[i++]-48)*10000;

    return month_number;
}


int scan_dates(companies * comp, int n)
{
    int i;
    for (i = 0; i < n; i++) 
    {
		printf("Set the latest date for tax payment for company \"%s\":\n", comp[i].name);
        comp[i].last_date = read_date();
    }
    for (i = 0; i < n; i++) 
    {
		printf("Set the actual date for tax payment for company \"%s\":\n", comp[i].name);
        comp[i].payment_date = read_date();
    }
    return 0;
}

int main()
{
    int j, i, n, month_number, better_numb;    // i,j - array steps, n - number of companies
    char month_name[10];
    companies *comp, bf;

    n = 50;

    comp = scan_names(n,&n);
    scan_tax(comp, n);
    scan_dates(comp, n);

    printf("Set date (month) to check companies with max debts:\n");
    month_number = read_date();

    for (i = 0; i < N; i++) 
    {
        for (j = i; j < n; j++)
        {
            better_numb = i;
            if ((comp[j].payment_date < month_number)
                && (comp[better_numb].tax < comp[j].tax))
            {
                better_numb = j;
            }
        }
        bf = comp[i];
        comp[i] = comp[better_numb];
        comp[better_numb] = bf;
    }
    for (i = 0; i < N; i++) {
        for (j = i; j < N; j++)
        {
            better_numb = i;
            if (comp[j].name[0] < comp[better_numb].name[0])
            {
                better_numb = j;
            }
        }
        bf = comp[i];
        comp[i] = comp[better_numb];
        comp[better_numb] = bf;
    }

    printf
        ("List of companies with the most outstanding tax before the %s:",
         month_name);
    for (i = 0; i < N; i++) {
        printf("%d. %s %4s\n", i, comp[i].name, comp[i].tax);
    }

    return 0;
}
