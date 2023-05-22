#include "ft_printf.h"
#include <stdio.h>

static t_printarg   *ft_printarg_new(char *s, enum e_flag flag)
{
    t_printarg *arg;

    arg = (t_printarg*)malloc(sizeof(t_printarg));
    if (arg)
    {
        arg->flag = 0 | flag;
        arg->width = 0;
        arg->precision = 1;
        arg->conversion = 0;
        arg->s = s;
    }
    return (arg);
}

static t_list       *ft_printf_getnext(char **s)
{
    char            *tmp;
    unsigned char   c;
    int             i;

    tmp = *s;
    if (!(*s) || !(**s))
        return (NULL);
    if (**s == '%')
    {
        i = ft_has(tmp + 1, "cspdiouxX%");
        tmp++;
        i++;
        (*s) += i + 1;
        c = FT_PRINTF_ARG;
    }
    else
    {
        *s = ft_strchr(tmp, '%');
        i = (int)(*s - tmp);
        c = 0;
    }
    return (ft_lstnew(ft_printarg_new(ft_strndup(tmp, i), c)));
}

static void         ft_printf_parse(va_list vl, t_list *lst)
{
    t_printarg  *arg;
    char        *s;
    char        *tmp;

    s = NULL;
    while (lst)
    {
        arg = lst->content;
        if (arg && (arg->flag & FT_PRINTF_ARG))
        {
            tmp = arg->s;
            ft_printf_fill(vl, arg);
            ft_printf_compute(arg);
            if (tmp && (tmp != arg->s))
                free(tmp);
        }
        tmp = s;
        s = ft_strjoin(s, arg->s);
        if (tmp && (tmp != s))
            free(tmp);
        if (arg->s)
            free(arg->s);
        lst = lst->next;
    }
    ft_putstr_fd(s, 1);
    free(s);
}

static void         ft_printf_free(void *content)
{
    t_printarg *arg = (t_printarg*)content;

    free(content);
}

int                 ft_printf(const char *format, ...)
{
    va_list vl;
    t_list  *lst;
    t_list  *e;
    char    *s;

    lst = NULL;
    s = (char*)format;
    va_start(vl, format);
    while ((e = ft_printf_getnext(&s)))
        ft_lstadd_back(&lst, e);
    ft_printf_parse(vl, lst);
    ft_lstclear(&lst, ft_printf_free);

    va_end(vl);
    return (1);
}