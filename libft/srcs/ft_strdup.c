#include "libft.h"

char    *ft_strdup(const char *s)
{
    char    *bytes;
    size_t  len;

    if (!s)
        return (NULL);
    len = ft_strlen(s);
    bytes = (char*)malloc(sizeof(char) * len);
    ft_strlcpy(bytes, s, len + 1);
    return (bytes);
}