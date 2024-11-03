/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:28:52 by aolabarr          #+#    #+#             */
/*   Updated: 2024/11/03 13:29:04 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define ERR_QUOTE		0
# define ERR_EXTREM		1
# define ERR_ALONE		2
# define ERR_ENVP		3
# define ERR_MALLOC		4
# define ERR_ARG        5

# define ERR_MSG_QUOTE		"SYNTAX ERROR: open quotes"
# define ERR_MSG_EXTREM		"SYNTAX ERROR: nothing after or before metachar"
# define ERR_MSG_ALONE		"SYNTAX ERROR: need separate metacharacter"
# define ERR_MSG_ENVP		"ENVIRONMENT VARIABLE NOT FOUND OR UNDEFINED"
# define ERR_MSG_MALLOC		"MALLOC FAILED"
# define ERR_MSG_ARG		"ningun argumento"

# define SINGLE_QUOTE		'\''
# define DOUBLE_QUOTE		'"'
# define SPACE				' '
# define NEW_LINE            "\n"
# define NO_NULL			"no_null"
# define EMPTY              ""
# define EXIT               "exit"
# define MINISHELL          "minishell> "

#endif