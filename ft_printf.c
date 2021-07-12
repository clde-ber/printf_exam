#include "ft_printf.h"

void    revstr(char **str)
{
    char *tmp;
    int i;
    int len;

    i = 0;
    tmp = ft_strdup(*str);
    len = ft_strlen(*str);
    while (tmp[i] && len - 1 - i >= 0)
    {
        (*str)[len - 1 - i] = tmp[i];
        i++;
    }
}

char *ft_strdup(char *str)
{
    char *tmp;
    int i;

    i = 0;
    tmp = malloc(sizeof(char) * (ft_strlen(str) + 1));
    if (!(tmp))
        return (0);
    while (str[i])
    {
        tmp[i] = str[i];
        i++;
    }
    tmp[i] = '\0';
    return (tmp);
}

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    if (!s1 || !s2)
        return (0);
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int ft_isdigit(char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

int ft_pow(int n, int pow)
{
    int res;
    int i;

    res = 1;
    i = 0;
    while (i < pow)
    {
        res = res * n;
        i++;
    }
    return (res);
}

int len_int(int n)
{
    int i;

    i = 0;
    if (n == -2147483648)
        return (11);
    if (n < 0)
        n = -n;
    while (n > 9)
    {
        n = n / 10;
        i++;
    }
    return (i);
}

int len_long(unsigned long long n)
{
    int i;

    i = 0;
    while (n > 9)
    {
        n = n / 10;
        i++;
    }
    return (i);
}

char    *ft_itoa(int n)
{
    int i;
    int neg;
    int count;
    int res;
    char *str;

    i = 0;
    neg = 0;
    count = ft_pow(10, len_int(n));
    if (n < 0)
        str = malloc(sizeof(char) * (len_int(n) + 2));
    else
        str = malloc(sizeof(char) * (len_int(n) + 1));
    if (!(str))
        return (0);
    res = n;
    if (res == -2147483648)
        return (ft_strdup("-2147483648"));
    if (n < 0)
    {
        i++;
        neg = 1;
        n = -n;
        res = n;
    }
    while (res % count)
    {
        str[i] = res / count + '0';
        res = n % count;
        count = count / 10;
        i++;
    }
    str[i] = res / count + '0';
    str[i + 1] = '\0';
    if (neg == 1)
        str[0] = '-';
    return (str);
}

int ft_atoi(char *str)
{
    int i;
    int nb;
    int neg;

    i = 0;
    nb = 0;
    while (!ft_isdigit(str[i]) && str[i] != '+' && str[i] != '-')
        i++;
    if (ft_strcmp(str, "-2147483648") == 0)
        return (-2147483648);
    if (str[i] == '+')
        i++;
    if (str[i] == '-')
    {
        i++;
        neg = 1;
    }
    nb = str[i] - '0';
    i++;
    while (i < ft_strlen(str) && ft_isdigit(str[i]))
    {
        nb = nb * 10 + str[i] - '0';
        i++;
    }
    if (neg == 1)
        nb = -nb;
    return (nb);
}

char *to_hex(unsigned long long n, char *base)
{
    int len;
    unsigned long long res;
    int count;
    int i;
    int k;
    char *str;

    i = 0;
    len = ft_strlen(base);
    count = ft_pow(10, len_long(n));
    res = n;
    k = n;
    str = malloc(sizeof(char) * (len_long(n) + 1));
    if (!(str))
        return (0);
    while (n > 9)
    {
        str[i] = base[n % len];
        n = n / len;
        i++;
    }
    str[i] = base[n % len];
    str[i + 1] = '\0';
    revstr(&str);
    return (str);
}

void    init_struct_flags(t_flag *flags)
{
    flags->set_prec = 0;
    flags->prec = 0;
    flags->set_width = 0;
    flags->width = 0;
}

void    print_str(char *str, t_flag *flags)
{
    int len;
    int i;

    len = 0;
    i = 0;
    if (flags->set_prec == 1)
        len = flags->prec;
    else
        len = ft_strlen(str);
    while (i < flags->width - flags->prec && flags->width > flags->prec)
    {
        write(1, " ", 1);
        i++;
    }
    i = 0;
    while (i < flags->prec - ft_strlen(str) && flags->prec > ft_strlen(str))
    {
        write(1, "0", 1);
        i++;
    }
    i = 0;
    while (i < len)
    {
        write(1, &str[i], 1);
        i++;
    }
}

char    *find_conv(int *i, const char *format, va_list *args, t_flag *flags)
{
    char *ret;

    ret = NULL;
    if (format[*i] == 'd')
        ret = ft_itoa(va_arg(*args, int));
    if (format[*i] == 's')
        ret = ft_strdup(va_arg(*args, char *));
    if (format[*i] == 'x')
        ret = to_hex(va_arg(*args, unsigned long long), "0123456789abcdef");
    *i = ft_strlen(ret);
    return (ret);
}

void    find_flags(int *i, const char *format, va_list *args, t_flag *flags)
{
    if (ft_isdigit(format[*i]))
    {
        flags->set_width = 1;
        flags->width = ft_atoi((char *)&format[*i]);
    }
    while (ft_isdigit(format[*i]))
        (*i)++;
    if (format[*i] == '.')
    {
        flags->set_prec = 1;
        flags->prec = ft_atoi((char *)&format[++(*i)]);
    }
    while (ft_isdigit(format[*i]))
        (*i)++;
}

void    parse_string(va_list *args, const char *format, int *ret, t_flag *flags)
{
    int i;
    char *str;

    i = 0;
    str = NULL;
    while (format[i] != '%' || (format[i] == '%' && format[i + 1] == '%'))
        i++;
    *ret = ++i;
    find_flags(&i, format, args, flags);
    str = find_conv(&i, format, args, flags);
    print_str(str, flags);
}

int ft_printf(const char *format, ...)
{
    int ret;
    va_list args;
    t_flag flags;

    ret = 0;
    init_struct_flags(&flags);
    va_start(args, format);
    parse_string(&args, format, &ret, &flags);
    va_end(args);
    return (0);
}
/*
int main(void)
{
    printf("str %s\n", ft_itoa(-12345));
    printf("%d\n", ft_atoi("-12345"));
    printf("str %s\n", ft_itoa(-2147483648));
    printf("%d\n", ft_atoi("-2147483648"));
    printf("str %s\n", ft_itoa(2147483647));
    printf("%d\n", ft_atoi("2147483647"));
    printf("hex %s\n", to_hex(2147483647, "0123456789abcdef"));
    printf("hex %s\n", to_hex(1234, "0123456789abcdef"));
    printf("hex %s\n", to_hex(17, "0123456789abcdef"));
    ft_printf("%05.02d\n", 12345);
    return (0);
}
*/