/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:20:13 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/01 13:13:39 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	*parse(char *str)
{
	t_list *lst;
	
	if (syntax_check(str))
      return (NULL);
	// do_expasion
	lst = tokenization(str);
	if (!lst)
		return (NULL);
   // aclarar bien el flujo de información
   // que estructuras se necesitan?
   // que se tiene que liberar en cada momento?
   return (lst);
}
