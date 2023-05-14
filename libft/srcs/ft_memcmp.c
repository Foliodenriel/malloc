#include "libft.h"

int ft_memcmp(const void *s1, const void *s2, size_t n)
{
    const unsigned char *s1_tmp;
    const unsigned char *s2_tmp;

    if (!s1 || !s2)
        return (0);
    s1_tmp = s1;
    s2_tmp = s2;
    while (*s1_tmp && *s2_tmp && n > 0)
    {
        if (*s1_tmp != *s2_tmp)
            return (*s1_tmp - *s2_tmp);
        n--;
        s1_tmp++;
        s2_tmp++;
    }
    return (*s1_tmp - *s2_tmp);
}