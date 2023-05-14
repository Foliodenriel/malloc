#include "libft.h"

void    *ft_memchr(const void *s, int c, size_t n)
{
    const unsigned char *s_tmp;
    size_t              i;

    if (!s)
        return (NULL);
    i = 0;
    s_tmp = s;
    while (s_tmp[i] && i < n)
    {
        if (s_tmp[i] == (unsigned char)c)
            return ((void*)&s_tmp[i]);
        i++;
    }
    return (NULL);
}