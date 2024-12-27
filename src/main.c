/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:00:10 by aolabarr          #+#    #+#             */
/*   Updated: 2024/12/27 09:47:23 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_status;

int	main(int argc, char **argv, char **envp)
{
	t_mini	shell;
	t_list	*exe_lst;

	if (argc != 1)
		return (handle_error(ERR_ARG), EXIT_FAILURE);
	g_status = 0;
	(void)argv;
	exe_lst = NULL;
	init_shell(&shell);
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

int	handle_enviroment(char **envp, t_mini *shell)
{
	if (!envp || !shell)
		return (EXIT_FAILURE);
	if (get_my_env(envp, shell))
		return (handle_error(ERR_ENVP), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	new_prompt(t_mini *shell, t_list *exe_lst)
{
	shell->input = readline(MINISHELL);
	handle_eof_interactive(shell->input);
	if (shell->input && *shell->input)
		add_history(shell->input);
	if (get_all_paths(shell))
		return ;
	exe_lst = parse(shell);
	if (exe_lst)
		init_execution(exe_lst, shell);
	free_to_prompt(exe_lst, shell);
	return ;
}

int	clone_env(t_mini *shell)
{
	char	**temp;
	int		size;
	int		i;

	i = 0;
	size = ft_matsize(shell->env);
	temp = malloc(sizeof(char *)* (size + 1));
	if (!temp)
		return (handle_error(ERR_MALLOC), EXIT_FAILURE);
	while (shell->env[i])
	{
		temp[i] = ft_strdup(shell->env[i]);
		if(!temp[i])
		{
			ft_free_mat_str(temp, i);
			return (handle_error(ERR_MALLOC), EXIT_FAILURE);
		}
		i++;
	}
	temp[i] = '\0';
	ft_free_mat_str(shell->env, size);
	shell->env = temp;
	return (EXIT_SUCCESS);
}