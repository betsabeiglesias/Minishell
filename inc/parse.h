/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:56:16 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/01 16:32:09 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef struct	s_quote
{
    bool	sing;
    bool	doub;
}				t_quote;

typedef struct	s_varparse
{
    t_list	*tk_lst;
	char	*tmp;
    int		i;
	int		old_len;
}				t_varparse;

# define ERR_QUOTE		0
# define ERR_EXTREM		1
# define ERR_ALONE		2
# define ERR_ENVP		3
# define ERR_MALLOC		4

# define ERR_MSG_QUOTE		"SYNTAX ERROR: open quotes"
# define ERR_MSG_EXTREM		"SYNTAX ERROR: nothing after or before metachar"
# define ERR_MSG_ALONE		"SYNTAX ERROR: need separate metacharacter"
# define ERR_MSG_ENVP		"ENVIRONMENT VARIABLE NOT FOUND OR UNDEFINED"
# define ERR_MSG_MALLOC		"MALLOC FAILED"

# define SINGLE_QUOTE		'\''
# define DOUBLE_QUOTE		'"'
# define SPACE				' '
# define NO_NULL			"no_null"

//MAIN
int    ft_print_lst(t_list *list);

// CHECK SYNTAX 1
int		syntax_check(char*str);
int		check_quotes(char *str);
int		check_extrems(char *str);

// CHECK UTILS
int		is_space(char c);
int		is_valid_metachar(char c);
int		is_str_space(char *str);

// HANDLE ERROR
int		handle_error(int error_type);

//PARSE
void	*parse(char *str);

//SYNTAX CHECK 2
int		check_metachar_separate(char *str);
int		do_check(char *str, int i);
int		check_pipe_separate(char *str, int i);
int		check_redir_separate(char *str, int i, char c);
int		do_redir_check(char *str,int i, char c);

//TOKENIZATION_1
t_list	*tokenization(char *str);
void	init_var_parse(t_varparse *data);
void	handle_quote(t_varparse *data, char *str, char quote);
void	handle_char(t_varparse *data, char *str);
char	*handle_token(t_varparse *data, char *str);

//TOKENIZATION_2
char	*save_token(t_varparse *data, char *str);
char	*handle_final_token(t_varparse *data);
char	*add_literal_str(char *dst, char *str, char quote);
char	*ft_add_char_freed(char *str, char const c);

//FREE
void	lst_clear_token_content(t_list *lst);

#endif