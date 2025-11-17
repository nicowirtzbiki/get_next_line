/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 20:28:15 by nico              #+#    #+#             */
/*   Updated: 2025/11/17 12:14:15 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *get_next_line(int fd)
{
    static char	*stash;          // Guarda o "resto" das leituras entre chamadas (memória persistente)
	char		buffer[BUFFER_SIZE + 1]; // Onde o read() escreve temporariamente
	ssize_t		bytes_read;      // Quantidade de bytes lidos pelo read()
	char		*newline_pos;    // Ponteiro para a posição do '\n' dentro do stash
	char		*tmp;            // Variável auxiliar para realocar e concatenar strings
	char		*line;           // Linha final que será retornada
	size_t		index;           // Índice numérico do '\n' dentro do stash

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
            break;
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
    //newline_pos = ft_strchr(stash, '\n');
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