/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binary <binary@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/16 16:11:34 by binary           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

int    init_shell(t_mini *shell, char **envp, char **envp)
{
	shell->env = NULL;
	shell->input = NULL;
	shell->oldpwd = true;
	shell->all_paths = NULL;
	shell->pid = NULL;
	shell->pipes = NULL;
	shell->num_pipes = 0;
	if(get_my_env(envp, shell))
		return(handle_error(ERR_ENVP), EXIT_FAILURE);
	if (get_all_paths(shell))
		return(EXIT_FAILURE);
	if(get_my_env(envp, shell))
		return(handle_error(ERR_ENVP), EXIT_FAILURE);
	if (get_all_paths(shell))
		return(EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_all_paths(t_mini *shell)
{
	size_t	i;
	int		get;
	char	**paths;

	if (!shell->env)
		return (EXIT_FAILURE);
	i = 0;
	get = 0;
	while (i < ft_matsize(shell->env) && get == 0)
	{
		if (!ft_strncmp(shell->env[i], PATH, ft_strlen(PATH)))
		{
			paths = ft_split(shell->env[i] + ft_strlen(PATH), DOTS);
			if (!paths)
				return(handle_error(ERR_MALLOC), EXIT_FAILURE);
			get = 1;
		}
		i++;
	}
	shell->all_paths = paths;
	return (EXIT_SUCCESS);
}

t_exec *init_cmd_node(void)
{
	t_exec *node;

	node = malloc(sizeof(t_exec));
	if (!node)
		return (handle_error(ERR_MALLOC), NULL);
	node->cmd_all = NULL;
	node->path = NULL;
	node->filename_in = NULL;
	node->filename_out = NULL;
	node->out_append = 0;
	node->heredoc_content = NULL;
	return (node);
}

int	**ft_malloc_mat_int(int x, int y, int size)
{
	int	**map;
	int	i;

	map = malloc(sizeof(void *) * x);
	if (!map)
		return (NULL);
	i = 0;
	while (i < x)
	{
		map[i] = malloc(size * y);
		if (!map[i])
			return (ft_free_mat_int(map, i), NULL);
		i++;
	}
	return (map);
}
