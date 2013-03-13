#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

/* enum month  {January, February, March, April, May, June, July, August, September, October, November, December};*/

struct companys
{
  char name[30];
  char tax[7];
  char month_name[8];
  char date[17];
};
struct tmp							// whether it  violates conditions of the task?
{								
  char name[30];
};
// Function uses temporary structure to scan names before the string starting from the point, and then allocates memory
// for necessary number of names of type "struct companys" and rewrite data in allocated memory.
int scan_names(struct companys *company)
{
  int i,j;
  struct tmp *arr;
  arr=(struct tmp *)malloc(50 * sizeof(struct tmp) );
  for(i=0;i<50;i++)
  {
    scanf_s("%s", arr[i].name);
    fflush(stdin);
    if(arr[i].name[0] == '.')
    {
       i--;
       break;
    }
  }
  company=(struct companys *)malloc(i * sizeof(struct companys) );
  for(j=0;j<i;j++) 
  {
	  strcpy(company[j].name,arr[j].name);
  }
  free(arr);
  return i+1;
}

int scan_tax(struct companys *company, int n)
{ 
  int i,j;
  for(i=0;i<n;i++)
  {
    scanf_s("%s", company[i].tax);
    fflush(stdin);
  }
  return 0;
}

int scan_date(struct companys *company,int n)
{
  int i,j;
  for(i=0;i<n;i++)
  {
    scanf_s("%s", company[i].month_name);
    fflush(stdin);
  }
  for(i=0;i<n;i++)
  {
    scanf_s("%s", company[i].date);
    fflush(stdin);
  }
  return 0;  
}

int main()
{
  int j,i,n; 					// i,j - array steps, n - number of companys
  char month_name[8];	
  struct companys  *company,bf;				
  arr=(int *)calloc(5,sizeof(int));
  n=scan_names(company);
  scan_tax(company,n);
  scan_date(company,n);
  printf("Set date (month) to check companys with max debts");
  gets(month_name);
 
  return 0;
}

