/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 12:18:33 by beiglesi          #+#    #+#             */
/*   Updated: 2024/11/23 18:12:43 by aolabarr         ###   ########.fr       */
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

	printf("Prueba A\n");
	len = ft_strlen(node->cmd_all[0]);
	if (!ft_strncmp(node->cmd_all[0], ENV, len))
		builtin_env(shell);
	// else if (!ft_strncmp((char *)(tk_lst->content), CD, len))
	// {
	// 	printf("entra en CD\n");
	// 	return (builtin_cd((char *)(tk_lst->content), shell),0);
	// }
	// if (!ft_strncmp((char *)(tk_lst->content), PWD, len))
	// {
	// 	printf("entra en PWD\n");
	// 	return (builtin_pwd(),0);
	// }
	// if (!ft_strncmp(node->cmd_all[0], "echo", len))
	// 	return (builtin_echo(node->cmd_all),0);
	// if (!ft_strncmp((char *)(tk_lst->content), CD, len))
	// {
	// 	printf("entra en CD\n");
	// 	return (builtin_cd((char *)(tk_lst->content), shell),0);
	// }
	// if (!ft_strncmp((char *)(tk_lst->content), EXPORT, len))
	// 	return (builtin_export(shell, /*VARIABLE*/));
	// if (!ft_strncmp(node->cmd_all[0], UNSET, len))
	// // 	return (builtin_unset(shell, /*VARIABLE*/));
	return(EXIT_SUCCESS);
}
