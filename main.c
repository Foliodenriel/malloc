#include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <sys/mman.h>
#include "ft_printf.h"
#include "ft_malloc.h"
#include <libft.h>

int main(void)
{
    char    *data1;
    void    *data2;
    void    *data3;

    ft_printf("t_block (%lu)\n", sizeof(t_block));
    ft_printf("t_page (%lu)\n\n", sizeof(t_page));

    data1 = ft_malloc( 10 );
    data2 = ft_malloc( 20 );

    show_memory( );

    ft_free( data1+5 );

    show_memory( );

    ft_free( data1 );

    show_memory( );

    data3 = ft_malloc( 272 );

    show_memory( );

    data1 = ft_malloc( 8 );

    show_memory( );

    ft_free( data1 );
    ft_free( data2 );
    ft_free( data3 );

    show_memory( );
    
    return (0);
}