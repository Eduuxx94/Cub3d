/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 09:34:01 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/30 12:07:57 by ede-alme         ###   ########.fr       */
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
