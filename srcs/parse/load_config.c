/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:25:52 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/28 10:55:50 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	ft_start_parse(t_file *file, char *file_path)
{
	if (ft_file_init(file, file_path) || ft_file_load_tiles(file))
		return (1);
	if (0)
		return (1);
	return (0);
}
