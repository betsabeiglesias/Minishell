/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:28:52 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/09 19:34:27 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MACROS_H
# define MACROS_H

# define ERR_QUOTE		    0
# define ERR_EXTREM		    1
# define ERR_ALONE		    2
# define ERR_CONSECUTIVE    3
# define ERR_ENVP		    4
# define ERR_MALLOC		    5
# define ERR_ARG            6
# define ERR_ATTR           7
# define ERR_OPEN			8


# define ERR_MSG_QUOTE		    "SYNTAX ERROR: open quotes"
# define ERR_MSG_EXTREM		    "SYNTAX ERROR: nothing after or before metachar"
# define ERR_MSG_ALONE		    "SYNTAX ERROR: need separate metacharacter"
# define ERR_MSG_CONSECUTIVE    "SYNTAX ERROR: Consecutive metachar"
# define ERR_MSG_ENVP		    "ENVIRONMENT VARIABLE NOT FOUND OR UNDEFINED"
# define ERR_MSG_MALLOC		    "MALLOC FAILED"
# define ERR_MSG_ARG		    "ningun argumento"
# define ERR_MSG_ATTR           "UNABLE TO ACCESS TERMINAL ATTRIBUTES"
# define ERR_MSG_OPEN           "OPEN ERROR"

# define SINGLE_QUOTE		'\''
# define DOUBLE_QUOTE		'"'
# define SPACE				' '
# define PIPE				'|'
# define DOTS	            58
# define SLASH		        "/"
# define NEW_LINE            "\n"
# define EMPTY              ""
# define EXIT               "exit"
# define MINISHELL          "minishell> "

# define REDIR_OUT_S		">"
# define REDIR_OUT_D		">>"
# define REDIR_IN_S		    "<"
# define REDIR_IN_D		    "<<"

# define ACCESS 			0
# define OPEN_ERROR			-1
# define OPEN_MODE          0644
# define RD_END		        0
# define WR_END		        1
# define PATH		        "PATH="
# define HERE_DOC           "here_doc"

# define REDIR_SINGLE       0
# define REDIR_DOUBLE       1


/*este archivo he cambiado*/

#endif