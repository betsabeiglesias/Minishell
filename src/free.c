/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:43:08 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/02 15:08:34 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	lst_clear_token_content(t_list *lst)
{
	int	i;
	int	size;

	size = ft_lstsize(lst);
	i = 0;
	while (i < size)
	{
		ft_free(lst->token.content);
		lst = lst->next;
		i++;
	}
	return ;
}
void handle_free(t_mini shell, int error)
{
	(void)shell;

	if (error == ERR_ENVP)
	{
		//liberar todo shell
	}	
	else if (error == EOF)
	{
		//liberar todo shell
	}
	return ;
}