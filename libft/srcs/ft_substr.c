#include "libft.h"

char    *ft_substr(char const *s, unsigned int start, size_t len)
{
    char    *n;
    size_t  i;

    if (!s)
        return (NULL);
    if (start > ft_strlen(s))
        return (NULL);
    i = 0;
    n = (char*)malloc(sizeof(char) * (len + 1));
    while (s[start] && i < len)
        n[i++] = s[start++];
    n[i] = '\0';
    return (n);
}