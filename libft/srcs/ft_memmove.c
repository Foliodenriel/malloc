#include "libft.h"

void    *ft_memmove(void *dest, const void *src, size_t n)
{
    size_t              i;
    unsigned char       *dest_tmp;
    const unsigned char *src_tmp;

    if (!dest || !src)
        return (NULL);
    i = 0;
    dest_tmp = dest;
    src_tmp = src;
    if (dest_tmp > src_tmp)
    {
        while (n > 0)
        {
            dest_tmp[n - 1] = src_tmp[n - 1];
            n--;
        }
    }
    else if (dest_tmp < src_tmp)
    {
        while (i < n)
        {
            dest_tmp[i] = src_tmp[i];
            i++;
        }
    }
    return (dest);
}
