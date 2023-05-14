#include "libft.h"

char    *ft_strtoupper(char *s)
{
    char    *tmp;

    tmp = s;
    while (*s)
    {
        *s = ft_toupper(*s);
        s++;
    }
    return (tmp);
}