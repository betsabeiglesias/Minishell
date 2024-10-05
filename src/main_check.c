



#include "../inc/minishell.h"

int main(int ac, char **av)
{
    if (ac > 2)
        return (printf("Solo 1 argumento please\n"), 0);
    printf("%s\n", av[1]);
    if (check_quotes(av[1]) == false)
        printf("Comillas abiertas NOK\n");
    else
        printf("Comillas cerradas OK\n");
    return (0);
}