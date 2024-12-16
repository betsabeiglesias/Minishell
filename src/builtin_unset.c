/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:06:14 by binary            #+#    #+#             */
/*   Updated: 2024/12/15 17:33:45 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//hacer un check de los argumentos alnum y _

int builtin_unset(t_exec *node, t_mini *shell)
{
    int     i;
    int     new_len;
	int		j;
	int 	arg;
    char    **new_env;
	bool	match;
	int		k;

	j = 0;
	i = 0;
	arg = ft_matsize(node->cmd_all) - 1;
	new_len = new_reduced_size_env(node, shell);
	new_env = malloc(sizeof(char *) * (new_len + 1));
    if (!new_env)
		return(handle_error(ERR_MALLOC), EXIT_FAILURE);
	while(shell->env[i])
	{
		k = 1;
		match = false;
		while(k <= arg)
		{
			if(is_var_name(node->cmd_all[k], shell->env[i]))
			{
				match = true;
				break;
			}
			k++;
		}
		if (match == false)
		{
			new_env[j] = ft_strdup(shell->env[i]);
			if(!new_env[j])
			{
				ft_free_mat_str(new_env, new_len);
				return(handle_error(ERR_MALLOC), EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	free_env(shell);
	shell->env = new_env;
	return (EXIT_SUCCESS);
}
int is_var_name(char *str, char *mini_var)
{
	if (!ft_strncmp(mini_var, str, ft_strlen(str)) && mini_var[ft_strlen(str)] == '=')
			return(1);
	return (0);
}

int	new_reduced_size_env(t_exec *node, t_mini *shell)
{
	int	i;
	int	size;
	int j;

	i = 1;
	size = 0;
	while (node->cmd_all[i])
	{
		j = 0;
		while(shell->env[j])
	    {	   
    	    if(!ft_strncmp(node->cmd_all[i], shell->env[j], ft_strlen(node->cmd_all[i])))
				break;
			j++;
    	    size++;
    	}
		i++;
	}
	return(size);
}
