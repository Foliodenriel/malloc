#include "libft.h"

char*   ft_strtolower(char *s)
{
    char    *tmp;

    tmp = s;
    while (*s)
    {
        *s = ft_tolower(*s);
        s++;
    }
    return (tmp);
}