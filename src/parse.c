/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:02:40 by aolabarr          #+#    #+#             */
/*   Updated: 2024/10/26 19:56:11 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int parse(char *str)
{
   if (syntax_check(str))
      return (1);
   //do_expasion
   //clean_string
   // aclarar bien el flujo de información
   // que estructuras se necesitan?
   // que se tiene que liberar en cada momento?
}