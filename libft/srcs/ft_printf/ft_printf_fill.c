#include "ft_printf.h"

static void ft_printf_fill_arg(va_list vl, t_printarg *arg)
{
    arg->s = NULL;
    if (arg->conversion == 'd' || arg->conversion == 'i')
        arg->s = ft_itoa((int)va_arg(vl, int));
    else if (arg->conversion == 'o')
        arg->s = ft_uitoa_base((unsigned int)va_arg(vl, unsigned int), 8);
    else if (arg->conversion == 'u')
        arg->s = ft_uitoa_base((unsigned int)va_arg(vl, unsigned int), 10);
    else if (arg->conversion == 'x')
        arg->s = ft_uitoa_base((unsigned int)va_arg(vl, unsigned int), 16);
    else if (arg->conversion == 'X')
        arg->s = ft_strtoupper(ft_uitoa_base((unsigned int)va_arg(vl, unsigned int), 16));
    else if (arg->conversion == 'c')
    {
        arg->s = (char*)malloc(sizeof(char) * 2);
        arg->s[0] = (int)va_arg(vl, int);
        arg->s[1] = '\0';
    }
    else if (arg->conversion == 'p')
        arg->s = ft_ulitoa_base((unsigned long int)va_arg(vl, unsigned long int), 16);
    else if (arg->conversion == 's')
        arg->s = ft_strdup((char*)va_arg(vl, char*));
    else if (arg->conversion == '%')
        arg->s = ft_strjoin("%", NULL);
}

static void ft_printf_fill_width(va_list vl, t_printarg *arg)
{
    if (arg->s[arg->index] == '*')
        arg->width = (int)va_arg(vl, int);
    else
        arg->width = ft_atoi(&arg->s[arg->index]);
    if (arg->width < 0)
    {
        arg->flag = arg->flag | FT_PRINTF_MINUS;
        arg->width *= -1;
        if ((arg->flag & FT_PRINTF_MINUS) && (arg->flag & FT_PRINTF_ZERO))
            arg->flag = arg->flag ^ FT_PRINTF_ZERO;
    }
    if (arg->width >= 0)
        arg->flag = arg->flag | FT_PRINTF_WIDTH;
    while (arg->s[arg->index] && (arg->s[arg->index] == '*' || ft_isdigit(arg->s[arg->index])
        || arg->s[arg->index] == '-' || arg->s[arg->index] == '+'))
        arg->index++;
}

static void ft_printf_fill_prec(va_list vl, t_printarg *arg)
{
    if (arg->s[arg->index] == '.')
    {
        arg->index++;
        if (arg->s[arg->index] == '*')
            arg->precision = (int)va_arg(vl, int);
        else
            arg->precision = ft_atoi(&arg->s[arg->index]);
        if (arg->precision >= 0)
            arg->flag = arg->flag | FT_PRINTF_PREC;
        arg->flag = arg->flag ^ FT_PRINTF_ZERO;
    }
}

static void ft_printf_fill_convflag(t_printarg *arg)
{
    arg->index = 0;
    arg->conversion = arg->s[ft_strlen(arg->s) - 1];
    while (arg->s[arg->index] && ft_strchr("#0- +", arg->s[arg->index]))
    {
        if (arg->s[arg->index] == '#')
            arg->flag = arg->flag | FT_PRINTF_DIESE;
        else if (arg->s[arg->index] == '0')
            arg->flag = arg->flag | FT_PRINTF_ZERO;
        else if (arg->s[arg->index] == '-')
            arg->flag = arg->flag | FT_PRINTF_MINUS;
        else if (arg->s[arg->index] == ' ')
            arg->flag = arg->flag | FT_PRINTF_SPACE;
        else if (arg->s[arg->index] == '+')
            arg->flag = arg->flag | FT_PRINTF_PLUS;
        arg->index++;
    }
    if ((arg->flag & FT_PRINTF_MINUS) && (arg->flag & FT_PRINTF_ZERO))
        arg->flag = arg->flag ^ FT_PRINTF_ZERO;
    if ((arg->flag & FT_PRINTF_SPACE) && (arg->flag & FT_PRINTF_PLUS))
        arg->flag = arg->flag ^ FT_PRINTF_SPACE;
    if (arg->conversion == 'p')
        arg->flag = arg->flag | FT_PRINTF_DIESE;
}

void        ft_printf_fill(va_list vl, t_printarg *arg)
{
    ft_printf_fill_convflag(arg);
    ft_printf_fill_width(vl, arg);
    ft_printf_fill_prec(vl, arg);
    ft_printf_fill_arg(vl, arg);
}