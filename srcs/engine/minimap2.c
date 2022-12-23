/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:26:38 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/19 21:19:49 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	render_block(t_eng *eng, int x, int y, int color)
{
	int	i;
	int	j;

	x = x * 16;
	y = y * 16;
	i = -1;
	while (++i < y)
	{
		j = -1;
		while (++j < x)
		{
			if (i >= (y - 16) && j >= (x - 16) && color == 0xf1c40f)
				put_pixel_image(&eng->minimap, j, i, color);
			if (i < (y - 6) && i > (y - 10) && j < (x - 6) \
			&& j > (x - 10) && color == 0xf1c40f)
				put_pixel_image(&eng->minimap, j, i, 0x000000);
			if (i >= (y - 16) && j >= (x - 16) && color != 0xf1c40f)
				put_pixel_image(&eng->minimap, j, i, color);
		}
	}
}

void	render_map(t_eng *eng)
{
	int	x;
	int	y;
	int	i;
	int	j;

	y = 0;
	i = -4;
	while (++y <= 9)
	{
		x = 0;
		j = -4;
		while (++x <= 9)
		{
			if (is_map(eng, (int)eng->player.posx + j, \
			(int)eng->player.posy + i) && eng->file->map \
			[i + (int)eng->player.posy][j + (int)eng->player.posx] == '1')
				render_block(eng, x, y, 0x000000);
			else if (is_map(eng, (int)eng->player.posx + j, \
			(int)eng->player.posy + i) && eng->file->map \
			[i + (int)eng->player.posy][j + (int)eng->player.posx] == '0')
				render_block(eng, x, y, 0x757575);
			else if (is_map(eng, (int)eng->player.posx + j, \
			(int)eng->player.posy + i) && eng->file->map \
			[i + (int)eng->player.posy][j + (int)eng->player.posx] == 'D')
				render_block(eng, x, y, 0xf1c40f);
			j++;
		}
		i++;
	}
}

void	render_player(t_eng *eng)
{
	int	x;
	int	y;

	y = -1;
	while (++y < 144)
	{
		x = -1;
		while (++x < 144)
		{
			if (((x - 71) * (x - 72)) + ((y - 71) * (y - 72)) < 48)
				put_pixel_image(&eng->minimap, y, x, 0x000000);
			if (((x - 71) * (x - 72)) + ((y - 71) * (y - 72)) < 32)
				put_pixel_image(&eng->minimap, y, x, 0xff0000);
		}
	}
}

void	render_bg(t_eng *eng)
{
	int	x;
	int	y;

	y = -1;
	while (++y <= 144)
	{
		x = -1;
		while (++x <= 144)
			put_pixel_image(&eng->minimap, y, x, 0x000000);
	}
}

void	render_border(t_eng *eng)
{
	int	x;
	int	y;

	y = -1;
	while (++y <= 144)
	{
		x = -1;
		while (++x <= 144)
		{
			if (x < 1 || x > 142 || y < 1 || y > 142)
				put_pixel_image(&eng->minimap, y, x, 0x000000);
		}
	}
}
