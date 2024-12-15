/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 12:18:33 by beiglesi          #+#    #+#             */
/*   Updated: 2024/12/14 23:39:49 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// COMPROBAR EN EL PROMPT COMO SE IMPRIME EL SALTO DE LÍNEA 

#include "../inc/minishell.h"

int	builtin_pwd(int fd)
{
	char	*currentwd;

	currentwd = getcwd(NULL, 0);
	if (currentwd == NULL)
	{
		return (handle_error(ERR_ACCESS), EXIT_FAILURE);
	}
	else
	{
		ft_putstr_fd(currentwd, fd);
		ft_putchar_fd('\n', fd);
		free(currentwd);
	}
	return (EXIT_SUCCESS);
}

int handle_exec_onlybuilt(t_exec *node, t_mini *shell)
{
	t_fd	*fd;
	
	fd = do_redir_built(node);
	if (!fd)
	{
		g_status = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	g_status = execute_uniquebuiltin(node, shell, fd);
	ft_free_v((void *)fd);
	return(g_status);
}

int	execute_uniquebuiltin(t_exec *node, t_mini *shell, t_fd *fd)
{
	int	len;

	len = ft_strlen(node->cmd_all[0]);
	if (!ft_strncmp(node->cmd_all[0], ENV, len))
		g_status = builtin_env(shell, fd->out);
	else if (!ft_strncmp(node->cmd_all[0], CD, len))
		g_status = builtin_cd(node, shell);
	else if (!ft_strncmp(node->cmd_all[0], PWD, len))
		g_status= builtin_pwd(fd->out);
	else if (!ft_strncmp(node->cmd_all[0], EXPORT, len))
		g_status= builtin_export(node, shell, fd->out);
	else if (!ft_strncmp(node->cmd_all[0], UNSET, len))
		g_status= builtin_unset(node, shell);
	else if (!ft_strncmp(node->cmd_all[0], "echo", len))
		g_status = builtin_echo(node, fd->out);
	else if (!ft_strncmp(node->cmd_all[0], EXIT, len))
		g_status= builtin_exit(node);
	return(g_status);
}

int	execute_builtin(t_exec *node, t_mini *shell)
{
	int	len;

	len = ft_strlen(node->cmd_all[0]);
	if (!ft_strncmp(node->cmd_all[0], ENV, len))
		g_status = builtin_env(shell, STDOUT_FILENO);
	else if (!ft_strncmp(node->cmd_all[0], EXIT, len))
		g_status = builtin_exit(node);
	else if (!ft_strncmp(node->cmd_all[0], "echo", len))
		g_status = builtin_echo(node, STDOUT_FILENO);
	else if (!ft_strncmp(node->cmd_all[0], PWD, len))
		g_status = builtin_pwd(STDOUT_FILENO);
	else if (!ft_strncmp(node->cmd_all[0], CD, len))
		g_status = builtin_cd(node, shell);
	else if (!ft_strncmp(node->cmd_all[0], EXPORT, len))
		g_status = builtin_export(node, shell, STDOUT_FILENO);
	else if (!ft_strncmp(node->cmd_all[0], UNSET, len))
		g_status = builtin_unset(node, shell);
	return(g_status);
}
t_fd *do_redir_built(t_exec *node)
{
	t_fd *fd;
	
	fd = malloc(sizeof(t_fd));
	if(!fd)
		return(handle_error(ERR_MALLOC), NULL);
	fd->in = 0;
	fd->out = 1;
	if (node->filename_in != NULL)
    {
        fd->in = open(node->filename_in, O_RDONLY);
        if (fd->in == ERROR)
		    return (handle_error(ERR_OPEN), NULL);
    }
    if (node->filename_out != NULL && node->out_append == 0)
        fd->out =  open(node->filename_out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    else if (node->filename_out != NULL && node->out_append == 1)
        fd->out = open(node->filename_out, O_CREAT | O_RDWR | O_APPEND, 0644);
    if (fd->out == ERROR)
		return (handle_error(ERR_OPEN), NULL);
	return (fd);
}
