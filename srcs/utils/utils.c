/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 09:42:19 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/30 12:13:15 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
//teste
int		ft_strisspace(const char *str);

t_utils	util(void)
{
	static t_utils	util = {
		ft_strisspace, ft_strlen, ft_strtrim, ft_strdup, ft_memcpy,
		ft_matrixdup, ft_matrixlen
	};

	return (util);
}
