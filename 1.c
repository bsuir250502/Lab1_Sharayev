#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#define Max_num_of_companies 50
#define Max_num_of_debtrs 5

typedef struct {
    char name[30];
    char tax[8];
    long int last_date;
    long int payment_date;
} companies_t;


int mysort(companies_t *, long int  ,int);
companies_t* scan_names(int *);
int scan_tax(companies_t *, int );
long int read_date(void);
int scan_dates(companies_t * comp, int n);

int main()
{
    int j, i, n = Max_num_of_companies, num_of_debtrs=0;
    long int date;
    companies_t *comp;
    comp = scan_names(&n);
    scan_tax(comp, n);
    scan_dates(comp, n);

    printf("Set date (month) to check companies with max debts:\n");
    date = read_date();
    num_of_debtrs=mysort(comp ,date , 8);
    printf
        ("List of %d companies with the most outstanding tax:\n",num_of_debtrs);
    for (i = 0; i < num_of_debtrs; i++) {
        printf("%d. %s %4s\n",i+1, comp[i].name, comp[i].tax);
    }
    
    free(comp);
    return 0;
}

char* myfgets(char *str, int num)
{
    if( !(fgets(str, num, stdin)) ){
    	return 0;
    }
    else {
    	str[strlen(str)-1]='\0';
    }
    return str;
}

int cmp_tax(const void* a, const void* b)
{
    companies_t *ca=(companies_t *)a,*cb=(companies_t *)b;
    return strcmp(cb->tax,ca->tax);
}

int cmp_name(const void* a, const void* b)
{
    companies_t *ca=(companies_t *)a,*cb=(companies_t *)b;
    return ca->name[0]-cb->name[0];
}

int mysort(companies_t *comp, long int date ,int n)
{
    int i,j = 0,num_of_debtrs;
    companies_t buffer;
    for(i = 0;i<n;i++){
        if((comp[i].payment_date == 0) || (comp[i].payment_date > comp[i].last_date && date<comp[i].payment_date)) {
            buffer=comp[i];
            comp[i]=comp[j];
            comp[j]=buffer;
            j++;
        }

    }
    num_of_debtrs=j;
    qsort(comp ,num_of_debtrs ,sizeof(companies_t) ,cmp_tax);
    if(num_of_debtrs>Max_num_of_debtrs) {
    num_of_debtrs=Max_num_of_debtrs;	
    }
    qsort(comp ,num_of_debtrs ,sizeof(companies_t) ,cmp_name);
    return num_of_debtrs;
}

companies_t* scan_names(int *n)
{
    int i, j;
    companies_t *comp;
    char arr[Max_num_of_companies][30];
    printf("Set names of companies:\n");
    for (i = 0; i < Max_num_of_companies; i++) {
        myfgets(arr[i], 30);
        if (arr[i][0] == '.') 
        {
            break;
        }
    }
    *n = i;
    comp = (companies_t *) malloc(*n * sizeof(companies_t));
    for (i = 0; i < *n; i++) {
        strncpy(comp[i].name, arr[i],30);
    }
    
    return comp;
}

int scan_tax(companies_t * comp, int n)
{
    int i, j;
    printf("Set taxes for company:\n");
    for (i = 0; i < n; i++) {
		printf("%s  - ",comp[i].name);
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

int scan_dates(companies_t * comp, int n)
{
    int i;
    for (i = 0; i < n; i++) {
	printf("Set the latest date for tax payment for company \"%s\":\n", comp[i].name);
        comp[i].last_date = read_date();
    }
    for (i = 0; i < n; i++) {
	printf("Set the actual date for tax payment for company \"%s\":\n", comp[i].name);
        comp[i].payment_date = read_date();
    }
    return 0;
}
