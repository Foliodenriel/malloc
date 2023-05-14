#include "libft.h"

size_t  ft_strlen(const char *s)
{
    const char  *t;

    t = s;
    if (!s)
        return (0);
    while (*s)
        s++;
    return (s - t);
}