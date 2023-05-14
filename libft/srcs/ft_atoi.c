#include "libft.h"

int         ft_atoi(const char *nptr)
{
    size_t  len;
    int     r;

    r = 0;
    if (!nptr || (nptr[0] != '-' && nptr[0] != '+' && !ft_isdigit(nptr[0])))
        return (r);
    len = 0;
    if (nptr[0] == '-' || nptr[0] == '+')
        len = 1;
    while (nptr[len] && ft_isdigit(nptr[len]))
        r = (r * 10) + ((int)nptr[len++] - 48);
    if (nptr[0] == '-')
        r *= -1;
    return (r);
}