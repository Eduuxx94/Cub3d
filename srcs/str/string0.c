/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 22:11:31 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/26 22:13:00 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
