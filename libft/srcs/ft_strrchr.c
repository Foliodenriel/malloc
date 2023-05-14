#include "libft.h"

char    *ft_strrchr(const char *s, int c)
{
    char    *r;
    size_t  i;

    if (!s)
        return (NULL);
    i = 0;
    r = NULL;
    while (s[i])
    {
        if (s[i] == c)
            r = (char*)&s[i];
        i++;
    }
    return (r);
}