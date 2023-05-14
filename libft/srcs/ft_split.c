#include "libft.h"

static size_t   ft_split_count(char *s, char c)
{
    size_t  count;

    count = 0;
    if (!s)
        return (0);
    while (*s)
    {
        if (*s != c)
        {
            count++;
            while (*s && *s != c)
                s++;
        }
        else
            s++;
    }
    return (count);
}

static char     *ft_split_next(char *s, char c, size_t *i)
{
    char    *str;
    size_t  start;

    start = *i;
    while (s[*i] && s[*i] != c)
        (*i)++;
    str = (char*)malloc(sizeof(char) * (*i - start + 1));
    ft_strlcpy(str, (const char*)&s[start], (*i - start + 1));
    while (s[*i] && s[*i] == c)
        (*i)++;
    return (str);
}

char            **ft_split(char const *s, char c)
{
    char    **tab;
    char    *tmp;
    size_t  count;
    size_t  index;
    size_t  i;

    i = 0;
    index = 0;
    tab = NULL;
    if (!s)
        return (NULL);
    tmp = ft_strtrim(s, &c);
    count = ft_split_count(tmp, c);
    if (!count)
        return (NULL);
    tab = (char**)malloc(sizeof(char*) * (count + 1));
    tab[count] = NULL;
    while (i < count)
    {
        tab[i] = ft_split_next(tmp, c, &index);
        i++;
    }
    free(tmp);
    return (tab);
}