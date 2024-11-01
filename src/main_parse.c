



#include "../inc/minishell.h"

int main(int ac, char **av)
{
    t_list *lst = NULL;

    if (ac == 1 || ac > 2)
        return (printf("1 argumento please\n"), 0);
    printf("\nENTRADA PROMPT\n%s\n", av[1]);
    lst = (t_list *)parse(av[1]);
    if (!lst)
      return (EXIT_FAILURE);
    ft_print_lst(lst);
    lst_clear_token_content(lst);
    ft_lstclear(&lst, &free);
    return (0);
}

int    ft_print_lst(t_list *list)
{
    if(!list)
        return (printf("Empty list\n"));
    printf("\nLISTA\n");
    while (list)
    {
        printf("%s ", list->token.content);
        list = list->next;
    }
    printf("\n\n");
    return (0);
}
