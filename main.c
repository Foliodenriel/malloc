#include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <sys/mman.h>
#include "ft_printf.h"
#include "ft_malloc.h"
#include <libft.h>

int main(void)
{
    char    *data;
    size_t  i;

    i = 0;
    data = NULL;
    data = (char*)malloc(10);
    while (i < 9)
    {
        data[i] = 'a';
        i++;
    }
    data[9] = '\0';

    printf("%s\n", data);

    free(&data[5]);

    printf("%s\n", data);



    // data = ft_malloc( 10 );

    // printf("%p\n", data);

    // data = ft_malloc( 20 );

    // printf("%p\n", data);

    // show_memory();
    return (0);
}