#include "get_next_line.h"

static t_list   *get_next_line_elem(t_list *lst, int fd)
{
    t_gnl   *g;

    g = NULL;
    if (!lst)
        return (NULL);
    while (lst)
    {
        g = lst->content;
        if (g && g->fd == fd)
            return (lst);
        lst = lst->next;
    }
    return (NULL);
}

static char     *get_next_line_compute(char **s)
{
    char    *eof;
    char    *tmp;
    char    *tmp2;

    if ((eof = ft_strchr(*s, '\n')))
    {
        tmp = (char*)malloc(sizeof(char) * (ft_strlen(eof)));
        ft_strlcpy(tmp, eof + 1, ft_strlen(eof));
        tmp2 = (char*)malloc(sizeof(char) * (eof - *s + 1));
        ft_strlcpy(tmp2, *s, eof - *s + 1);
        if (*s)
            free(*s);
        *s = tmp;
    }
    else
    {
        tmp2 = (char*)malloc(sizeof(char) * (ft_strlen(*s) + 1));
        ft_strlcpy(tmp2, *s, ft_strlen(*s) + 1);
        if (*s)
            free(*s);
        *s = NULL;
    }
    return (tmp2);
}

static char     *get_next_line_read(t_list *e)
{
    t_gnl   *g;
    char    *buffer;
    char    *tmp;
    ssize_t len;

    buffer = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    ft_bzero(buffer, BUFFER_SIZE + 1);
    g = e->content;
    while ((len = read(g->fd, buffer, BUFFER_SIZE)) > 0)
    {
        tmp = g->s;
        g->s = ft_strjoin(g->s, buffer);
        if (tmp)
            free(tmp);
        if (ft_strchr(buffer, '\n') || len < BUFFER_SIZE)
            break ;
        ft_bzero(buffer, BUFFER_SIZE + 1);
    }
    if (ft_strlen(g->s) == 0)
        return (NULL);
    return (get_next_line_compute(&g->s));
}

char            *get_next_line(int fd)
{
    static t_list   *lst;
    t_list          *e;
    t_gnl           *g;

    e = get_next_line_elem(lst, fd);
    if (!e)
    {
        ft_lstadd_front(&lst, ft_lstnew(malloc(sizeof(t_gnl))));
        e = lst;
        if ((g = e->content))
        {
            g->s = NULL;
            g->fd = fd;
        }
    }
    return (get_next_line_read(e));
}