/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:51:08 by aolabarr          #+#    #+#             */
/*   Updated: 2024/12/27 09:38:14 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_v(void *str)
{
	if (str)
		free(str);
	return ;
}

void	free_to_prompt(t_list *exe_lst, t_mini *shell)
{
	lst_clear_exec(exe_lst);
	ft_lstclear(&exe_lst, &free);
	if (shell->input)
		ft_free(shell->input);
	if (shell->pid)
		ft_free_v((void *)shell->pid);
	if (shell->pipes)
		ft_free_mat_int(shell->pipes, shell->num_pipes);
	if (access("./here_doc", F_OK) == ACCESS)
	{
		if (unlink(HERE_DOC_DIR) == ERROR)
			perror (ERR_MSG_HERE);
	}
	if (shell->all_paths)
		ft_free_mat_str(shell->all_paths, ft_matsize(shell->all_paths));
	shell->num_pipes = 0;
	exe_lst = NULL;
	shell->input = NULL;
	shell->pid = NULL;
	shell->pipes = NULL;
	shell->all_paths = NULL;
	return ;
}
