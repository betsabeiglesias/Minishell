/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:36:24 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/28 14:57:32 by binary           ###   ########.fr       */
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
	char	*value;
	char	*var_expanded;
	int		start;
	int		len;
}				t_varenv;

// typedef struct s_varenv{
// 	char	*value;
// 	char	*pointer;
// 	char	*ant;
// 	char	*post;
// }				t_varenv;


char	*prompt(void);

char	*expand_varenv(char *str, t_mini *mini);
bool	has_dollar(char *cmd_line, t_varenv *var, int *i);



// version 1
// bool	is_expansible(char *cmd_line, int *i);
// char	*find_value_position(char *cmd_line, int *i);
// void	trim_to_expand(char *cmd_line, t_varenv *var, int *i);
// char	*expanded_cmd_line(t_varenv *var, t_mini *mini);
// char	*do_expansion(char *cmd_line, t_mini *mini);
// char	*get_var_env(t_mini *mini, t_varenv *var);
// int		len_var(char *cmd_line);


// version 2
void	insert_expanded_var (char **cmd_line, t_varenv *var);
char	*do_expansion(char **cmd_line, t_mini *mini);
void	init_varen (t_varenv *var, char *cmd_line, int i);
bool	is_expansible(char *cmd_line, int i);
void	get_var_env(t_mini *mini, t_varenv *var);
int		len_var(char *cmd_line, int i);
void	clean_varen (t_varenv *var);



char	**get_my_env(char **envp, t_mini *mini);
void	free_env(t_mini *mini);
void	free_mini(t_mini *mini);

void	builtin_echo(char **cmd);
void	builtin_pwd(void);
int		builtin_cd(char **cmd);
void	builtin_env(char **cmd, t_mini *mini);
#endif