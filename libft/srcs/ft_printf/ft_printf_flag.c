#include "ft_printf.h"

static void ft_printf_flag_zero(t_printarg *arg)
{
    size_t  i;

    i = 0;
    if (ft_strchr("diouxX", arg->conversion))
    {
        while (arg->s[i] && arg->s[i] == ' ')
            arg->s[i++] = '0';
    }
}

static void ft_printf_flag_diese(t_printarg *arg)
{
    char    *tmp;

    tmp = arg->s;
    if ((arg->conversion == 'x' || arg->conversion == 'p') && (ft_has(arg->s, "123456789") >= 0))
        arg->s = ft_strjoin("0x", arg->s);
    else if (arg->conversion == 'X' && (ft_has(arg->s, "123456789") >= 0))
        arg->s = ft_strjoin("0X", arg->s);
    else if (arg->conversion == 'o' && arg->s[0] != '0')
        arg->s = ft_strjoin("0", arg->s);
    if (tmp != arg->s)
        free(tmp);
}

static void ft_printf_flag_plus(t_printarg *arg)
{
    char    *tmp;

    tmp = arg->s;
    if (ft_strchr("di", arg->conversion))
        arg->s = ft_strjoin("+", arg->s);
    if (tmp != arg->s)
        free(tmp);
}

static void ft_printf_flag_space(t_printarg *arg)
{
    char    *tmp;

    tmp = arg->s;
    if (ft_strchr("di", arg->conversion))
        arg->s = ft_strjoin(" ", arg->s);
    if (tmp != arg->s)
        free(tmp);
}

void        ft_printf_flag(t_printarg *arg)
{
    if (arg->flag & FT_PRINTF_DIESE)
        ft_printf_flag_diese(arg);
    if (arg->flag & FT_PRINTF_ZERO)
        ft_printf_flag_zero(arg);
    if (arg->flag & FT_PRINTF_PLUS)
        ft_printf_flag_plus(arg);
    if (arg->flag & FT_PRINTF_SPACE)
        ft_printf_flag_space(arg);
}