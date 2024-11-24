/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:20:13 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/24 01:29:57 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list	*parse(t_mini *shell)
{
	t_list	*tk_lst;
	t_list	*exe_lst;
	char	*str;
	
	if (syntax_check(shell->input))
      return (NULL);
	str = do_expansion(shell);
	if (!str)
		return(NULL);
	tk_lst = tokenization(str);
	if (!tk_lst)
		return (NULL);
	exe_lst = create_execution_list(tk_lst, shell);
	//ft_print_lst(tk_lst); PRINT LISTA TOKENS
	//printf("print en parse...\n");
	//ft_print_cmd_lst(exe_lst); PRINT LISTA DE EXECUTION
	//lst_clear_token_content(tk_lst); LIBERAR AL FINAL EN EL MAIN
	ft_lstclear(&tk_lst, &free); // LIBERAR aqui solo la lista
	return (exe_lst);
}
