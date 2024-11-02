/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:36:24 by beiglesi          #+#    #+#             */
/*   Updated: 2024/11/02 16:23:02 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <stddef.h>
# include <limits.h>


typedef struct s_varenv
{
	char	*value;
	char	*var_expanded;
	int		start;
	int		len;
}				t_varenv;


//char	*expand_varenv(char *str, t_mini *mini);

// SIGNALS
void	setup_signal_handlers(void);
void	handle_signal_interactive(int signum);
void	handle_eof_interactive(char *str);

//EXPANSION
char	*do_expansion(t_mini *shell);
void	init_varen (t_varenv *var, char *cmd_line, int i);
void	insert_expanded_var (char **cmd_line, t_varenv *var);
int		len_var(char *cmd_line, int i);

//EXPANSION PREP
bool	is_expansible(char *cmd_line, int i);
void	get_var_env(t_mini *mini, t_varenv *var);
void	clean_varen (t_varenv *var);

// ENVIROMENT
int		init_env(char **envp, t_mini *mini);
int		get_my_env(char **envp, t_mini *mini);
void	free_env(t_mini *mini);
void	free_mini(t_mini *mini);


void	builtin_echo(char **cmd);
void	builtin_pwd(void);
int		builtin_cd(char **cmd);
void	builtin_env(char **cmd, t_mini *mini);
#endif