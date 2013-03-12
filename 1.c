#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


struct companys
{
  char name[30];
  char tax[7];
  char month_name[8];
  char date[17];
};

int scan_names(struct companys);
int scan_tax(struct companys,int);
int scan_date(struct companys,int);

int main()
{
  int j,i,n,*arr,bf; 					// i,j - array steps, n - number of companys, bf - buffer var, arr - array containing max taxes
  char month_name[8];	
  struct companys  company[50];					// temporary irrational space usage
  arr=(int *)calloc(5,sizeof(int));
  n=scan_names(company);
  scan_tax(company,n);
  scan_date(company,n);
  printf("Set date (month) to check companys with max debts");
  gets("%s", month_name);
  bf=1000001;
  for(i=0;i<5;i++)						// searching for max taxes(rubbishj)
  {
    for(j=0;j<n;j++)
    {
      if( (strcmp(company[i].month_name,month_name)) == 0)
      {
	if( (arr[i]<company[j].tax-48) && (company[j].tax-48<bf) )
	{
	  arr[i]= company[j].tax-48;
	}
      }
    }
    bf=arr[i];
  }

  return 0;
}

int scan_names(struct companys company)
{
  int i;
  char *name;
  name=(char *)malloc(30)
  for(i=0;i<50;i++)
  {
    scanf_s("%s", company[i].name);
    if(name[0]!='.')
    {
      strcpy(company[i].name,name);
    }
    else 
    {
      free(name);
      break;
    }
    fflush(stdin);
  }
  return i+1;
}

int scan_tax(struct companys company, int n)
{ 
  int i;j
  for(i=0;i<n;i++)
  {
    fscanf("%d\n", company[i].tax);
    fflush(stdin);
  }
  return 0;
}

int scan_date(struct companys company,int n);
{
  int i;j
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
