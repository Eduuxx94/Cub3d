/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:34:37 by ede-alme          #+#    #+#             */
/*   Updated: 2022/12/23 18:12:26 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

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
			color = get_pixel_image(eng->shot, (float)(x - (SCREENWIDTH / 2 - 7)) / pxsize * eng->shot.img_height, (float)(y - (SCREENHEIGHT / 2 - 7)) / pysize * eng->shot.img_height, 0);
			if (color != 13898154)
				put_pixel_image(&eng->canva, x, y, color);
		}
	}
}

void	load_bonus_sprites(t_eng *eng)
{
	eng->shot.tex[0] = mlx_xpm_file_to_image(eng->mlx_ptr, "./tiles/fire0.xpm", &eng->shot.img_width, &eng->shot.img_height);
	eng->shot.addr[0] = mlx_get_data_addr(eng->shot.tex[0], &eng->shot.bits_per_pixel, &eng->shot.line_length, &eng->shot.endian);
	eng->shot.tex[1] = mlx_xpm_file_to_image(eng->mlx_ptr, "./tiles/fire0.xpm", &eng->shot.img_width, &eng->shot.img_height);
	eng->shot.addr[1] = mlx_get_data_addr(eng->shot.tex[1], &eng->shot.bits_per_pixel, &eng->shot.line_length, &eng->shot.endian);
	eng->shot.tex[2] = mlx_xpm_file_to_image(eng->mlx_ptr, "./tiles/fire0.xpm", &eng->shot.img_width, &eng->shot.img_height);
	eng->shot.addr[2] = mlx_get_data_addr(eng->shot.tex[2], &eng->shot.bits_per_pixel, &eng->shot.line_length, &eng->shot.endian);
	eng->shot.tex[3] = mlx_xpm_file_to_image(eng->mlx_ptr, "./tiles/fire0.xpm", &eng->shot.img_width, &eng->shot.img_height);
	eng->shot.addr[3] = mlx_get_data_addr(eng->shot.tex[3], &eng->shot.bits_per_pixel, &eng->shot.line_length, &eng->shot.endian);
	eng->shot.tex[4] = mlx_xpm_file_to_image(eng->mlx_ptr, "./tiles/fire0.xpm", &eng->shot.img_width, &eng->shot.img_height);
	eng->shot.addr[4] = mlx_get_data_addr(eng->shot.tex[4], &eng->shot.bits_per_pixel, &eng->shot.line_length, &eng->shot.endian);
	eng->shot.tex[5] = mlx_xpm_file_to_image(eng->mlx_ptr, "./tiles/fire0.xpm", &eng->shot.img_width, &eng->shot.img_height);
	eng->shot.addr[5] = mlx_get_data_addr(eng->shot.tex[5], &eng->shot.bits_per_pixel, &eng->shot.line_length, &eng->shot.endian);
	eng->shot.tex[6] = mlx_xpm_file_to_image(eng->mlx_ptr, "./tiles/fire0.xpm", &eng->shot.img_width, &eng->shot.img_height);
	eng->shot.addr[6] = mlx_get_data_addr(eng->shot.tex[6], &eng->shot.bits_per_pixel, &eng->shot.line_length, &eng->shot.endian);
	eng->shot.tex[7] = mlx_xpm_file_to_image(eng->mlx_ptr, "./tiles/fire0.xpm", &eng->shot.img_width, &eng->shot.img_height);
	eng->shot.addr[7] = mlx_get_data_addr(eng->shot.tex[7], &eng->shot.bits_per_pixel, &eng->shot.line_length, &eng->shot.endian);
	eng->shot.tex[8] = mlx_xpm_file_to_image(eng->mlx_ptr, "./tiles/fire0.xpm", &eng->shot.img_width, &eng->shot.img_height);
	eng->shot.addr[8] = mlx_get_data_addr(eng->shot.tex[8], &eng->shot.bits_per_pixel, &eng->shot.line_length, &eng->shot.endian);
}
