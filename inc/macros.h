/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:28:52 by aolabarr          #+#    #+#             */
/*   Updated: 2024/12/18 19:53:40 by binary           ###   ########.fr       */
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
# define ERR_ACCESS			9
# define ERR_FORK			10
# define ERR_EXECVE         11
# define ERR_WAIT           12
# define ERR_PIPE           13
# define ERR_BUILT			14
# define ERR_EXPORT			15
# define ERR_CHDIR			16
# define ERR_HERE			17
# define ERR_GETWD			18
# define ERR_OLDPWD			19
# define ERR_EOF            20
# define ERR_ENV			21

# define ERR_MSG_QUOTE		    "SYNTAX ERROR: open quotes"
# define ERR_MSG_EXTREM		    "SYNTAX ERROR: nothing after or before metachar"
# define ERR_MSG_ALONE		    "SYNTAX ERROR: need separate metacharacter"
# define ERR_MSG_CONSECUTIVE    "SYNTAX ERROR: Consecutive metachar"
# define ERR_MSG_ENVP		    "ENVIRONMENT VARIABLE NOT FOUND OR UNDEFINED"
# define ERR_MSG_MALLOC		    "MALLOC FAILED"
# define ERR_MSG_ARG		    "ningun argumento"
# define ERR_MSG_ATTR           "UNABLE TO ACCESS TERMINAL ATTRIBUTES"
# define ERR_MSG_OPEN           "OPEN ERROR"
# define ERR_MSG_ACCESS			"COMMAND NOT FOUND"
# define ERR_MSG_FORK			"FAILED FORK"
# define ERR_MSG_EXECVE			"FAILED EXECVE"
# define ERR_MSG_PIPE			"FAILED PIPE"
# define ERR_MSG_BUILT			"FAILED BUILT"
# define ERR_MSG_EXPORT			"FAILED EXPORT"
# define ERR_MSG_CHDIR			"ERROR CHDIR"
# define ERR_MSG_HERE			"Error deleting here_doc"
# define ERR_MSG_GETWD			"FAILED TO GET WORKING DIRECTORY"
# define ERR_MSG_OLDPWD			"Error updating OLDPWD"
# define ERR_MSG_EOF			"Warning: here-document deilimited by end-of-file (wanted 'delimiter')"
# define ERR_MSG_ENV			"ERROR INITIALIZING ENVIRONMENT"


# define SINGLE_QUOTE		'\''
# define DOUBLE_QUOTE		'"'
# define SPACE				' '
# define POINT              '.'
# define PIPE				'|'
# define DOTS	            58
# define SLASH		        "/"
# define SLASH_CHAR		    '/'
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
# define HERE_DOC_DIR       "./here_doc"
# define ERROR			    -1

# define REDIR_SINGLE       0
# define REDIR_DOUBLE       1

# define CD					"cd"
# define PWD				"pwd"
# define EXPORT				"export"
# define UNSET				"unset"
# define ENV				"env"
# define EXIT				"exit"


#endif