/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nico <nico@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 21:40:25 by nico              #+#    #+#             */
/*   Updated: 2025/11/27 22:39:35 by nico             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	if (!str || *str == 0)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	len1;
	size_t	len2;
	size_t	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	newstr = malloc((len1 + len2 + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		newstr[i] = s1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		newstr[i] = s2[i - len1];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

size_t	has_newline(char *str)
{
	size_t len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
	{
		if (str[len] == '\n')
			return (1);
		len++;
	}
	return (0);
}

char	*ft_strdup(const char *s1)
{
	char	*strcopy;
	int		i;
	int		len;

	len = ft_strlen(s1);
	strcopy = malloc((len + 1) * sizeof(char));
	if (!strcopy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		strcopy[i] = s1[i];
		i++;
	}
	strcopy[i] = '\0';
	return (strcopy);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	if (!s || ft_strlen(s) <= start)
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}