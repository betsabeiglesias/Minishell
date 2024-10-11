/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:39:06 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/10 17:28:11 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef enum	e_error
{
    ERR_OTHER
}				t_error;

# define ERR_QUOTE 0
# define ERR_FINAL 1

# define ERR_MSG_QUOTE "SYNTAX ERROR: open quotes\n"
# define ERR_MSG_FINAL "SYNTAX ERROR: nothing after metacharacter\n"


int	check_quotes(char *str);
int	check_final(char *str);
int	is_space(char c);
int	is_valid_metachar(char c);

void handle_error(int error_type);

void syntax_check(char*str);


#endif