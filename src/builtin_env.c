/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beiglesi <beiglesi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:53:50 by beiglesi          #+#    #+#             */
/*   Updated: 2024/10/23 11:14:28 by beiglesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

void	builtin_env(char **cmd, t_mini *mini)
{
	if(ft_strncmp(cmd[1], "env", ft_strlen("env")))
	{
		while(mini->env[i])
		{
			ft_putstr_fd(mini->env[i], STDOUT_FILENO);
			i++;
		}
	}

}

int	main(int argc, char **argv, t_mini *mini)
{
	if(argc < 2)
		printf("Incorrect number of arguments\n");
	else
	mini->env = get_my_env(envp, mini);
	builtin_env(argv[1], mini);
	return (0);
}