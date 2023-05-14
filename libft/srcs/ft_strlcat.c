#include "libft.h"

size_t  ft_strlcat(char *dst, const char *src, size_t size)
{
    size_t  i;

    if (!dst || !src)
        return (0);
    i = 0;
    while (dst[i])
        i++;
    return (i + ft_strlcpy(&dst[i], src, size));
}