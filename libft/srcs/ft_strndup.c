#include "libft.h"
#include <stdio.h>

char    *ft_strndup(const char *s, size_t n)
{
    char    *bytes;
    size_t  len;

    len = ft_strlen(s);
    if (len > n)
        len = n;
    if (!s)
        return (NULL);
    bytes = (char*)malloc(sizeof(char) * len + 1);
    ft_strlcpy(bytes, s, len + 1);
    return (bytes);
}