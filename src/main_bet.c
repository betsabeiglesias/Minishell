/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bet.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:00:10 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/05 11:36:19 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	term_attributes(void)
{
	struct termios term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return(EXIT_FAILURE);
	if (term.c_lflag & ECHOCTL)
	{
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term); 
	}
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv, char **envp)
{
	t_mini	shell;
	t_list	*cmdline;

	if (argc != 1)
		return(handle_error(ERR_ARG), EXIT_FAILURE);
	(void)argv;
	if(!term_attributes())
		return(handle_error(ERR_ATTR), EXIT_FAILURE);
	init_shell(&shell);
	if (get_my_env(envp, &shell))
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
		ft_print_lst(cmdline);
		
		//FREE
		ft_free(shell.input);
	}
	//liberar shell
	return (EXIT_SUCCESS);
}
