/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwirtzbi <nwirtzbi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:57:07 by nwirtzbi          #+#    #+#             */
/*   Updated: 2025/11/28 12:05:20 by nwirtzbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*join_and_free(char *stash, char *buffer)
{
	char	*updated_stash;

	updated_stash = ft_strjoin(stash, buffer);
	if (!updated_stash)
	{
		free(stash);
		return (NULL);
	}
	free(stash);
	return (updated_stash);
}

static char	*read_and_update_stash(int fd, char *stash)
{
	ssize_t	bytes_read;
	char	*buffer;
	size_t	i;

	bytes_read = 1;
	buffer = malloc (BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	i = 0;
	while (i < BUFFER_SIZE + 1)
		buffer[i++] = 0;
	while (bytes_read > 0 && !has_newline(stash))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(stash);
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stash = join_and_free(stash, buffer);
	}
	free (buffer);
	return (stash);
}

static char	*extract_line(char *stash)
{
	size_t	index;

	index = 0;
	while (stash[index] && stash[index] != '\n')
		index++;
	if (stash[index] == '\n')
		return (ft_substr(stash, 0, index + 1));
	return (ft_strdup(stash));
}

static char	*update_stash(char *stash)
{
	size_t	index;
	char	*new_stash;

	index = 0;
	while (stash[index] && stash[index] != '\n')
		index++;
	if (!stash[index])
	{
		free (stash);
		return (NULL);
	}
	new_stash = ft_strdup(stash + index + 1);
	free (stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_and_update_stash(fd, stash);
	if (!stash)
		return (NULL);
	if (stash[0] == 0)
		return (free(stash), stash = NULL, NULL);
	line = extract_line(stash);
	if (!line)
		return (free(stash), stash = NULL, NULL);
	stash = update_stash(stash);
	if (stash && stash[0] == 0)
	{
		free(stash);
		stash = NULL;
	}
	return (line);
}

// int	main(void)
// {
// 	char	*line;
// 	int		fd;

// 	fd = open("test_empty.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (1);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// } 
