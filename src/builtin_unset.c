/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:06:14 by binary            #+#    #+#             */
/*   Updated: 2024/11/30 18:56:48 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//var_name es el argumento de unset, pueden ser varios.
//hacer un check de los argumentos alnum y _

int builtin_unset(t_exec *node, t_mini *shell)
{
    int     i;
    int     new_len;
	int		j;
	int 	arg;
    char    **new_env;

	i = 0;
	j = 0;
	arg = ft_matsize(node->cmd_all) - 1;
	new_len = new_reduced_size_env(node, shell);
	new_env = malloc(sizeof(char *) * (new_len + 1));
    if (!new_env)
		return(handle_error(ERR_MALLOC), EXIT_FAILURE);
	while (arg > 0)
	{
		while(shell->env[i])
    	{
			if(ft_strncmp(node->cmd_all[arg], shell->env[i], ft_strlen(node->cmd_all[arg])))
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
		arg--;
	}
	new_env[j] = NULL;
	shell->env = new_env;
	return (EXIT_SUCCESS);
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
