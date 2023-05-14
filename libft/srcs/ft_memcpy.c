#include "libft.h"

void    *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t              i;
    unsigned char       *dest_tmp;
    const unsigned char *src_tmp;

    if (!dest || !src)
        return (NULL);
    i = 0;
    dest_tmp = dest;
    src_tmp = src;
    while (i < n)
    {
        *dest_tmp = *src_tmp;
        i++;
        dest_tmp++;
        src_tmp++;
    }
    return (dest);
}