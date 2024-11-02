/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:38:42 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/02 17:25:55 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_exe_list
{
	char	**env;
	char	*cmd;
	char	**cmd_all;
	char	*path;
	int		fd_in;
	int		fd_out;
}				t_exe_list;

#endif