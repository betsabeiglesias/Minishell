/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:39:06 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/11 20:03:05 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef enum	e_error
{
    ERR_OTHER
}				t_error;

# define ERR_QUOTE      0
# define ERR_EXTREM     1
# define ERR_ALONE      2

# define ERR_MSG_QUOTE   "SYNTAX ERROR: open quotes"
# define ERR_MSG_EXTREM   "SYNTAX ERROR: nothing after or before metachar"
# define ERR_MSG_ALONE   "SYNTAX ERROR: need separate metacharacter"


int	check_quotes(char *str);
int	check_final(char *str);
int	is_space(char c);
int	is_valid_metachar(char c);
int	check_extrems(char *str);

int handle_error(int error_type);

int syntax_check(char*str);
int	check_metachar_separate(char *str);

#endif