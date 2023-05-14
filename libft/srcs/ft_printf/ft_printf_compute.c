#include "ft_printf.h"

static void ft_printf_compute_width(t_printarg *arg)
{
    char    *tmp;
    size_t  len;

    tmp = arg->s;
    len = ft_strlen(arg->s);
    if (arg->width > (int)len)
    {
        arg->s = ft_calloc(sizeof(char), arg->width + 1);
        ft_memset(arg->s, ' ', arg->width);
        if (arg->flag & FT_PRINTF_MINUS)
            ft_memcpy(arg->s, tmp, len);
        else
            ft_strlcpy(&arg->s[arg->width - len], tmp, len + 1);
    }
    if (tmp != arg->s)
        free(tmp);
}

static void ft_printf_compute_precision_helper(t_printarg *arg, size_t len, int neg)
{
    char    *tmp;

    tmp = arg->s;
    if (neg)
    {
        arg->s = ft_calloc(sizeof(char), ft_strlen(tmp));
        ft_strlcpy(arg->s, &tmp[1], ft_strlen(tmp));
        if (tmp && (tmp != arg->s))
            free(tmp);
        tmp = arg->s;
        len = ft_strlen(arg->s);
    }
    if (arg->conversion != 's')
    {
        arg->s = ft_calloc(sizeof(char), arg->precision + 1);
        ft_memset(arg->s, '0', arg->precision);
        ft_strlcpy(&arg->s[arg->precision - len], tmp, len + 1);
    }
    if (neg)
        arg->s = ft_strjoin("-", arg->s);
    if (tmp && (tmp != arg->s))
            free(tmp);
}

static void ft_printf_compute_precision(t_printarg *arg)
{
    char    *tmp;
    size_t  len;

    tmp = arg->s;
    len = ft_strlen(arg->s);
    if (arg->precision < (int)len)
    {
        if (arg->conversion == 's')
            arg->s = ft_strndup(arg->s, arg->precision);
        if (tmp && (tmp != arg->s))
            free(tmp);
    }
    else if (arg->precision >= (int)len)
        ft_printf_compute_precision_helper(arg, len, (arg->s[0] == '-'));
}

void        ft_printf_compute(t_printarg *arg)
{
    if (ft_strchr("spdiouxX", arg->conversion) && arg->flag & FT_PRINTF_PREC)
        ft_printf_compute_precision(arg);
    ft_printf_flag(arg);
    if (arg->flag & FT_PRINTF_WIDTH)
        ft_printf_compute_width(arg);
}