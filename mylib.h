#ifndef _MYLIB_H_
#define _MYLIB_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long int date_t;

char* myfgets(char *, int);
int input_number_in_range(int from, int to);
long int read_date(void);
int prnt_manual(int ,char **);

#endif
