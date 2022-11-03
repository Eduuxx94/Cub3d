/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 09:42:19 by ede-alme          #+#    #+#             */
/*   Updated: 2022/11/03 21:00:11 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_utils	utils(void)
{
	static t_utils	util = {
		ft_strncmp, ft_strisspace, ft_strlen, ft_strtrim, ft_strdup, ft_memcpy,
		ft_matrixdup, ft_matrixlen, ft_matrixfree, get_next_line
	};

	return (util);
}
