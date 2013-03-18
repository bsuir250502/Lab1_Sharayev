#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct 
{
  char name[30];
  char tax[8];
  char month_name[10];
  int  month_numb;
  char rep_month_name[10];
  int  rep_month_numb;
}companys;

 typedef struct   						// whether it  violates conditions of the task?
{								
  char name[30];
}tmp;
// Function uses temporary structure to scan names before the string starting from the point, and then allocates memory
// for necessary number of names of type "struct companys" and rewrite data in allocated memory.
companys* scan_names(int* n)
{
  int i,j;
  companys *comp;
  tmp *arr;
  arr=(tmp *)malloc(50 * sizeof(tmp) );
  printf("Set names of companys:\n");
  for(i=0;i<*n;i++) 
  {
  	fgets(arr[i].name,30,stdin);
  	fflush(stdin);
  	if(arr[i].name[0] == '.')
  	{
		break;
  	}
  }
  *n=i;
  comp=(companys *)malloc(*n * sizeof(companys) );
  
  for(i=0;i<*n;i++) 
  {
  	strcpy(comp[i].name,arr[i].name);
  }
  
  free(arr);
  return comp;
}

int scan_tax(companys *comp, int n)
{ 
  int i,j;
  printf("Set taxes %d:\n",n);
  for(i=0;i<n;i++)
  {
  	fgets(comp[i].tax, 8, stdin);
  	fflush(stdin);
  }
  return 0;
}

int valid_input(char* month_name)
{
  int i,month_number;
  char list_of_months[][10]=
  {"January","February","March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
  while(1)
  {
  	fgets(month_name,10,stdin);
  	fflush(stdin);
  	for(i=0;i<12;i++)
  	{
   		if ( (strcmp(list_of_months[i],month_name)) == 0 )
   		{
  			month_number=i;
  			break;
  			break;
  		}
  	}
  	printf("Invalid input\n");
  }
  return month_number;
}


int scan_dates(companys *comp,int n)
{
  int i;
  printf("Set the latest date for tax payment(month with a capital letter):\n");
  for(i=0;i<n;i++)
  {
  	comp[i].month_numb = valid_input(comp[i].month_name);	
  }
  printf("Set the actual date for tax payment (month with a capital letter):\n");
  for(i=0;i<n;i++)
  {
  	comp[i].rep_month_numb = valid_input(comp[i].month_name);
  }
  return 0;  
}

int main()
{
  int j,i,*n,month_number,better_numb; 					// i,j - array steps, n - number of companys
  char month_name[10];	
  companys  *comp,bf;	
  n=(int *)malloc(sizeof(int));
 
  *n=50;

  comp=scan_names( n );
  scan_tax( comp, *n );
  scan_dates( comp, *n );
  
  printf("Set date (month) to check companys with max debts");
  month_number = valid_input(month_name);
  
  for(i=0;i<5;i++)
  {
	for(j=i;j<*n;j++)
	{
		better_numb=i;
		if( (comp[j].rep_month_numb<month_number) && (comp[better_numb].tax<comp[j].tax) )
		{
			better_numb=j;
		}
	}
	bf=comp[i];
	comp[i]=comp[better_numb];
	comp[better_numb]=bf;
  }
  for(i=0;i<5;i++)
  {
	for(j=i;j<5;j++)
	{
		better_numb=i;
		if(comp[j].name[0]<comp[better_numb].name[0])
		{
			better_numb=j;
		}
	}
	bf=comp[i];
	comp[i]=comp[better_numb];
	comp[better_numb]=bf;
  }

  printf("List of companies with the most outstanding tax before the %s:", month_name);
  for(i=0;i<5;i++)
  {
	 printf("%d. %s %4s\n", i, comp[i].name, comp[i].tax);
  }

  return 0;
}
