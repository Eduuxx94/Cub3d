/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:34:37 by ede-alme          #+#    #+#             */
/*   Updated: 2022/12/27 18:45:13 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

//This function will choice the shot anim anim[id] by time lapse
int	get_anim_id(t_eng *eng)
{
	if (!eng->shot.id)
		return (0);
	if (eng->world.world_time - eng->shot.timer < 30000)
		return (eng->shot.id);
	if (eng->shot.id == 1 && ++eng->shot.id)
		eng->shot.timer = eng->world.world_time;
	else if (eng->shot.id == 2 && ++eng->shot.id)
		eng->shot.timer = eng->world.world_time;
	else if (eng->shot.id == 3 && ++eng->shot.id)
		eng->shot.timer = eng->world.world_time;
	else if (eng->shot.id == 4 && ++eng->shot.id)
		eng->shot.timer = eng->world.world_time;
	else if (eng->shot.id == 5 && ++eng->shot.id)
		eng->shot.timer = eng->world.world_time;
	else if (eng->shot.id == 6 && ++eng->shot.id)
		eng->shot.timer = eng->world.world_time;
	else if (eng->shot.id == 7 && ++eng->shot.id)
		eng->shot.timer = eng->world.world_time;
	else if (eng->shot.id == 8)
		eng->shot.id = 0;
	return (eng->shot.id);
}

//This fuction will print shot in the canva
void	put_shot(t_eng *eng, int x, int y)
{
	int	color;
	int	pxsize;
	int	pysize;
	int	xtemp;

	pxsize = SCREENWIDTH - x;
	pysize = SCREENHEIGHT - y;
	xtemp = x;
	while (++y <= SCREENHEIGHT)
	{
		x = xtemp;
		while (++x <= SCREENWIDTH)
		{
			color = get_pixel_image(eng->shot, (float)(x - (SCREENWIDTH * \
0.48)) / pxsize * eng->shot.img_height, (float)(y - (SCREENHEIGHT * 0.48)) \
	/ pysize * eng->shot.img_height, get_anim_id(eng));
			if (color != 13898154)
				put_pixel_image(&eng->canva, x, y, color);
		}
	}
}

//create data from anim sprites
void	create_data_anim(t_tex *anim)
{
	int	i;

	i = -1;
	while (++i < 9)
		anim->addr[i] = mlx_get_data_addr(anim->tex[i], &anim->bits_per_pixel, \
&anim->line_length, &anim->endian);
}

//void	load_bonus_addr(t_eng *eng)
void	load_bonus_sprites(t_eng *eng)
{
	eng->shot.tex[0] = mlx_xpm_file_to_image(eng->mlx_ptr, "./tiles/fire0.xpm"\
, &eng->shot.img_width, &eng->shot.img_height);
	eng->shot.tex[1] = mlx_xpm_file_to_image(eng->mlx_ptr, "./tiles/fire1.xpm"\
, &eng->shot.img_width, &eng->shot.img_height);
	eng->shot.tex[2] = mlx_xpm_file_to_image(eng->mlx_ptr, "./tiles/fire2.xpm"\
, &eng->shot.img_width, &eng->shot.img_height);
	eng->shot.tex[3] = mlx_xpm_file_to_image(eng->mlx_ptr, "./tiles/fire3.xpm"\
, &eng->shot.img_width, &eng->shot.img_height);
	eng->shot.tex[4] = mlx_xpm_file_to_image(eng->mlx_ptr, "./tiles/fire4.xpm"\
, &eng->shot.img_width, &eng->shot.img_height);
	eng->shot.tex[5] = mlx_xpm_file_to_image(eng->mlx_ptr, "./tiles/fire5.xpm"\
, &eng->shot.img_width, &eng->shot.img_height);
	eng->shot.tex[6] = mlx_xpm_file_to_image(eng->mlx_ptr, "./tiles/fire6.xpm"\
, &eng->shot.img_width, &eng->shot.img_height);
	eng->shot.tex[7] = mlx_xpm_file_to_image(eng->mlx_ptr, "./tiles/fire7.xpm"\
, &eng->shot.img_width, &eng->shot.img_height);
	eng->shot.tex[8] = mlx_xpm_file_to_image(eng->mlx_ptr, "./tiles/fire8.xpm"\
, &eng->shot.img_width, &eng->shot.img_height);
	create_data_anim(&eng->shot);
}

void	swap_door(t_eng *eng, int x)
{
	if (eng->event.key_space && x == SCREENWIDTH / 2 && eng->world.world_time \
	- eng->world.last_door > 400000)
	{
		if (eng->file->map[(int)(eng->player.posy + eng->player.diry * 1)] \
		[(int)(eng->player.posx + eng->player.dirx * 1)] == 'D')
			eng->file->map[(int)(eng->player.posy + eng->player.diry * 1)] \
			[(int)(eng->player.posx + eng->player.dirx * 1)] = 'F';
		else if (eng->file->map[(int)(eng->player.posy + eng->player.diry * 1)] \
		[(int)(eng->player.posx + eng->player.dirx * 1)] == 'F')
			eng->file->map[(int)(eng->player.posy + eng->player.diry * 1)] \
			[(int)(eng->player.posx + eng->player.dirx * 1)] = 'D';
		eng->world.last_door = eng->world.world_time;
	}
}
