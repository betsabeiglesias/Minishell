/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:39:06 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/13 13:55:44 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef enum	e_error
{
    ERR_OTHER
}				t_error;

typedef struct  s_quote
{
    bool sing;
    bool doub;
}               t_quote;


# define ERR_QUOTE      0
# define ERR_EXTREM     1
# define ERR_ALONE      2

# define ERR_MSG_QUOTE   "SYNTAX ERROR: open quotes"
# define ERR_MSG_EXTREM   "SYNTAX ERROR: nothing after or before metachar"
# define ERR_MSG_ALONE   "SYNTAX ERROR: need separate metacharacter"

// CHECK SYNTAX 1
int syntax_check(char*str);
int	check_quotes(char *str);
int	check_extrems(char *str);

// CHECK UTILS
int	is_space(char c);
int	is_valid_metachar(char c);

// HANDLE ERROR
int handle_error(int error_type);

//SYNTAX CHECK 2
int	check_metachar_separate(char *str);
int do_check(char *str, int i);
int	check_pipe_separate(char *str, int i);
int	check_redir_separate(char *str, int i, char c);
int	do_redir_check(char *str,int i, char c);

#endif