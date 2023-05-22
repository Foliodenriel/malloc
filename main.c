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

    // data1 = NULL;

    ft_printf("t_block (%lu)\n", sizeof(t_block));
    ft_printf("t_page (%lu)\n\n", sizeof(t_page));

    data1 = (char*)ft_malloc( 10 );
    data1[0] = 'H';
    data1[1] = 'e';
    data1[2] = 'l';
    data1[3] = 'l';
    data1[4] = 'o';
    data1[5] = ' ';
    data1[6] = 'g';
    data1[7] = 'u';
    data1[8] = 'y';
    data1[9] = '\0';

    show_memory( );

    ft_printf("Phrase : %s\n", data1);

    // printf("%p\n", data1);

    // data2 = ft_malloc( 20 );
    // printf("%p\n", data2);

    // data3 = ft_malloc( 10 );
    // printf("%p\n", data3);

    // show_memory();

    // ft_free( data2 );

    // show_memory();

    // data2 = ft_malloc( 136 );
    // printf("%p\n", data2);

    // show_memory();
    return (0);
}