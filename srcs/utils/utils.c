/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 09:42:19 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/30 17:28:18 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
//teste
int		ft_strisspace(const char *str);

t_utils	utils(void)
{
	static t_utils	util = {
		ft_strisspace, ft_strlen, ft_strtrim, ft_strdup, ft_memcpy,
		ft_matrixdup, ft_matrixlen, ft_matrixfree
	};

	return (util);
}
