



#include "../inc/minishell.h"

int main(int ac, char **av)
{
    if (ac > 2)
        return (printf("Solo 1 argumento please\n"), 0);
    printf("%s\n", av[1]);
    syntax_check(av[1]);
    return (0);
}