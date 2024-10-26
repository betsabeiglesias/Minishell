



#include "../inc/minishell.h"

int main(int ac, char **av)
{
    char *str = NULL;

    if (ac == 1 || ac > 2)
        return (printf("1 argumento please\n"), 0);
    printf("%s\n", av[1]);
    if (syntax_check(av[1]))
        printf("\nUN NUEVO PROMPT\n" );
    str = clean_string(av[1]);
    if (str)
        printf("%s\n", str);
    else
        printf("null\n");
    return (0);
}