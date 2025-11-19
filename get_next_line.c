/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 09:57:07 by nico              #+#    #+#             */
/*   Updated: 2025/11/19 09:16:22 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *read_and_update_stash(int fd, char *buffer, char *stash)
{
    size_t  bytes_read;
    char    *tmp;

    bytes_read = 1;
    while (bytes_read > 0 && (!stash || !ft_strchr(stash, '\n')))
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0)
            return (stash);
        buffer[bytes_read] = '\0';
        //juntar buffer no stash
        if (!stash)
        {
            stash = ft_strdup(buffer);
        }
        else
        {
            tmp = ft_strjoin(stash, buffer);
            free (stash);
            stash = tmp;
        }
    }
    return (stash);
}
char    *extract_line(char  *stash)
{
    size_t  index;

    index = 0;
    while (stash[index] && stash[index] != '\n')
        index++;
    if (stash[index] == '\n')
        return (ft_substr(stash, 0, index + 1));
    return (ft_strdup(stash));
}
char    *update_stash(char *stash)
{
    size_t  index;
    char    *new_stash;

    index = 0;
    while(stash[index] && stash[index] != '\n')
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

char    *get_next_line(int fd)
{
    static char *stash;
    char        *buffer;
    char        *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    buffer = malloc (BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);

    stash = read_and_update_stash(fd, buffer, stash);
    free(buffer);
    if (!stash)
        return (NULL);
    line = extract_line(stash);
    stash = update_stash(stash);
    return (line);
}