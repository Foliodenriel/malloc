#include "libft.h"

t_list  *ft_lstnew(void *content)
{
    t_list  *e;

    e = (t_list*)malloc(sizeof(t_list));
    e->next = NULL;
    e->content = content;
    return (e);
}