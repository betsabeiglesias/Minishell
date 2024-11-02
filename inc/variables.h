/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:38:42 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/02 18:04:25 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_H
# define VARIABLES_H

typedef struct s_exe_list
{
	char	**env;
	char	*cmd;
	char	**cmd_all;
	char	*path;
	int		fd_in;
	int		fd_out;
}				t_exe_list;

typedef struct	s_mini
{
   char		**env;
   bool		oldpwd;
   char		*input;
}				t_mini;

typedef struct s_varenv
{
	char	*value;
	char	*var_expanded;
	int		start;
	int		len;
}				t_varenv;

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

/*
typedef struct s_token
{
   t_token_type     type;
   char             *cmd;
   char             **cmd_av;
   char             *str;
   struct t_token   *next;
   struct t_token   *prev;
}				t_token;
*/
#endif