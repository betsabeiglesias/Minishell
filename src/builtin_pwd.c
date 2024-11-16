/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 12:18:33 by beiglesi          #+#    #+#             */
/*   Updated: 2024/11/16 13:37:42 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// COMPROBAR EN EL PROMPT COMO SE IMPRIME EL SALTO DE LÍNEA 

#include "../inc/minishell.h"

int	builtin_pwd(void)
{
	char	*currentwd;

	currentwd = getcwd(NULL, 0);
	if (currentwd == NULL)
	{
		return (handle_error(ERR_ACCESS), EXIT_FAILURE);
	}
	else
	{
		ft_putstr_fd(currentwd, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		free(currentwd);
	}
	return (EXIT_SUCCESS);
}

int	execute_builtin(t_exec *node, t_mini *shell)
{
	int	len;

	len = ft_strlen(node->cmd_all[0]);
	if (!ft_strncmp(node->cmd_all[0], "echo", len))
		return (builtin_echo(node->cmd_all));
	if (!ft_strncmp(node->cmd_all[0], CD, len))
		return (builtin_cd(node->cmd_all));
	if (!ft_strncmp(node->cmd_all[0], PWD, len))
		return (builtin_env(shell));
	if (!ft_strncmp(node->cmd_all[0], EXPORT, len))
		return (builtin_export(shell, /*VARIABLE*/));
	if (!ft_strncmp(node->cmd_all[0], UNSET, len))
		return (builtin_unset(shell, /*VARIABLE*/));
	if (!ft_strncmp(node->cmd_all[0], ENV, len))
		return (builtin_env(shell));
	if (!ft_strncmp(node->cmd_all[0], EXIT, len))
		return (builtin_exit(node->cmd_all));
}
