/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 09:34:01 by ede-alme          #+#    #+#             */
/*   Updated: 2022/11/30 18:14:03 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*instr;
	unsigned char	*outstr;

	i = 0;
	instr = (unsigned char *)src;
	outstr = (unsigned char *)dest;
	while (n > 0)
	{
		outstr[i] = instr[i];
		i++;
		n--;
	}
	return (outstr);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*a;

	a = (unsigned char *)s;
	while (n--)
	{
		*a++ = (unsigned char)c;
	}
	return (s);
}
