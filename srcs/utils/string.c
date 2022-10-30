/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 22:11:31 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/30 09:36:24 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_strisspace(const char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str != '\f' && *str != '\n' && *str != '\r' && *str != '\t'\
			&& *str != '\v' && *str != ' ')
			return (0);
		str++;
	}
	return (1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strtrim(const char *str)
{
	int		size;
	int		i;
	char	*out;

	out = NULL;
	if (!str)
		return (NULL);
	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;
	i = -1;
	size = 0;
	while (str[++i])
		size++;
	while (i > 0 && (str[--i] == ' ' || str[i] == '\t' || str[i] == '\n'))
		size--;
	out = malloc(sizeof(char) * (size + 1));
	if (!out)
		return (NULL);
	out[size] = 0;
	while (--size >= 0)
		out[size] = str[i--];
	return (out);
}

char	*ft_strdup(const char *s)
{
	char	*new;
	int		size;

	size = 0;
	while (s[size] != '\0')
		size++;
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	while (size >= 0)
	{
		new[size] = s[size];
		size--;
	}
	return (new);
}
