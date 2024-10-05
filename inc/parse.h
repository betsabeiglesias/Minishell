/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:39:06 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/05 18:19:03 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

bool	check_quotes(char *str);
// si solo hay espacios blanco o tabulaciones etc           	-> no hacer nada
// si el primer caracter despues de los espacios 
//						no es [A-Z] o [a-z] o $ -> mensaje 		-> syntax error
// si el ultimo caracter es pipe, redirecciones, metacaracteres	-> syntax error


#endif