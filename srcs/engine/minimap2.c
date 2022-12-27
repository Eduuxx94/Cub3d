/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:29:28 by ede-alme          #+#    #+#             */
/*   Updated: 2022/12/27 19:35:55 by ede-alme         ###   ########.fr       */
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
			if (i >= (y - 16) && j >= (x - 16))
				put_pixel_image(&eng->minimap, j, i, color);
			if (i < (y - 5) && i > (y - 11) && j < (x - 5) \
			&& j > (x - 11) && (color == 0xf1c40f || color == 0x00a300))
				put_pixel_image(&eng->minimap, j, i, 0x000000);
		}
	}
}

void	render_map(int y, int i, int x, int j)
{
	while (++y <= 9 && ++i + 50)
	{
		j = -5;
		x = 0;
		while (++x <= 9 && ++j + 50)
		{
			if (is_map(engine(), (int)engine()->player.posx + j, \
			(int)engine()->player.posy + i) && engine()->file->map[i + \
			(int)engine()->player.posy][j + (int)engine()->player.posx] == '1')
				render_block(engine(), x, y, 0x000000);
			else if (is_map(engine(), (int)engine()->player.posx + j, \
			(int)engine()->player.posy + i) && engine()->file->map[i + \
			(int)engine()->player.posy][j + (int)engine()->player.posx] == '0')
				render_block(engine(), x, y, 0x757575);
			else if (is_map(engine(), (int)engine()->player.posx + j, \
			(int)engine()->player.posy + i) && engine()->file->map[i + \
			(int)engine()->player.posy][j + (int)engine()->player.posx] == 'D')
				render_block(engine(), x, y, 0xf1c40f);
			else if (is_map(engine(), (int)engine()->player.posx + j, \
			(int)engine()->player.posy + i) && engine()->file->map[i + \
			(int)engine()->player.posy][j + (int)engine()->player.posx] == 'F')
				render_block(engine(), x, y, 0x00a300);
		}
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
