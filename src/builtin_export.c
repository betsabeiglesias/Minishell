/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:56:51 by binary            #+#    #+#             */
/*   Updated: 2024/12/15 17:33:46 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_export(t_exec *node, t_mini *shell, int fd)
{
	int	args;

	args = 1;
	if (!node->cmd_all[args])
		export_no_args(shell, fd);
	while(node->cmd_all[args])
	{
		if(!check_namevar(node->cmd_all[args]))
			return(EXIT_FAILURE);
		if (export_args(node->cmd_all[args], shell))
			return (EXIT_FAILURE);
		args++;
	}
	return (EXIT_SUCCESS);
}

int change_var_value(char *str, t_mini *shell)
{
	int	i;
	int	len_name;

	i = 0;
	len_name = len_var_name(str);
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], str, len_name))
		{
			shell->env[i] = ft_strdup(str);
			if (!shell->env[i])
				return (handle_error(ERR_MALLOC), EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}
int	len_var_name(char *str)
{
	int	i;

	i = 0;
	while(str[i] && str[i] != '=')
		i++;
	return (i);
}

int	export_args(char *str, t_mini *shell)
{
	if (!change_var_value(str, shell))
		return (EXIT_SUCCESS);
	if (!add_newvar(str, shell))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

// void	ft_free_mat_str2(char ***mat, size_t size)
// {
// 	size_t	i;

// 	if (!mat || !(*mat))
// 		return ;
// 	i = 0;
// 	while (i < size)
// 	{
// 		if ((*mat)[i])
// 			free((*mat)[i]);
// 		(*mat)[i] = NULL;
// 		i++;
// 	}
// 	free(*mat);
// 	*mat = NULL; // Ahora el puntero original se establece en NULL
// }

int add_newvar(char *str, t_mini *shell)
{
	size_t	len;
	size_t	i;
	char	**new_env;

	len = ft_matsize(shell->env);
	i = 0;
	new_env = malloc(sizeof(char *) * (len + 2));
	if (!new_env)
		return (handle_error(ERR_MALLOC), EXIT_FAILURE);
	while (i < len)
	{
		new_env[i] = ft_strdup(shell->env[i]);
		if (!new_env[i])
		{
            while (i > 0)
                free(new_env[--i]);
            free(new_env);
            return (handle_error(ERR_MALLOC), EXIT_FAILURE);
        }
		i++;
	}
	new_env[i] = ft_strdup(str);
	if (!new_env[i])
	{
            while (i > 0)
                free(new_env[--i]);
            free(new_env);
            return (handle_error(ERR_MALLOC), EXIT_FAILURE);
    }
	new_env[i + 1] = NULL;
	ft_free_mat_str(shell->env, len);
	shell->env = new_env;
	return (EXIT_SUCCESS);
}

int	check_namevar(char *str)
{
	int	i;
	
	i = 0;
	while (is_space(str[i]))
		i++;
	if(ft_isalpha(str[i]) || str[i] == '_')
		i++;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		else
			return (0);
	}
	if (str[i] == '=')
		return(1);	
	return (0);
}

void	export_no_args(t_mini *shell, int fd)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		ft_putstr_fd("declare -x ", fd);
		print_export(shell->env[i], fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
}

void	print_export(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar_fd(str[i], fd);
		if (str[i] == '=')
			ft_putchar_fd('\"', fd);
		i++;
	}
	ft_putchar_fd('\"', fd);
}
