/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:50:32 by aolabarr          #+#    #+#             */
/*   Updated: 2024/12/20 17:05:09 by aolabarr         ###   ########.fr       */
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

# define ERR_MSG_QUOTE	"SYNTAX ERROR: open quotes"
# define ERR_MSG_EXTREM	"SYNTAX ERROR: nothing after or before metachar"
# define ERR_MSG_ALONE	"SYNTAX ERROR: need separate metacharacter"
# define ERR_MSG_CONSEC	"SYNTAX ERROR: consecutive metachar"
# define ERR_MSG_ENVP	"ENV ERROR: env. variable not found or undefined"
# define ERR_MSG_ENV	"ENV ERROR: initializing enviroment failed"
# define ERR_MSG_OLDPWD	"ENV ERROR: updating OLDPWD"
# define ERR_MSG_MALLOC	"SYS ERROR: malloc failed"
# define ERR_MSG_ATTR	"SYS ERROR: unable to access terminal attributes"
# define ERR_MSG_OPEN	"SYS ERROR: open failed"
# define ERR_MSG_CHDIR	"SYS ERROR: chdir failed"
# define ERR_MSG_FORK	"SYS ERROR: fork failed"
# define ERR_MSG_EXECVE	"SYS ERROR: execve failed"
# define ERR_MSG_PIPE	"SYS ERROR: pipe failed"
# define ERR_MSG_GETWD	"SYS ERROR: failed to get working directory"
# define ERR_MSG_ACCESS	"ERROR: command not found"
# define ERR_MSG_BUILT	"ERROR: built failed"
# define ERR_MSG_EXPORT	"ERROR: export failed"
# define ERR_MSG_HERE	"ERROR: deleting here_doc failed"
# define ERR_MSG_EOF	"WAR: here-doc delimited by EOF (wanted 'delimiter')"

# define SINGLE_QUOTE		39
# define DOUBLE_QUOTE		34
# define SPA_C			    32
# define POINT              46
# define PIPE				124
# define DOTS	            58
# define SLASH		        "/"
# define SLASH_CHAR		    47
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