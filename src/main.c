/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:00:10 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/09 18:19:48 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_mini	shell;
	t_list	*cmdline;

	if (argc != 1)
		return(handle_error(ERR_ARG), EXIT_FAILURE);
	(void)argv;

	init_shell(&shell);
	if (get_my_env(envp, &shell))
		return(handle_error(ERR_ENVP), EXIT_FAILURE);
	if (get_all_paths(&shell))
		return(handle_error(ERR_ENVP), EXIT_FAILURE);
	setup_signal_handlers();
	while (1)
	{
		shell.input = readline(MINISHELL);
		if(handle_eof_interactive(shell.input))
			continue ;
		if (shell.input && *shell.input)
			add_history(shell.input);
		cmdline = parse(&shell);
		// analizar si cmdline = NULL
		if (!ft_strncmp(shell.input, EXIT, ft_strlen(shell.input)))
		{
			free(shell.input);
			exit(EXIT_SUCCESS);
		}
		//PRINTS
		//printf("%s\n", shell.input);
		
		
		//FREES
		lst_clear_token_content(cmdline);
		ft_lstclear(&cmdline, &free);
		ft_free(shell.input);
	}
	//liberar shell
	rl_clear_history();
	free_shell(&shell);
	return (EXIT_SUCCESS);
}
