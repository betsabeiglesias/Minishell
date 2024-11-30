/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:30:14 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/30 10:59:29 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_H
# define VARIABLES_H

typedef struct s_exec
{
	char	**cmd_all;
	char	*path;
	char	*filename_in;
	char	*filename_out;
	int		out_append;
	char	*heredoc_content;
}				t_exec;

typedef struct	s_mini
{
   char		**env;
   char		**all_paths;
   char		**paths;
   bool		oldpwd;
   char		*input;
   char		*delimiter;
   pid_t	*pid;
   int		**pipes;
   int		num_pipes;
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

#endif