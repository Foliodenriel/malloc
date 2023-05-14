#include "libft.h"

char    *ft_strtrim(char const *s1, char const *s2)
{
    char    *r;
    size_t  start;
    size_t  end;

    start = 0;
    end = ft_strlen(s1) - 1;
    r = NULL;
    while (ft_strchr(s2, s1[start]) && s1[start])
        start++;
    while (ft_strchr(s2, s1[end]) && end != 0)
        end--;
    if (start > end)
        return (NULL);
    r = ft_substr(s1, start, end - start + 1);
    return (r);
}