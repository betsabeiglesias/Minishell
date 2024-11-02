/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:36:24 by beiglesi          #+#    #+#             */
/*   Updated: 2024/11/02 18:08:36 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

//AUX
int    ft_print_lst(t_list *list);

// CHECK SYNTAX 1
int		syntax_check(char*str);
int		check_quotes(char *str);
int		check_extrems(char *str);

// CHECK UTILS
int		is_space(char c);
int		is_valid_metachar(char c);
int		is_str_space(char *str);

// HANDLE ERROR
int		handle_error(int error_type);

//PARSE
t_list	*parse(t_mini *shell);

//SYNTAX CHECK 2
int		check_metachar_separate(char *str);
int		do_check(char *str, int i);
int		check_pipe_separate(char *str, int i);
int		check_redir_separate(char *str, int i, char c);
int		do_redir_check(char *str,int i, char c);

//TOKENIZATION_1
t_list	*tokenization(char *str);
void	init_var_parse(t_varparse *data);
void	handle_quote(t_varparse *data, char *str, char quote);
void	handle_char(t_varparse *data, char *str);
char	*handle_token(t_varparse *data, char *str);

//TOKENIZATION_2
char	*save_token(t_varparse *data);
char	*handle_final_token(t_varparse *data);
char	*add_literal_str(char *dst, char *str, char quote);
char	*ft_add_char_freed(char *str, char const c);

//FREE
void	lst_clear_token_content(t_list *lst);

// SIGNALS
void	setup_signal_handlers(void);
void	handle_signal_interactive(int signum);
void	handle_eof_interactive(char *str);

//EXPANSION
char	*do_expansion(t_mini *shell);
void	init_varen (t_varenv *var, char *cmd_line, int i);
void	clean_varen (t_varenv *var);
int		len_var(char *cmd_line, int i);

//EXPANSION PREP
void	insert_expanded_var (char **cmd_line, t_varenv *var);
bool	is_expansible(char *cmd_line, int i);
int		len_var(char *cmd_line, int i);
void	get_var_env(t_mini *mini, t_varenv *var);

// ENVIROMENT
int		init_env(char **envp, t_mini *mini);
int		get_my_env(char **envp, t_mini *mini);
void	free_env(t_mini *mini);
void	free_mini(t_mini *mini);

// BUILT INS (en archivos separados)
void	builtin_echo(char **cmd);
void	builtin_pwd(void);
int		builtin_cd(char **cmd);
void	builtin_env(char **cmd, t_mini *mini);

// INIT_DATA
void    init_shell(t_mini *shell);

#endif