/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:06:14 by binary            #+#    #+#             */
/*   Updated: 2024/12/26 22:08:29 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_unset(t_exec *node, t_mini *shell)
{
	int		i;
	int		j;
	int		new_len;
	char	**new_env;

	i = 0;
	j = 0;
	new_len = new_reduced_size_env(node, shell);
	new_env = malloc(sizeof(char *) * (new_len + 1));
	if (!new_env)
		return (handle_error(ERR_MALLOC), EXIT_FAILURE);
	while (shell->env[i])
	{
		if (!match(node->cmd_all, shell->env[i], ft_matsize(node->cmd_all) - 1))
		{
			if (copy_varenv(new_env, shell->env[i], j))
				return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	free_env(shell);
	shell->env = new_env;
	return (EXIT_SUCCESS);
}

int	copy_varenv(char **new_env, char *var_env, int j)
{
	char	*temp;

	temp = ft_strdup(var_env);
	if (!temp)
	{
		ft_free_mat_str(new_env, j);
		return (handle_error(ERR_MALLOC), EXIT_FAILURE);
	}
	new_env[j] = temp;
	return (EXIT_SUCCESS);
}

int	match(char **cmd_all, char *var_env, int arg)
{
	int	k;

	k = 1;
	while (k <= arg)
	{
		if (is_var_name(cmd_all[k], var_env))
			return (1);
		k++;
	}
	return (0);
}

int	is_var_name(char *str, char *mini_var)
{
	if (!ft_strncmp(mini_var, str, ft_strlen(str)) && \
		(mini_var[ft_strlen(str)] == '=' || mini_var[ft_strlen(str)] == '\0'))
		return (1);
	return (0);
}

int	new_reduced_size_env(t_exec *node, t_mini *shell)
{
	int	i;
	int j;
	int	size;

	i = 1;
	size = ft_matsize(shell->env);
	while (node->cmd_all[i])
	{
		j = 0;
		while (shell->env[j])
		{
			if (is_var_name(node->cmd_all[i], shell->env[j]))
			{
				size--;
				break ;
			}
			j++;
		}
		i++;
	}
	return (size);
}
