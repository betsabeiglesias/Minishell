



#include "../inc/minishell.h"

int main(int ac, char **av)
{
    t_list *lst = NULL;

    if (ac == 1 || ac > 2)
        return (printf("1 argumento please\n"), 0);
    printf("ENTRADA PROMPT\n%s\n", av[1]);
    if (syntax_check(av[1]))
    {
        printf("\nUN NUEVO PROMPT\n" );
        return (1);
    }  
    lst = tokenization(av[1]);
    ft_print_lst(lst);
    return (0);
}

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
    return (0);
}
