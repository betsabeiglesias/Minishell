/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:37:46 by beiglesi          #+#    #+#             */
/*   Updated: 2024/11/09 18:45:34 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

int	insert_expanded_var(char **input, t_varenv *var)
{
	int 	old_len;
	int		new_len;
	int		exp_var_len;
	char	*new_line;

	old_len = ft_strlen(*input);
	exp_var_len = ft_strlen(var->var_expanded);
	new_len = old_len - var->len + exp_var_len;
	new_line = malloc(sizeof(char) * (new_len + 1));
	if (new_line == NULL)
		return(handle_error(ERR_MALLOC), EXIT_FAILURE);
	ft_strlcpy(new_line, *input, var->start);
	if (var->var_expanded != NULL)
	{
		ft_strlcat(new_line, var->var_expanded, new_len + 1);
		ft_strlcat(new_line, (*input + var->start + var->len), new_len + 1);
	}
	else 
		ft_strlcat(new_line, (*input + var->start + var->len + 1), new_len + 1);
	clean_varen(var);
	free(*input);
	*input = new_line;
	return (EXIT_SUCCESS);
}	

int	len_var(char *input, int i)
{
	size_t	len;
	int		temp;

	temp = i;
	len = 0;
	while (!valid_char_env(input[temp]))
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
		new_quote_status(&s_quote, &d_quote, j, input);
		j++;
	}
	if (s_quote == true)
		return (false);
	return (true);
}

int	get_var_env(t_mini *shell, t_varenv *var)
{
	char	*var_name;
	char	**env_start;

	env_start = shell->env;
	var_name = malloc (sizeof(char) * (var->len + 2));
	if (!var_name)
		return (handle_error(ERR_MALLOC), EXIT_FAILURE);
	ft_strlcpy(var_name, var->value, var->len + 1);
	var_name[var->len] = '=';
	var_name[var->len + 1] = '\0';
	while (*shell->env != NULL)
	{
		if (!ft_strncmp(*shell->env, var_name, var->len))
		{
			var->var_expanded = (*shell->env + 1 + (var->len));
			free(var_name);
			shell->env = env_start;
			return (EXIT_SUCCESS); 
		}
		shell->env++;
	}
	shell->env = env_start;
	var->var_expanded = "";
	free(var_name);
	return (EXIT_SUCCESS);
}
