#include "libft.h"

void    *ft_memset(void *s, int c, size_t n)
{
    unsigned char   *bytes;

    bytes = s;
    if (!s)
        return (NULL);
    while (n)
    {
        *bytes = c;
        bytes++;
        n--;
    }
    return (s);
}