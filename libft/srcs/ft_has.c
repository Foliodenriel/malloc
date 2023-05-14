#include "libft.h"

#include <stdio.h>

int ft_has(const char *s, const char *list)
{
    size_t  i;

    i = 0;
    if (!list)
        return (-1);
    while (s[i])
    {
        if (ft_strchr(list, s[i]))
            return (i);
        i++;
    }
    return (-1);
}