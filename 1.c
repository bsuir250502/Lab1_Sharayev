#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"
#define MAX_NUM_OF_COMPANIES 50
#define MAX_NUM_OF_DEBTRS 5
#define SIZE( x ) (sizeof(x)/sizeof(*x))

typedef long int date_t;
typedef char tax_t[20];

typedef struct {
    char name[30];
    tax_t tax;
    date_t last_date;
    date_t payment_date;
} company_t;

int cmp_tax(const void *a, const void *b)
{
    company_t *ca = (company_t *) a, *cb = (company_t *) b;
    return strcmp(cb->tax, ca->tax);
}

int cmp_name(const void *a, const void *b)
{
    company_t *ca = (company_t *) a, *cb = (company_t *) b;
    return strcmp(ca->name,cb->name);
}

int mysort(company_t *, long int, int);
company_t *scan_names(int *);
int scan_tax(company_t *, int);
long int read_date(void);
int scan_dates(company_t * comp, int n);

int main()
{
    int i, n = MAX_NUM_OF_COMPANIES, num_of_debtrs = 0;
    long int date;
    company_t *companies;
    companies = scan_names(&n);
    scan_tax(companies, n);
    scan_dates(companies, n);

    printf("Set date (month) to check companies with max debts:\n");
    date = read_date();
    num_of_debtrs = mysort(companies, date, n);
    printf
        ("List of %d companies with the most outstanding tax:\n",
         num_of_debtrs);
    for (i = 0; i < num_of_debtrs; i++) {
        printf("%d. %s %4s\n", i + 1, companies[i].name, companies[i].tax);
    }

    free(companies);
    return 0;
}

int mysort(company_t * comp, long int date, int n)
{
    int i, j = 0, num_of_debtrs;
    company_t buffer;
    for (i = 0; i < n; i++) {
        if ((comp[i].payment_date == 0)
            || (comp[i].payment_date > comp[i].last_date
                && date < comp[i].payment_date)) {
            buffer = comp[i];
            comp[i] = comp[j];
            comp[j] = buffer;
            j++;
        }

    }
    num_of_debtrs = j;
    qsort(comp, num_of_debtrs, sizeof(company_t), cmp_tax);
    if (num_of_debtrs > MAX_NUM_OF_DEBTRS) {
        num_of_debtrs = MAX_NUM_OF_DEBTRS;
    }
    qsort(comp, num_of_debtrs, sizeof(company_t), cmp_name);
    return num_of_debtrs;
}


company_t *scan_names(int *n)
{
    int i;
    company_t *comp;
    char arr[MAX_NUM_OF_COMPANIES][30];
    printf("Set names of companies:\n");
    for (i = 0; i < MAX_NUM_OF_COMPANIES; i++) {
        myfgets(arr[i], SIZE(arr[i]));
        if (arr[i][0] == '.') {
            break;
        }
    }
    *n = i;
    comp = (company_t *) malloc(*n * sizeof(company_t));
    for (i = 0; i < *n; i++) {
        strncpy(comp[i].name, arr[i], SIZE(arr[i]));
    }

    return comp;
}

int scan_tax(company_t * comp, int n)
{
    int i;
    printf("Set taxes for company:\n");
    for (i = 0; i < n; i++) {
        printf("%s  - ", comp[i].name);
        myfgets(comp[i].tax, 8);
    }
    return 0;
}

long int read_date(void)
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

int scan_dates(company_t * comp, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        printf("Set the latest date for tax payment for company \"%s\":\n",
               comp[i].name);
        comp[i].last_date = read_date();
    }
    for (i = 0; i < n; i++) {
        printf("Set the actual date for tax payment for company \"%s\":\n",
               comp[i].name);
        comp[i].payment_date = read_date();
    }
    return 0;
}
