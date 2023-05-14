#ifndef __FT_PRINTF_H__
# define __FT_PRINTF_H__

# include "libft.h"

typedef struct      s_printarg
{
    unsigned char   flag;
    int             width;
    int             precision;
    char            conversion;
    char            *s;
    size_t          index;
}                   t_printarg;

enum                e_flag
{
    FT_PRINTF_DIESE = 0b00000001,
    FT_PRINTF_ZERO  = 0b00000010,
    FT_PRINTF_MINUS = 0b00000100,
    FT_PRINTF_SPACE = 0b00001000,
    FT_PRINTF_PLUS  = 0b00010000,
    FT_PRINTF_WIDTH = 0b00100000,
    FT_PRINTF_PREC  = 0b01000000,
    FT_PRINTF_ARG   = 0b10000000
};

void    ft_printf_fill(va_list vl, t_printarg *arg);
void    ft_printf_compute(t_printarg *arg);
void    ft_printf_flag(t_printarg *arg);
int     ft_printf(const char *format, ...);

#endif