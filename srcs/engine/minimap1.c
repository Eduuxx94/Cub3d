/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:29:11 by ede-alme          #+#    #+#             */
/*   Updated: 2022/12/27 18:37:22 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	render_minimap(t_eng *eng)
{
	render_bg(eng);
	render_map(0, -5, 0, -5);
	render_border(eng);
	render_player(eng);
	return (0);
}

int	is_map(t_eng *eng, int x, int y)
{
	int	ymax;
	int	xmax;

	if (x < 0 || y < 0)
		return (0);
	ymax = 0;
	while (eng->file->map[ymax])
		ymax++;
	if (y >= ymax)
		return (0);
	xmax = 0;
	while (eng->file->map && eng->file->map[y][xmax])
		xmax++;
	if (x >= xmax)
		return (0);
	return (1);
}
