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
    int minus;
    int nb;
}           t_flag;

void    free_string(char *str);
void    revstr(char **str);
char *ft_strdup(char *str);
int ft_strcmp(char *s1, char *s2);
int ft_strlen(char *str);
int ft_isdigit(char c);
int ft_pow(int n, int pow);
int len_int(int n);
int len_long(unsigned long long n);
char    *ft_itoa(int n);
int ft_atoi(char *str);
char *to_hex(unsigned long long n, char *base);
void    init_struct_flags(t_flag *flags);
void    print_str(char *str, t_flag *flags, int *ret, int minus);
char    *find_conv(int *i, const char *format, va_list *args, t_flag *flags);
void    find_flags(int *i, const char *format, t_flag *flags, va_list *args);
int    parse_string(va_list *args, const char *format, int *ret, t_flag *flags);
int ft_printf(const char *format, ...);

#endif