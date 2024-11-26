/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 12:18:33 by beiglesi          #+#    #+#             */
/*   Updated: 2024/11/25 14:07:23 by binary           ###   ########.fr       */
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
	if (!ft_strncmp(node->cmd_all[0], ENV, len))
	{
		printf("ENTRA EN ENV\n\n");
		builtin_env(shell);
	}
	else if (!ft_strncmp(node->cmd_all[0], EXIT, len))
	{
		printf("ENTRA EN EXIT\n\n");
		builtin_exit();
	}
	else if (!ft_strncmp(node->cmd_all[0], "echo", len))
	{
		printf("ENTRA EN ECHO\n\n");
		builtin_echo(node);
	}
	else if (!ft_strncmp(node->cmd_all[0], PWD, len))
	{
		printf("ENTRA EN PWD\n\n");
		builtin_pwd();
	}
	else if (!ft_strncmp(node->cmd_all[0], CD, len))
	{
		printf("ENTRA EN CD\n\n");
		builtin_cd(node, shell);
	}
	else if (!ft_strncmp(node->cmd_all[0], EXPORT, len))
	{
		printf("ENTRA EN EXPORT\n\n");
		builtin_export(node, shell);
	}
	if (!ft_strncmp(node->cmd_all[0], UNSET, len))
	{
		printf("ENTRA EN UNSET\n\n");
		builtin_unset(node, shell);
	}
	return(EXIT_SUCCESS);
}
