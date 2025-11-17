/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 20:28:15 by nico              #+#    #+#             */
/*   Updated: 2025/11/17 12:29:02 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		bytes_read;
	char		*newline_pos;
	char		*tmp;
	char		*line;
	size_t		index;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	newline_pos = NULL;
	bytes_read = 1;
	while (!newline_pos && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			if (stash)
				free (stash);
			stash = NULL;
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!stash)
			stash = ft_strdup(buffer);
		else
		{
			tmp = ft_strjoin(stash, buffer);
			free(stash);
			stash = tmp;
		}
		newline_pos = ft_strchr(stash, '\n');
	}
	if (!stash || stash[0] == '\0')
		return (NULL);
	if (newline_pos)
	{
		index = (size_t)(newline_pos - stash);
		line = ft_substr(stash, 0, index + 1);
		tmp = ft_strdup(stash + index + 1);
		free (stash);
		stash = tmp;
		return (line);
	}
	line = stash;
	stash = NULL;
	return (line);
}
