#include "libft.h"

static size_t   ft_itoa_base_length(unsigned long int n, int base)
{
    size_t  i;

    i = 0;
    if (n == 0)
        return (1);
    while (n)
    {
        n /= base;
        i++;
    }
    return (i);
}

static char     ft_itoa_base_compute(unsigned int n)
{
    if (n >= 10)
        return (n + 87);
    return (n + 48);
}

static char     *ft_itoa_base_parse(char *s, unsigned long int n, int base, size_t len)
{
    int n_abs;

    while (len)
    {
        n_abs = n % base;
        if (n_abs < 0)
            n_abs *= -1;
        s[len] = ft_itoa_base_compute(n_abs);
        n /= base;
        len--;
    }
    n_abs = n % base;
    if (n_abs < 0)
        n_abs *= -1;
    s[len] = ft_itoa_base_compute(n_abs);
    return (s);
}

char            *ft_ulitoa_base(unsigned long int n, int base)
{
    char    *s;
    size_t  len;

    if (base > 16)
        return (NULL);
    len = ft_itoa_base_length(n, base);
    s = (char*)malloc(sizeof(char) * (len + 1));
    if (!s)
        return (NULL);
    if (n == 0)
        s = ft_itoa_base_parse(s, n, base, 0);
    else
        s = ft_itoa_base_parse(s, n, base, len - 1);
    return (s);
}