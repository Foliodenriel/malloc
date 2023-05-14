#include "libft.h"

void    ft_lstclear(t_list **lst, void (*del)(void *))
{
    t_list  *tmp;

    tmp = NULL;
    while (*lst)
    {
        if (tmp)
            ft_lstdelone(tmp, del);
        tmp = *lst;
        *lst = (*lst)->next;
    }
    if (tmp)
        ft_lstdelone(tmp, del);
}