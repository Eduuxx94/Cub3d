/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:34:37 by ede-alme          #+#    #+#             */
/*   Updated: 2022/12/23 21:24:20 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	get_anim_id(t_eng *eng)
{
	if (!eng->shot.id)
		return (0);
	if (eng->world.world_time - eng->shot.timer < 30000)
		return (eng->shot.id);
	if (eng->shot.id == 1)
	{
		eng->shot.timer = eng->world.world_time;
		eng->shot.id++;
	}
	else if (eng->shot.id == 2)
	{
		eng->shot.timer = eng->world.world_time;
		eng->shot.id++;
	}
	else if (eng->shot.id == 3)
	{
		eng->shot.timer = eng->world.world_time;
		eng->shot.id++;
	}
	else if (eng->shot.id == 4)
	{
		eng->shot.timer = eng->world.world_time;
		eng->shot.id++;
	}
	else if (eng->shot.id == 5)
	{
		eng->shot.timer = eng->world.world_time;
		eng->shot.id++;
	}
	else if (eng->shot.id == 6)
	{
		eng->shot.timer = eng->world.world_time;
		eng->shot.id++;
	}
	else if (eng->shot.id == 7)
	{
		eng->shot.timer = eng->world.world_time;
		eng->shot.id++;
	}
	else if (eng->shot.id == 8)
	{
		eng->shot.timer = eng->world.world_time;
		eng->shot.id = 0;
	}
	return (eng->shot.id);
}

void	put_shot(t_eng *eng, int x, int y)
{
	int	color;
	int	pxsize;
	int	pysize;
	int	xtemp;

	pxsize = SCREENWIDTH - x;
	pysize = SCREENHEIGHT - y;
	xtemp = x;
	while (++y < SCREENHEIGHT)
	{
		x = xtemp;
		while (++x < SCREENWIDTH)
		{
			color = get_pixel_image(eng->shot, (float)(x - (SCREENWIDTH / 2 - \
7)) / pxsize * eng->shot.img_height, (float)(y - (SCREENHEIGHT / 2 - 7)) / \
pysize * eng->shot.img_height, get_anim_id(eng));
			if (color != 13898154)
				put_pixel_image(&eng->canva, x, y, color);
		}
	}
}

//void	load_bonus_addr(t_eng *eng)

void	load_bonus_sprites(t_eng *eng)
{
	eng->shot.tex[0] = mlx_xpm_file_to_image(eng->mlx_ptr, "./tiles/fire0.xpm", &eng->shot.img_width, &eng->shot.img_height);
	eng->shot.addr[0] = mlx_get_data_addr(eng->shot.tex[0], &eng->shot.bits_per_pixel, &eng->shot.line_length, &eng->shot.endian);
	eng->shot.tex[1] = mlx_xpm_file_to_image(eng->mlx_ptr, "./tiles/fire1.xpm", &eng->shot.img_width, &eng->shot.img_height);
	eng->shot.addr[1] = mlx_get_data_addr(eng->shot.tex[1], &eng->shot.bits_per_pixel, &eng->shot.line_length, &eng->shot.endian);
	eng->shot.tex[2] = mlx_xpm_file_to_image(eng->mlx_ptr, "./tiles/fire2.xpm", &eng->shot.img_width, &eng->shot.img_height);
	eng->shot.addr[2] = mlx_get_data_addr(eng->shot.tex[2], &eng->shot.bits_per_pixel, &eng->shot.line_length, &eng->shot.endian);
	eng->shot.tex[3] = mlx_xpm_file_to_image(eng->mlx_ptr, "./tiles/fire3.xpm", &eng->shot.img_width, &eng->shot.img_height);
	eng->shot.addr[3] = mlx_get_data_addr(eng->shot.tex[3], &eng->shot.bits_per_pixel, &eng->shot.line_length, &eng->shot.endian);
	eng->shot.tex[4] = mlx_xpm_file_to_image(eng->mlx_ptr, "./tiles/fire4.xpm", &eng->shot.img_width, &eng->shot.img_height);
	eng->shot.addr[4] = mlx_get_data_addr(eng->shot.tex[4], &eng->shot.bits_per_pixel, &eng->shot.line_length, &eng->shot.endian);
	eng->shot.tex[5] = mlx_xpm_file_to_image(eng->mlx_ptr, "./tiles/fire5.xpm", &eng->shot.img_width, &eng->shot.img_height);
	eng->shot.addr[5] = mlx_get_data_addr(eng->shot.tex[5], &eng->shot.bits_per_pixel, &eng->shot.line_length, &eng->shot.endian);
	eng->shot.tex[6] = mlx_xpm_file_to_image(eng->mlx_ptr, "./tiles/fire6.xpm", &eng->shot.img_width, &eng->shot.img_height);
	eng->shot.addr[6] = mlx_get_data_addr(eng->shot.tex[6], &eng->shot.bits_per_pixel, &eng->shot.line_length, &eng->shot.endian);
	eng->shot.tex[7] = mlx_xpm_file_to_image(eng->mlx_ptr, "./tiles/fire7.xpm", &eng->shot.img_width, &eng->shot.img_height);
	eng->shot.addr[7] = mlx_get_data_addr(eng->shot.tex[7], &eng->shot.bits_per_pixel, &eng->shot.line_length, &eng->shot.endian);
	eng->shot.tex[8] = mlx_xpm_file_to_image(eng->mlx_ptr, "./tiles/fire8.xpm", &eng->shot.img_width, &eng->shot.img_height);
	eng->shot.addr[8] = mlx_get_data_addr(eng->shot.tex[8], &eng->shot.bits_per_pixel, &eng->shot.line_length, &eng->shot.endian);
}
