/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:37:46 by beiglesi          #+#    #+#             */
/*   Updated: 2024/11/06 13:45:14 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

void	insert_expanded_var(char **cmd_line, t_varenv *var)
{
	int 	old_len;
	int		new_len;
	int		exp_var_len;
	char	*new_line;

	old_len = ft_strlen(*cmd_line);
	if(!var->var_expanded)
		exp_var_len = 0;
	else 
		exp_var_len = ft_strlen(var->var_expanded);
	new_len = old_len - var->len + exp_var_len;
	new_line = malloc(sizeof(char) * (new_len + 1));
	if (new_line == NULL)
		return ;
	ft_strlcpy(new_line, *cmd_line, var->start);
	if (var->var_expanded != NULL)
	{
		ft_strlcat(new_line, var->var_expanded, new_len + 1);
		ft_strlcat(new_line, (*cmd_line + var->start + var->len), new_len + 1);
	}
	else 
		ft_strlcat(new_line, (*cmd_line + var->start + var->len + 1), new_len + 1);
	clean_varen(var);
	free(*cmd_line);
	*cmd_line = new_line;
}	

int	len_var(char *cmd_line, int i)
{
	size_t	len;
	int		temp;

	temp = i;
	len = 0;
	while (!valid_char_env(cmd_line[temp]))
	{
		len++;
		temp++;
	}
	return (len);
}

int	valid_char_env(char c)
{
	if(ft_isalnum(c) || c == '_')
		return(0);
	return(1);
}

bool	is_expansible(char *input, int i)
{
	int		temp;
	int		j;
	bool	s_quote;
	bool	d_quote;
	
	temp = i ;
	s_quote = false;
	d_quote = false;
	j = 0;
	while (j < temp)
	{
		if (input[j] == SINGLE_QUOTE && s_quote == false)
			s_quote = true;
		else if (input[j] == SINGLE_QUOTE && s_quote == true)
			s_quote = false;
		else if (input[j] == DOUBLE_QUOTE && d_quote == false)
			d_quote = true;
		else if (input[j] == DOUBLE_QUOTE && d_quote == true)
			d_quote = false;
		j++;
	}
	if (d_quote == true && s_quote == true)
	{
		while (input[j] != '\0')
		{
			if (input[j] == SINGLE_QUOTE)
				return (false);
			j++;
		}
	}
	else if (d.quote == false && s.quote == true)
	{
		while (input[j] != '\0')
		{
			if (input[j] == SINGLE_QUOTE)
				return (false);
			j++;
		}
	}
	else
		return (true);
}

void	get_var_env(t_mini *mini, t_varenv *var)
{
	char	*var_name;
	char	**env_start;

	env_start = mini->env;
	var_name = malloc (sizeof(char) * (var->len + 2));
	if (!var_name)
		return	;
	ft_strlcpy(var_name, var->value, var->len + 1);
	var_name[var->len] = '=';
	var_name[var->len + 1] = '\0';
	while (*mini->env != NULL)
	{
		if (!ft_strncmp(*mini->env, var_name, var->len))
		{
			var->var_expanded = (*mini->env + 1 + (var->len));
			free(var_name);
			mini->env = env_start;
			return ; 
		}
		mini->env++;
	}
	mini->env = env_start;
	free(var_name);
}
