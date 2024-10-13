/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:13:15 by aolabarr          #+#    #+#             */
/*   Updated: 2024/10/13 15:05:48 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef enum    e_token_type
{
    CMD,
    PIPE,
    DQ_STR,
    SQ_STR,
    RDS_IN,
    RDS_OUT,
    RDD_IN,
    RDD_OUT,
    EXIT_CODE,
    NO_TYPE
}				t_token_type;


typedef struct s_token
{
   t_token_type  type;
   char         *cmd;
   char			**cmd_av;
   char			*str;
   t_token      *next;
   t_token      *prev;
}				t_token;

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# include "../lib/libft/src/libft.h"
# include "../lib/liblst/liblst.h"

# include "parse.h"
# include "prompt.h"

#endif