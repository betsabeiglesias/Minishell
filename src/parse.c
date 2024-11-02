/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:20:13 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/02 16:48:45 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_list	*parse(t_mini *shell)
{
	t_list	*lst;
	char	*str;
	
	if (syntax_check(shell->input))
      return (NULL);
	str = do_expansion(shell);
	if (!str)
		return(NULL);
	lst = tokenization(str);
	if (!lst)
		return (NULL);
   // aclarar bien el flujo de información
   // que estructuras se necesitan?
   // que se tiene que liberar en cada momento?
   return (lst);
}
