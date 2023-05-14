#include "libft.h"

static size_t   ft_itoa_length(int n)
{
    size_t  i;

    i = 0;
    while (n)
    {
        n /= 10;
        i++;
    }
    if (i == 0)
        return (1);
    return (i);
}

static char     *ft_itoa_parse(char *s, int n, size_t len)
{
    int n_abs;

    while (len != 0)
    {
        n_abs = n % 10;
        if (n_abs < 0)
            n_abs *= -1;
        s[len] = n_abs + 48;
        n /= 10;
        len--;
    }
    n_abs = n % 10;
    if (n_abs < 0)
        n_abs *= -1;
    s[len] = n_abs + 48;
    return (s);
}

char            *ft_itoa(int n)
{
    char    *s;
    int     neg;
    size_t  len;

    neg = 0;
    if (n < 0)
        neg = 1;
    len = ft_itoa_length(n);
    s = (char*)malloc(sizeof(char) * (len + neg + 1));
    if (!s)
        return (NULL);
    s[len] = '\0';
    if (n == 0)
        s = ft_itoa_parse(s, n, 0);
    else
        s = ft_itoa_parse(s, n, len + neg - 1);
    if (neg)
        s[0] = '-';
    return (s);
}