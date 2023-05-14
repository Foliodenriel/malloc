#ifndef __GET_NEXT_LINE_H__
# define __GET_NEXT_LINE_H__

# include "libft.h"

# define BUFFER_SIZE 8

typedef struct  s_gnl
{
    char        *s;
    int         fd;
}               t_gnl;

char    *get_next_line(int fd);

#endif