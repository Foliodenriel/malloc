#include "libft.h"

char    *ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
    char    *n;
    size_t  len;

    if (!f)
        return (NULL);
    len = ft_strlen(s);
    n = (char*)malloc(sizeof(char) * (len + 1));
    if (!n)
        return (NULL);
    n[len] = '\0';
    len = 0;
    while (s[len])
    {
        n[len] = f(len, s[len]);
        len++;
    }
    return (n);
}