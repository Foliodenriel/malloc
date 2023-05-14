#include "libft.h"

char    *ft_strnstr(const char *big, const char *little, size_t len)
{
    size_t  i;
    size_t  little_len;

    if (!big)
        return (NULL);
    if (!little || little[0] == '\0')
        return ((char*)big);
    i = 0;
    little_len = ft_strlen(little);
    while (big[i] && (i + little_len) <= len)
    {
        if (ft_strncmp(&big[i], little, little_len - 1) == 0)
            return ((char*)&big[i]);
        i++;
    }
    return (NULL);
}