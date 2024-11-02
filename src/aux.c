

#include "../inc/minishell.h"

int    ft_print_lst(t_list *list)
{
    if(!list)
        return (printf("Empty list\n"));
    printf("\nLISTA\n");
    while (list)
    {
        printf("%s\n", list->token.content);
        list = list->next;
    }
    printf("\n\n");
    return (0);
}
