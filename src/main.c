/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:00:10 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/30 19:22:47 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_mini	shell;
	t_list	*exe_lst;

	if (argc != 1)
		return(handle_error(ERR_ARG), EXIT_FAILURE);
	(void)argv;
	exe_lst = NULL;
	init_shell(&shell);
	if (get_my_env(envp, &shell))
		return(handle_error(ERR_ENVP), EXIT_FAILURE);
	if (get_all_paths(&shell))
		return(handle_error(ERR_ENVP), EXIT_FAILURE);
	setup_signal_handlers();
	while (1)
	{
		shell.input = readline(MINISHELL);
		if (shell.input && !ft_strncmp(shell.input, EXIT, 4))
		{
			ft_free(shell.input);
			exit(EXIT_SUCCESS);
		}
		if(handle_eof_interactive(shell.input)) // quitar if
			continue ;
		if (shell.input && *shell.input)
			add_history(shell.input);
		exe_lst = parse(&shell);
		if (exe_lst)
			init_execution(exe_lst, &shell);
		//FREES
		free_to_prompt(exe_lst, &shell);
	}
	//liberar shell
	rl_clear_history();
	free_shell(&shell);
	return (EXIT_SUCCESS);
}

void free_to_prompt(t_list *exe_lst, t_mini *shell)
{
	lst_clear_exec(exe_lst);
	ft_lstclear(&exe_lst, &free);
	if (shell->input)
		ft_free(shell->input);
	//printf("Prueba D\n");
	//ft_free(shell->delimiter);
	//printf("Prueba F\n");
	if (shell->pid)
		ft_free_v((void *)shell->pid);
	//printf("Prueba G\n");
	if (shell->pipes)
		ft_free_mat_int(shell->pipes, shell->num_pipes);
	shell->num_pipes = 0;
	exe_lst = NULL;
	shell->input = NULL;
	shell->delimiter = NULL;
	shell->pid  = NULL;
	shell->pipes  = NULL;
	return ;
}
