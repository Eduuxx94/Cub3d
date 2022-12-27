/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 20:07:38 by ede-alme          #+#    #+#             */
/*   Updated: 2022/12/27 18:40:58 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

//length of ray from one x or y-side to next x or y-side
void	rc_calc_ray_length(t_eng *eng, int x)
{
	eng->raycast.camerax = 2 * x / (double)SCREENWIDTH - 1;
	eng->raycast.raydirx = eng->player.dirx + eng->player.planex * \
eng->raycast.camerax;
	eng->raycast.raydiry = eng->player.diry + eng->player.planey * \
eng->raycast.camerax;
	eng->raycast.mapx = eng->player.posx;
	eng->raycast.mapy = eng->player.posy;
	if (eng->raycast.raydirx == 0)
		eng->raycast.deltadistx = 1e30;
	else
		eng->raycast.deltadistx = fabs(1 / eng->raycast.raydirx);
	if (eng->raycast.raydiry == 0)
		eng->raycast.deltadisty = 1e30;
	else
		eng->raycast.deltadisty = fabs(1 / eng->raycast.raydiry);
}

//calculate step and initial sideDist
void	rc_calc_ray_dist(t_eng *eng)
{
	if (eng->raycast.raydirx < 0)
	{
		eng->raycast.stepx = -1;
		eng->raycast.sidedistx = (eng->player.posx - \
	(double)eng->raycast.mapx) * eng->raycast.deltadistx;
	}
	else
	{
		eng->raycast.stepx = 1;
		eng->raycast.sidedistx = ((double)eng->raycast.mapx + 1.0 - \
eng->player.posx) * eng->raycast.deltadistx;
	}
	if (eng->raycast.raydiry < 0)
	{
		eng->raycast.stepy = -1;
		eng->raycast.sidedisty = (eng->player.posy - (double)eng->raycast.mapy) \
	* eng->raycast.deltadisty;
	}
	else
	{
		eng->raycast.stepy = 1;
		eng->raycast.sidedisty = ((double)eng->raycast.mapy + 1.0 - \
eng->player.posy) * eng->raycast.deltadisty;
	}
}

//check where ray hit a wall
void	rc_check_wall_hit(t_eng *eng)
{
	eng->raycast.hit = 0;
	while (eng->raycast.hit == 0)
	{
		if (eng->raycast.sidedistx < eng->raycast.sidedisty)
		{
			eng->raycast.sidedistx += eng->raycast.deltadistx;
			eng->raycast.mapx += eng->raycast.stepx;
			eng->raycast.side = 0;
		}
		else
		{
			eng->raycast.sidedisty += eng->raycast.deltadisty;
			eng->raycast.mapy += eng->raycast.stepy;
			eng->raycast.side = 1;
		}
		if (eng->file->map[eng->raycast.mapy][eng->raycast.mapx] != '0' \
	&& eng->file->map[eng->raycast.mapy][eng->raycast.mapx] != 'F')
			eng->raycast.hit = 1;
		if (eng->file->map[eng->raycast.mapy][eng->raycast.mapx] == 'D')
			eng->raycast.hit = 2;
	}
}

//Calculate distance projected on camera direction.
void	rc_calc_cam_dir(t_eng *eng)
{
	if (eng->raycast.side == 0)
		eng->raycast.perpwalldist = (eng->raycast.sidedistx - \
eng->raycast.deltadistx);
	else
		eng->raycast.perpwalldist = (eng->raycast.sidedisty - \
eng->raycast.deltadisty);
	eng->raycast.lineheight = (SCREENHEIGHT / eng->raycast.perpwalldist);
	eng->raycast.drawstart = -eng->raycast.lineheight / 2 + SCREENHEIGHT / 2;
	eng->raycast.drawend = eng->raycast.lineheight / 2 + SCREENHEIGHT / 2;
	if (eng->raycast.side == 0)
		eng->raycast.wallx = eng->player.posy + eng->raycast.perpwalldist \
	* eng->raycast.raydiry;
	else
		eng->raycast.wallx = eng->player.posx + eng->raycast.perpwalldist \
	* eng->raycast.raydirx;
	eng->raycast.wallx -= floor((eng->raycast.wallx));
}

//choose wall tex: EA=0 WE=1 SO=2 NO=3
void	rc_check_tex_hit(t_eng *eng)
{
	if (eng->raycast.side)
	{
		if (eng->raycast.raydiry > 0)
				eng->raycast.texture = 1;
		else
			eng->raycast.texture = 0;
	}
	else
	{
		if (eng->raycast.raydirx > 0)
			eng->raycast.texture = 3;
		else
			eng->raycast.texture = 2;
	}
	if (eng->raycast.hit == 2)
		eng->raycast.texture += 4;
}
