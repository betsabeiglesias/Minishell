/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bet.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:00:10 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/30 16:49:33 by beiglesi         ###   ########.fr       */
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
		//free_to_prompt(exe_lst, &shell);
	}
	//liberar shell
	rl_clear_history();
	free_shell(&shell);
	return (EXIT_SUCCESS);
}



// int	term_attributes(void)
// {
// 	struct termios term;

// 	if (tcgetattr(STDIN_FILENO, &term) == -1)
// 		return(EXIT_FAILURE);
// 	if (term.c_lflag & ECHOCTL)
// 	{
// 		term.c_lflag &= ~ECHOCTL;
// 		tcsetattr(STDIN_FILENO, TCSANOW, &term); 
// 	}
// 	return (EXIT_SUCCESS);
// }

