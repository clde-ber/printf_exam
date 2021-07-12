#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_flag
{
    int set_prec;
    int prec;
    int set_width;
    int width;
}           t_flag;

int ft_isdigit(char c);
int ft_pow(int n, int pow);
int len_int(int n);
char    *ft_itoa(int n);
int ft_atoi(char *str);
char *ft_strdup(char *str);
int ft_strcmp(char *s1, char *s2);
int ft_strlen(char *str);

#endif