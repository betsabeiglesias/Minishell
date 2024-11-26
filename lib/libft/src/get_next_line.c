/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aolabarr <aolabarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 11:58:55 by aolabarr          #+#    #+#             */
/*   Updated: 2024/04/07 13:09:33 by aolabarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free2(&backup), NULL);
	if (!backup || !ft_strchr(backup, '\n'))
		backup = read_file(fd, backup);
	if (!backup)
		return (NULL);
	line = extract_line(backup);
	if (!line)
		return (ft_free2(&backup), NULL);
	backup = save_rest(backup, ft_strlen(line));
	if (!backup)
		return (ft_free2(&line), NULL);
	return (line);
}

char	*read_file(int fd, char *bkup)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_read;

	bytes_read = 1;
	if (!bkup)
		bkup = ft_strdup("");
	if (!bkup)
		return (NULL);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (ft_free2(&bkup), NULL);
		buffer[bytes_read] = '\0';
		bkup = ft_strjoin_freed(bkup, buffer);
		if (!bkup)
			return (NULL);
		if (ft_strchr(bkup, '\n'))
			break ;
	}
	return (bkup);
}

char	*extract_line(char *aux)
{
	char	*newline;
	size_t	len;

	if (!aux || aux[0] == '\0')
		return (NULL);
	if (ft_strchr(aux, '\n'))
		len = ft_strlen(aux) - ft_strlen(ft_strchr(aux, '\n')) + 1;
	else
		len = ft_strlen(aux);
	newline = malloc((len + 1) * sizeof(char));
	if (!newline)
		return (NULL);
	ft_strlcpy(newline, aux, len + 1);
	newline[len] = '\0';
	return (newline);
}

char	*save_rest(char *aux, size_t len)
{
	char	*rest;

	rest = ft_strdup(aux + len);
	ft_free2(&aux);
	return (rest);
}
