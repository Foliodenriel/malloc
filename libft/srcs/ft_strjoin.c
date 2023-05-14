#include "libft.h"

char    *ft_strjoin(char const *s1, char const *s2)
{
    char    *r;
    size_t  s1_len;
    size_t  s2_len;

    s1_len = ft_strlen(s1);
    s2_len = ft_strlen(s2);
    r = (char*)malloc(sizeof(char) * (s1_len + s2_len + 1));
    ft_strlcpy(r, s1, s1_len + 1);
    ft_strlcpy(&r[s1_len], s2, s2_len + 1);
    r[s1_len + s2_len] = '\0';
    return (r);
}