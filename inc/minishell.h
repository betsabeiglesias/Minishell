/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:05:15 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/02 17:42:49 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define _POSIX_C_SOURCE 200809L

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stddef.h>
# include <limits.h>

# include "../lib/libft/src/libft.h"
# include "../lib/liblst/liblst.h"

typedef struct	s_mini
{
   char		**env;
   bool		oldpwd;
   char		*input;
}				t_mini;

# include "parse.h"
# include "prompt.h"


// INIT_DATA
void    init_shell(t_mini *shell);




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