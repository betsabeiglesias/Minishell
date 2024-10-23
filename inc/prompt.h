/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:36:24 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/23 12:02:43 by beiglesi         ###   ########.fr       */
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
	char	*value;
	char	*post;
	char	*pointer;
}				t_varenv;


char	*prompt(void);

char	*expand_varenv(char *str, t_mini *mini);
bool	has_dollar(char *cmd_line, t_varenv *var, int *i);
bool	is_expansible(char *cmd_line, int *i);
char	*find_value_position(char *cmd_line, int *i);
void	trim_to_expand(char *cmd_line, t_varenv *var, int *i);
char	*expanded_cmd_line(t_varenv *var, t_mini *mini);
int		len_var(char *cmd_line);
char	*get_var_env(t_mini *mini, t_varenv *var);
char	*do_expansion(char *cmd_line, t_mini *mini);

char	**get_my_env(char **envp, t_mini *mini);

void	builtin_echo(char **cmd);
void	builtin_pwd(void);
int		builtin_cd(char **cmd);
void	builtin_env(char **cmd, t_mini *mini);
#endif