



#include "../inc/minishell.h"

int main(int ac, char **av)
{
    char *str;

    if (ac > 2)
        return (printf("Solo 1 argumento please\n"), 0);
    printf("%s\n", av[1]);
    if (syntax_check(av[1]))
        printf("\nUN NUEVO PROMPT\n" );
    str = clean_string(av[1]);
    printf("%s\n", str);
    return (0);
}