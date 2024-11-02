



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

