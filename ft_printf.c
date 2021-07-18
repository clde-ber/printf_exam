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
    free_string(tmp);
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

int ft_isspace(char c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || \
    c == '\f')
        return (1);
    return (0);
}

char    *ft_itoa(int n)
{
    int i;
    int neg;
    int count;
    int res;
    char *str;
    int len;

    i = 0;
    neg = 0;
    count = ft_pow(10, len_int(n));
    len = (n < 0) ? len_int(n) + 2 : len_int(n) + 1;
    str = malloc(sizeof(char) * (len + 1));
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
    while (i < len - 1)
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
    str = malloc(sizeof(char) * (len_long(n) + 2));
    if (!(str))
        return (0);
    while (n / len)
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
    flags->minus = 0;
    flags->nb = 0;
}

void    update_flags_null(t_flag *flags, char *str, int len)
{
    int limit;

    limit = ft_strlen(str);
    if (flags->set_prec)
    {
        if (flags->prec >= len)
            flags->prec = 0;
        else
        {
            str[0] = '\0';
            flags->prec = 0;
        }
    }
    if (flags->prec < 0)
        flags->prec = 0;
    if (flags->set_width)
    {
        if (flags->width > ft_strlen(str))
            flags->width = flags->width - flags->prec - ft_strlen(str);
        else
            flags->width = 0;
    }
}

void    update_flags_nb(t_flag *flags, char *str, int len)
{
    int limit;

    limit = (flags->minus) ? ft_strlen(str) - 1 : ft_strlen(str);
    if (flags->set_prec)
    {
        if (flags->prec > len)
            flags->prec = flags->prec - limit;
        else
        {
            str[flags->prec] = '\0';
            flags->prec = 0;
        }
    }
    if (flags->prec < 0)
        flags->prec = 0;
    if (flags->set_width)
    {
        if (flags->width > ft_strlen(str))
            flags->width = flags->width - flags->prec - ft_strlen(str);
        else
            flags->width = 0;
    }
}

void    update_flags_str(t_flag *flags, char *str, int len)
{
    int limit;

    limit = ft_strlen(str);
    if (flags->set_prec)
    {
        if (flags->prec > len)
            flags->prec = flags->prec - limit;
        else
        {
            str[flags->prec] = '\0';
            flags->prec = 0;
        }
    }
    if (flags->prec < 0)
        flags->prec = 0;
    if (!flags->set_width || (flags->set_width && flags->width < ft_strlen(str)))
        flags->prec = 0;
    if (flags->set_width)
    {
        if (flags->width >= ft_strlen(str))
            flags->width = flags->width - flags->prec - ft_strlen(str);
        else
            flags->width = 0;
    }
}

void    update_flags(t_flag *flags, char *str)
{
    if (flags->nb)
        update_flags_nb(flags, str, 0);
    else if (!(ft_strcmp(str, "(null)") == 0 || \
    ft_strcmp(str, "") == 0))
        update_flags_str(flags, str, ft_strlen(str));
    else
        update_flags_null(flags, str, ft_strlen(str));
}

void    print_str(char *str, t_flag *flags, int *ret, int minus)
{
    int len;
    int i;
    int min;
    int cmp;

    len = 0;
    i = 0;
    min = 0;
    cmp = 0;
    update_flags(flags, str);
    while (i < flags->width)
    {
        write(1, " ", 1);
        i++;
    }
    if (flags->minus == 1)
    {
        write(1, &str[0], 1);
        min = 1;
    }
    *ret += i;
    i = 0;
    while (i < flags->prec)
    {
        if (flags->nb)
            write(1, "0", 1);
        else
            write(1, " ", 1);
        i++;
    }
    *ret += i;
    i = 0;
    while (str[i + min])
    {
        write(1, &str[i + min], 1);
        i++;
    }
    *ret = *ret + i + min;
}

char    *find_conv(int *i, const char *format, va_list *args, t_flag *flags)
{
    char *ret;
    char   *tmp;
    int     is_neg;

    ret = NULL;
    tmp = NULL;
    if (format[*i] == 'd')
    {
        is_neg = va_arg(*args, int);
        if (is_neg < 0)
            flags->minus = 1;
        flags->nb = 1;
        ret = ft_itoa(is_neg);
    }
    if (format[*i] == 's')
    {
        if (!(tmp = va_arg(*args, char *)))
            ret = ft_strdup("(null)");
        else
            ret = ft_strdup(tmp);
    }
    if (format[*i] == 'x')
    {
        flags->nb = 1;
        ret = to_hex(va_arg(*args, unsigned long long), "0123456789abcdef");
    }
    (*i)++;
    return (ret);
}

void    find_flags(int *i, const char *format, t_flag *flags, va_list *args)
{
    if (ft_isdigit(format[*i]) || format[*i] == '+' || format[*i] == '-')
    {
        flags->set_width = 1;
        flags->width = ft_atoi((char *)&format[*i]);
        if (format[*i] == '+' || format[*i] == '-')
            (*i)++;
        while (ft_isdigit(format[*i]))
            (*i)++;
    }
    else if (format[*i] == '*')
    {
        flags->set_width = 1;
        flags->width = va_arg(*args, int);
        (*i)++;
    }
    if (format[*i] == '.')
    {
        flags->set_prec = 1;
        if (ft_isdigit(format[++(*i)]))
            flags->prec = ft_atoi((char *)&format[*i]);
        if (format[*i] == '+' || format[*i] == '-')
            (*i)++;
        while (ft_isdigit(format[*i]))
            (*i)++;
    }
    if (format[*i] == '*')
    {
        flags->prec = va_arg(*args, int);
        (*i)++;
    }
}

void    free_string(char *str)
{
    free(str);
    str = NULL;
}

int    parse_string(va_list *args, const char *format, int *ret, t_flag *flags)
{
    int i;
    char *str;

    i = 0;
    str = NULL;
    init_struct_flags(flags);
    if (format[0] == '\0')
        return (0);
    while (format[i] && (format[i] != '%' || (format[i] == '%' && format[i + 1] == '%')))
    {
        write(1, &format[i], 1);
        i++;
    }
    *ret += i;
    if (format[i] == '\0')
        return (0); 
    i++;
    find_flags(&i, format, flags, args);
    str = find_conv(&i, format, args, flags);
    if (!(str))
        return (-1);
    print_str(str, flags, ret, flags->minus);
    free_string(str);
    if (i < ft_strlen((char *)format))
        parse_string(args, &format[i], ret, flags);
    return (0);
}

int ft_printf(const char *format, ...)
{
    int ret;
    va_list args;
    t_flag flags;

    ret = 0;
    init_struct_flags(&flags);
    va_start(args, format);
    if (parse_string(&args, format, &ret, &flags) == -1)
        ret = -1;
    va_end(args);
    return (ret);
}
/*
int main(void)
{
    printf("%d\n", printf("%8.5x", 0));
    printf("%d\n", ft_printf("%8.5x", 0));
    printf("%d\n", printf("%03.3d", -8462));
    printf("%d\n", ft_printf("%03.3d", -8462));
    printf("%d\n", printf("%03.3d", 6983));
    printf("%d\n", ft_printf("%03.3d", 6983));
    printf("%d\n", printf("%08.5d", 34));
    printf("%d\n", ft_printf("%08.5d", 34));
    printf("%d\n", printf("%32s", "abc"));
    printf("%d\n", ft_printf("%32s", "abc"));
    printf("%d\n", printf("%16s", "nark nark"));
    printf("%d\n", ft_printf("%16s", "nark nark"));
    printf("%d\n", printf("%5s", "goes over"));
    printf("%d\n", ft_printf("%5s", "goes over"));
    printf("%d\n", printf("%.3d", 13862));
    printf("%d\n", ft_printf("%.3d", 13862));
    printf("%d\n", printf("%.4d", -2372));
    printf("%d\n", ft_printf("%.4d", -2372));
    printf("%d\n", printf("%.6d", -3));
    printf("%d\n", ft_printf("%.6d", -3));
    printf("%d\n", printf("%.09s", NULL));
    printf("%d\n", ft_printf("%.09s", NULL));
    printf("%d\n", printf("this %d number", 17));
    printf("%d\n", ft_printf("this %d number", 17));
    printf("%d\n", printf("%.5d", 2));
    printf("%d\n", ft_printf("%.5d", 2));
    printf("%d\n", printf("%.7s", "hello"));
    printf("%d\n", ft_printf("%.7s", "hello"));
    printf("%d\n", printf("%.3s%.2s", "holla", "bitch"));
    printf("%d\n", ft_printf("%.3s%.2s", "holla", "bitch"));
    printf("%d\n", printf("%20.6s", "hi low\0don't print me lol\0"));
    printf("%d\n", ft_printf("%20.6s", "hi low\0don't print me lol\0"));
    printf("%d\n", printf("%.4d", 5263));
    printf("%d\n", ft_printf("%.4d", 5263));
    printf("%d\n", printf("%.03s", NULL));
    printf("%d\n", ft_printf("%.03s", NULL));
    printf("%d\n", printf("%3.1s", NULL));
    printf("%d\n", ft_printf("%3.1s", NULL));
    printf("%d\n", printf("%9.1s", NULL));
    printf("%d\n", ft_printf("%9.1s", NULL));
    printf("%d\n", printf("%.5d", 2));
    printf("%d\n", ft_printf("%.5d", 2));
    printf("%d\n", printf("%.6d", -3));
    printf("%d\n", ft_printf("%.6d", -3));
    printf("%d\n", printf("%.3d", 0));
    printf("%d\n", ft_printf("%.3d", 0));
    return (0);
}*/