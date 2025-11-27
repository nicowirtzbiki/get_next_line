/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:55:40 by nico              #+#    #+#             */
/*   Updated: 2025/11/27 22:33:07 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*join_and_free(char *stash, char *buffer)
{
	char *updated_stash;

	updated_stash = ft_strjoin(stash, buffer);
	if (!updated_stash)
	{
		free(stash);
		return (NULL);
	}
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
	while (i <= BUFFER_SIZE)
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
	static char	*stash[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_and_update_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = extract_line(stash[fd]);
	if (!line)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = update_stash(stash[fd]);
	if (stash[fd] && stash[fd][0] == 0)
	{
		free(stash[fd]);
		stash[fd] = NULL;
	}
	return (line);
}


int	main(void)
{
	char	*line1;
	char	*line2;
	int		fd1 = open("test_file.txt", O_RDONLY);
	int		fd2 = open("test_file2.txt", O_RDONLY);

	if (fd1 < 0 || fd2 < 0)
    {
		printf("Erro ao abrir ficheiros!");
		return (1);
    }
	line1 = get_next_line(fd1);
	line2 = get_next_line(fd2);
	while (line1 || line2)
	{
		printf("%s", line1);
		printf("%s", line2);
		free(line1);
		free(line2);
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
	}
	close(fd1);
	close(fd2);
	return (0);
} 