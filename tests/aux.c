

#include "../inc/minishell.h"

int    ft_print_lst(t_list *list)
{
    if(!list)
        return (printf("Empty list\n"));
    printf("\nLISTA\n");
    while (list)
    {
        printf("%s\n", (char *)list->content);
        list = list->next;
    }
    printf("\n");
    return (0);
}
int ft_print_cmd_lst(t_list *cmd_lst)
{
    printf("\nLISTA DE EXEC\n");
    while (cmd_lst != NULL)
    {
        printf("EXEC\n");
        printf("path: %s\n",((t_exec *)cmd_lst->content)->path);
        printf("file IN: %s\n",((t_exec *)cmd_lst->content)->filename_in);
        printf("file OUT: %s\n",((t_exec *)cmd_lst->content)->filename_out);
        printf("OUT append: %d\n",((t_exec *)cmd_lst->content)->out_append);
        printf("here doc: %s\n",((t_exec *)cmd_lst->content)->hdoc_content);
        print_cmd_all(((t_exec *)cmd_lst->content)->cmd_all);
        cmd_lst = cmd_lst->next;
    }
    return (EXIT_SUCCESS);
}

void print_cmd_all(char **cmd_all)
{
    size_t i;
    
    i = 0;
    printf("CMD_all:");
    while (i < ft_matsize(cmd_all))
    {
        printf("%s ", cmd_all[i]); // comprobar direcciones si hay problemas
        i++;
    }
    printf("\n");
}

// void print_env(t_mini *shell)
// {
//     int i = 0;
//     printf("Contenido actual de shell->env:\n");
//     while (shell->env[i])
//     {
//         printf("env[%d]: %s\n", i, shell->env[i]);
//         i++;
//     }
// 	// printf("DIRECCIÓN MEMORIA SHELL ENV: %p\n", shell->env);
// }
