#include "mylib.h"

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
