/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:31:32 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/19 21:09:01 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	render_minimap(t_eng *eng)
{
	render_bg(eng);
	render_map(eng);
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
