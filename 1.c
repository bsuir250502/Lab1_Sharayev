#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#define N 5

typedef struct {
    char name[30];
    char tax[8];
    long int last_date;
    long int payment_date;
} companies;

char* myfgets(char *str, int num)
{
	if( !(fgets(str, num, stdin)) ){
		return 0;
	}
	else {
	str[strlen(str)-1]='\0';
	}
	fflush(stdin);
	return str;
}

int cmp_date(const void* a, const void* b)
{
    companies *ca=(companies *)a,*cb=(companies *)b;
    return (int *)ca->payment_date-(int *)cb->payment_date;
}

int cmp_name(const void* a, const void* b)
{
    companies *ca=(companies *)a,*cb=(companies *)b;
    return (int *)ca->name[0]-(int *)cb->name[0];
}

companies* scan_names(int max, int *n)
{
    int i, j;
    companies *comp;
    char arr[50][30];
    printf("Set names of companies:\n");
    for (i = 0; i < max; i++) {
        myfgets(arr[i], 30);
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
        myfgets(comp[i].tax, 8);
    }
    return 0;
}

long int read_date(void)
{
    int num, i;
	long int  date = 0;
    char month[10], list_of_months[][4] =
        { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
"Aug", "Sep", "Oct", "Nov", "Dec" };
	printf("  1)Specify the month: ");
    while (!date) 
    {
        myfgets(month, 12);
        for (i = 0; i < 12; i++)
        {
            if ((strstr(list_of_months[i], month)) != NULL) 
            {
                date = (i+1)*100;
                break;
            }
            else
            {
                date = 0;
            }
        }
		if (date == 0) {
        printf("Invalid input, try again!\n");
		}
    }
	printf("  2)Specify the day: ");
	scanf("%d", &num);
	date+=num;
	printf("  3)Specify the year(in format YYYY): ");
	scanf("%d", &num);
	date+=num*10000;

    return date;
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
    int j, i, n, better_numb;
    long int date;
    char month_name[10];
    companies *comp, bf;

    n = 50;

    comp = scan_names(n,&n);
    scan_tax(comp, n);
    scan_dates(comp, n);

    printf("Set date (month) to check companies with max debts:\n");
    date = read_date();

    for (i = 0; i < N; i++) 
    {
        for (j = i; j < n; j++)
        {
            better_numb = i;
            if ((comp[j].payment_date < date)
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
        ("List of companies with the most outstanding tax before the %ld:",
         date);
    for (i = 0; i < N; i++) {
        printf("%d. %s %4s\n", i+1, comp[i].name, comp[i].tax);
    }

    return 0;
}
