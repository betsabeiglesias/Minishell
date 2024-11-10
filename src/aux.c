

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
    /*
    char	**env;
	char	*cmd;
	char	**cmd_all;
	char	*path;
	char	*filename_in;
	char	*filename_out;
	char	*heredoc_content;
    */
    printf("\nLISTA DE EXEC: %p\n", cmd_lst);
    while (cmd_lst != NULL)
    {
        printf("EXEC\n");
        printf("here doc: %s\n",((t_exec *)cmd_lst->content)->heredoc_content);
        cmd_lst = cmd_lst->next;
    }
    return (EXIT_SUCCESS);
}

void print_cmd_all(char **cmd_all)
{
    size_t i;
    
    i = 0;
    printf("CMD_all: ");
    while (i < ft_matsize(cmd_all))
    {
        printf("%s ", cmd_all[i]);
    }
    printf("\n");
}
