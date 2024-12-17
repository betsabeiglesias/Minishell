/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:20:13 by aolabarr          #+#    #+#             */
/*   Updated: 2024/12/17 19:17:31 by aolabarr         ###   ########.fr       */
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
	//ft_print_lst(tk_lst);
	if (!tk_lst)
		return (NULL);
	if (syntax_check_on_tokens(tk_lst))
	{
		lst_clear_token_content(tk_lst);
		ft_lstclear(&tk_lst, &free);
		return (NULL); // LIBERAR TK_LST
	}
	exe_lst = create_execution_list(tk_lst, shell);
	//ft_print_cmd_lst(exe_lst);
	//lst_clear_token_content(tk_lst); LIBERAR AL FINAL EN EL MAIN
	ft_lstclear(&tk_lst, &free);
	return (exe_lst);
}
int syntax_check_on_tokens(t_list *tk_lst)
{
	int size;

	size = ft_lstsize(tk_lst);

	if (size == 1 && is_str_metachar((char *)(tk_lst->content)))
		return(handle_error(ERR_EXTREM), EXIT_FAILURE);
	else if (size == 1 && !is_str_metachar((char *)(tk_lst->content)))
		return(EXIT_SUCCESS);
	else
	{
		if (check_extrem_tokens(tk_lst))
			return(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS) ;
}

int check_extrem_tokens(t_list *tk_lst)
{
	char *token;
	char *token_nx;
	int size;
	int i;

	size = ft_lstsize(tk_lst);
	i = 0;
	while(i < size - 1)
	{
		token = (char *)(tk_lst->content);
		token_nx = (char *)(tk_lst->next->content);
		if (i == 0 && is_str_pipe(token))
			return(handle_error(ERR_EXTREM), EXIT_FAILURE);
		if (i == size - 2 && is_str_metachar(token_nx))
			return(handle_error(ERR_EXTREM), EXIT_FAILURE);
		if (is_str_metachar(token) && is_str_metachar(token_nx))
			return(handle_error(ERR_CONSECUTIVE), EXIT_FAILURE);
		i++;
		tk_lst = tk_lst->next;
	}
	return (EXIT_SUCCESS);	
}

int is_str_metachar(char *str)
{
	if(!str)
		return (0);
	if (is_str_redir(str, REDIR_IN_S) || is_str_redir(str, REDIR_IN_D))
		return(1);
	else if (is_str_redir(str, REDIR_OUT_S) || is_str_redir(str, REDIR_OUT_D))
		return(1);
	else if (is_str_pipe(str))
		return (1);
	return (0);
}
