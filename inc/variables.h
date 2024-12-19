/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:30:14 by aolabarr          #+#    #+#             */
/*   Updated: 2024/12/19 19:32:31 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_H
# define VARIABLES_H

extern int	g_status;

typedef struct s_exec
{
	char	**cmd_all;
	char	*path;
	char	*filename_in;
	char	*filename_out;
	int		out_append;
	char	*hdoc_content;
}				t_exec;

typedef struct s_mini
{
	char	**env;
	char	**all_paths;
	bool	oldpwd;
	char	*input;
	//char		*delimiter; BORRAR
	pid_t	*pid;
	int		**pipes;
	int		num_pipes;
	int		is_redir;
	int		exit_status;
}				t_mini;

typedef struct s_varenv
{
	char	*value;
	char	*var_expanded;
	int		start;
	int		len;
}				t_varenv;

typedef struct s_quote
{
	bool	sing;
	bool	doub;
}				t_quote;

typedef struct s_varparse
{
	t_list	*tk_lst;
	char	*tmp;
	int		i;
	int		old_len;
}				t_varparse;

typedef struct s_fd
{
	int		in;
	int		out;
}				t_fd;

#endif
