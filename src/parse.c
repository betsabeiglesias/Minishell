/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:20:13 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/25 12:24:05 by binary           ###   ########.fr       */
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
	// ft_print_lst(tk_lst);
	// printf("print en parse...\n");
	// ft_print_cmd_lst(exe_lst);
	//lst_clear_token_content(tk_lst); LIBERAR AL FINAL EN EL MAIN
	//ft_lstclear(&tk_lst, &free); LIBERAR AL FINAL
   // aclarar bien el flujo de información
   // que estructuras se necesitan?
   // que se tiene que liberar en cada momento?
   return (exe_lst);
}
