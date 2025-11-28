/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nwirtzbi <nwirtzbi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 20:29:43 by nwirtzbi          #+#    #+#             */
/*   Updated: 2025/11/28 09:43:52 by nwirtzbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h> // for read, close
# include <stdlib.h> // for malloc, free
# include <fcntl.h>  // for open
# include <stdio.h>  // for printf (testing purposes)
# include <limits.h> // OPEN_MAX
// Define um valor padrão se o BUFFER_SIZE não for passado na compilação
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	has_newline(char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
#endif
