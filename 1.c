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

int cmp_tax_with_date_ch(const void* a, const void* b)
{
    companies *ca=(companies *)a,*cb=(companies *)b;
    if((ca->payment_date >= ca->last_date) || (ca->payment_date == 0)) return -1;
    if((cb->payment_date < cb->last_date) && (ca->payment_date != 0)) return 1;
    return strcmp(cb->tax,ca->tax);
}

int cmp_tax(const void* a, const void* b)
{
    companies *ca=(companies *)a,*cb=(companies *)b;
    return strcmp(cb->tax,ca->tax);
}

int cmp_name(const void* a, const void* b)
{
    companies *ca=(companies *)a,*cb=(companies *)b;
    return ca->name[0]-cb->name[0];
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
            if ((strstr(list_of_months[i], month)) != NULL) {
                date = (i+1)*100;
                break;
            }
            else {
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
    int j, i, n = 50, num_of_debtrs;
    long int date;
    companies *comp, bf;
    comp = scan_names(n,&n);
    scan_tax(comp, n);
    scan_dates(comp, n);

    printf("Set date (month) to check companies with max debts:\n");
    date = read_date();
    qsort(comp ,n ,sizeof(companies) ,cmp_tax_with_date_ch);
    for(i=0;i<8;i++)
    {
        if((comp[i].payment_date <= comp[i].last_date) || (comp[i].payment_date == 0)){
            num_of_debtrs=i;
            break;
        }
    }
    qsort(comp ,num_of_debtrs ,sizeof(companies) ,cmp_tax);
    if(num_of_debtrs>N) {
    num_of_debtrs=N;	
    }
    qsort(comp ,num_of_debtrs ,sizeof(companies) ,cmp_name);
    printf
        ("List of companies with the most outstanding tax before the %ld:",
         date);
    for (i = 0; i < N; i++) {
        printf("%d. %s %4s\n", i+1, comp[i].name, comp[i].tax);
    }

    return 0;
}
