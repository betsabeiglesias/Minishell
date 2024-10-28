/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:32:31 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/28 14:58:57 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"


void	init_varen (t_varenv *var, char *cmd_line, int i)
{
	var->start = i;
	var->len = len_var(cmd_line, i);
	// printf("VAR.LEN %d\n", var->len);
	var->value = ft_substr(cmd_line, i, var->len);
	var->var_expanded = NULL;
	// printf("VAR.value %s\n", var->value);
}

void	clean_varen (t_varenv *var)
{
	if (var->value)
	{
		free (var->value);
		var->value = NULL;
	}
	// if (var->var_expanded)
	// {
	// 	free (var->var_expanded);
	// 	var->var_expanded = NULL;
	// }
}


char	*do_expansion(char **cmd_line, t_mini *mini)
{
	int	i;
	t_varenv var;
	
	
	i = 0;
	while((*cmd_line)[i] != '\0')
	{
		if ((*cmd_line)[i] == '$' && is_expansible(*cmd_line, i))
		{
			i++;
			init_varen(&var, *cmd_line, i);
			// printf("VAR.LEN %d\n", var.len);
			//printf("VAR.value %s\n", var.value);
			get_var_env(mini, &var);
			insert_expanded_var(cmd_line, &var);
			i += var.len;
			//clean_varen(&var);
		}
		i++;
	}
	return(*cmd_line);
}

int main(int argc, char **argv, char **envp)
{
	t_mini *mini;
	mini = malloc(sizeof(t_mini));
    if (mini == NULL) {
        printf("Error al asignar memoria\n");
        return (1);
	}
	t_varenv *var = malloc(sizeof(t_varenv));
   	if (var == NULL) {
   	   printf("Error al asignar memoria\n");
        return (1);
    }
	// int	i;

	// i = 0;	
	mini->env = get_my_env(envp, mini);
	if (mini->env == NULL) 
	{
		printf("Error al inicializar el entorno\n");
		free_mini(mini);
    	return (1);
	}
	if (argc < 2)
	{
		printf("not enough arguments\n");
		free(mini);
		return (1);
	}
	char *cmd_line = strdup(argv[1]);
	if (cmd_line == NULL) 
	{
		printf("Error al asignar memoria para cmd_line\n");
		free_mini(mini);
		return (1);
	}
	printf("RECIBE: %s\n", cmd_line);
	do_expansion(&cmd_line, mini);
	printf("RETORNA: %s\n",cmd_line);
	// free_env(mini);
	free_mini(mini);
	if (var)
		free(var);
	return(0);
}