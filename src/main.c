/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:00:10 by aolabarr          #+#    #+#             */
/*   Updated: 2024/12/16 16:36:57 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int g_status = 0;

int main(int argc, char **argv, char **envp)
{
	t_mini	shell;
	t_list	*exe_lst;

	if (argc != 1)
		return(handle_error(ERR_ARG), EXIT_FAILURE);
	(void)argv;
	exe_lst = NULL;
	init_shell(&shell, envp);
	if (handle_enviroment(envp, &shell))
		return (EXIT_FAILURE);
	setup_signal_handlers_shell();
	while (1)
	{
		new_prompt(&shell, exe_lst);
	}
	rl_clear_history();
	free_shell(&shell);
	return (EXIT_SUCCESS);
}

int handle_enviroment(char **envp, t_mini *shell)
{
	if (!envp || !shell)
		return (EXIT_FAILURE);
	if (get_my_env(envp, shell))
		return(handle_error(ERR_ENVP), EXIT_FAILURE);
	if (get_all_paths(shell))
	{
		ft_free_mat_str(shell->env, ft_matsize(shell->env));
		return(handle_error(ERR_ENVP), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	new_prompt(t_mini *shell, t_list *exe_lst)
{
	shell->input = readline(MINISHELL);
	/* parte del exit BORRAR
	if (shell.input && !ft_strncmp(shell.input, EXIT, 4))
	{
		ft_free(shell.input);
		exit(EXIT_SUCCESS);
	}
	*/
	handle_eof_interactive(shell->input);
	if (shell->input && *shell->input)
		add_history(shell->input);
	exe_lst = parse(shell);
	if (exe_lst)
		init_execution(exe_lst, shell);
	//FREES
	free_to_prompt(exe_lst, shell);
	return ;
}

void free_to_prompt(t_list *exe_lst, t_mini *shell)
{
	lst_clear_exec(exe_lst);
	ft_lstclear(&exe_lst, &free);
	if (shell->input)
		ft_free(shell->input);
	if (shell->pid)
		ft_free_v((void *)shell->pid); //DA SEG FAULT
	if (shell->pipes)
		ft_free_mat_int(shell->pipes, shell->num_pipes);
	if (access("./here_doc", F_OK) == ACCESS)
	{
		if (unlink(HERE_DOC_DIR) == ERROR)
        	perror(ERR_MSG_HERE);
	}
	shell->num_pipes = 0;
	exe_lst = NULL;
	shell->input = NULL;
	shell->pid  = NULL;
	shell->pipes  = NULL;
	return ;
}
