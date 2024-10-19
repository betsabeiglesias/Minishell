/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:36:24 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/19 13:38:40 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <stddef.h>
# include <limits.h>


typedef struct s_mini{
    char        **env;
	bool		oldpwd;
}               t_mini;


typedef struct s_varenv{
	char	*ant;
	char	*post;
	char	*pointer;
}				t_varenv;


char	*prompt(void);

char	*expand_varenv(char *str, t_mini *mini);
bool	has_dollar(char *cmd_line, t_varenv *var, int *i);
bool	is_expansible(char *cmd_line, int *i);
char	*find_varposition(char *cmd_line, int *i);
void	trim_toexpand(char *cmd_line, t_varenv *var, int *i);
int		len_var(char *cmd_line, int *i);


void	builtin_echo(char **cmd);
void	builtin_pwd(void);
int		builtin_cd(char **cmd);
#endif