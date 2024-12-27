/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 10:56:41 by beiglesi          #+#    #+#             */
/*   Updated: 2024/12/27 14:55:06 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_cd(t_exec *node, t_mini *shell)
{
	if (!node->cmd_all[1])
		return (cd_to_home(shell), EXIT_SUCCESS);
	if (!ft_strncmp(node->cmd_all[1], "..", 2) \
		|| !ft_strncmp(node->cmd_all[1], "-", 1))
		return (cd_especial_cases(node, shell), EXIT_SUCCESS);
	if (chdir(node->cmd_all[1]) == 0)
		return (EXIT_SUCCESS);
	return (handle_error(ERR_CHDIR), EXIT_FAILURE);
}

int	cd_to_home(t_mini *shell)
{
	char	*home_path;
	char	*dir_to_save;

	home_path = find_value_varenv("HOME", shell);
	if (!home_path)
		return (handle_error(ERR_GETWD), EXIT_FAILURE);
	dir_to_save = getcwd(NULL, 0);
	if (!dir_to_save)
		return (handle_error(ERR_GETWD), EXIT_FAILURE);
	if (change_value_varenv("OLDPWD", dir_to_save, shell) != 0)
		return (free(dir_to_save), handle_error(ERR_OLDPWD), EXIT_FAILURE);
	if (chdir(home_path) != 0)
		return (free(dir_to_save), handle_error(ERR_CHDIR), EXIT_FAILURE);
	free(dir_to_save);
	dir_to_save = getcwd(NULL, 0);
	if (!dir_to_save)
		return (handle_error(ERR_GETWD), EXIT_FAILURE);
	if (change_value_varenv("PWD", dir_to_save, shell) != 0)
		return (free(dir_to_save), EXIT_FAILURE);
	free(dir_to_save);
	return (EXIT_SUCCESS);
}

char	*find_value_varenv(char *str, t_mini *shell)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (shell->env[i])
	{
		if (!ft_strncmp(str, shell->env[i], len) && shell->env[i][len] == '=')
			return (shell->env[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	update_dir_env(char *dir, char *new_value, t_mini *shell)
{
	int		i;
	int		len;
	char	*new_var;

	i = 0;
	len = ft_strlen(dir);
	while (shell->env[i])
	{
		if (!ft_strncmp(dir, shell->env[i], len) && shell->env[i][len] == '=')
		{
			new_var = ft_strjoin_variadic(3, dir, "=", new_value);
			if (!new_var)
				return (handle_error(ERR_MALLOC), EXIT_FAILURE);
			free(shell->env[i]);
			shell->env[i] = new_var;
			return (EXIT_SUCCESS);
		}
		i++;
	}
	new_var = ft_strjoin_variadic(3, dir, "=", new_value);
	if (!new_var)
		return (handle_error(ERR_MALLOC), EXIT_FAILURE);
	if (add_newvar(new_var, shell) != EXIT_SUCCESS)
		return (free(new_var), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	update_env(char *var_name, char *new, t_mini *shell)
{
	size_t	i;
	char	*temp;
	int		len;

	i = 0;
	len = ft_strlen(var_name);
	while (shell->env[i])
	{
		if (!ft_strncmp(var_name, shell->env[i], len) \
		&& shell->env[i][len] == '=')
		{
			temp = shell->env[i];
			shell->env[i] = ft_strdup(new);
			if (!shell->env[i])
				return (handle_error(ERR_MALLOC), EXIT_FAILURE);
			free(temp);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}
