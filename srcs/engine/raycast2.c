/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 20:09:33 by ede-alme          #+#    #+#             */
/*   Updated: 2022/12/27 18:57:24 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

//This functions will write vertical lines in canva image
void	rc_write_raycast(t_eng *eng)
{
	int	x;

	x = SCREENWIDTH;
	eng->event.frame_time = (eng->world.world_time - \
eng->world.last_time) / 1000.0;
	eng->world.last_time = eng->world.world_time;
	while (--x)
	{
		rc_calc_ray_length(eng, x);
		rc_calc_ray_dist(eng);
		rc_check_wall_hit(eng);
		rc_calc_cam_dir(eng);
		rc_check_tex_hit(eng);
		paint_vertical(eng, x, eng->raycast.drawstart + eng->event.screen_y, \
eng->raycast.drawend + eng->event.screen_y);
		swap_door(eng, x);
	}
	eng->event.key_space = 0;
}

void	rc_event_w_s(t_eng *eng, double dirx, double diry, double movespeed)
{
	float	dx;
	float	dy;

	dx = get_dir(dirx);
	dy = get_dir(diry);
	if ((eng->file->map[(int)(eng->player.posy)][(int)(eng->player.posx + dirx \
	* movespeed)] == '0' || eng->file->map[(int)(eng->player.posy)][(int)(eng->\
player.posx + dirx * movespeed)] == 'F') && (eng->file->map[(int)((eng->player.\
posy) + dy)][(int)((eng->player.posx + dirx * movespeed) + dx)] == '0' || eng->\
file->map[(int)((eng->player.posy) + dy)][(int)((eng->player.posx + dirx * \
movespeed) + dx)] == 'F'))
		eng->player.posx += dirx * movespeed;
	if ((eng->file->map[(int)(eng->player.posy + diry * movespeed)][(int)(eng->\
player.posx)] == '0' || eng->file->map[(int)(eng->player.posy + diry * \
movespeed)][(int)(eng->player.posx)] == 'F') && (eng->file->map[(int)((eng->\
player.posy + diry * movespeed) + dy)][(int)((eng->player.posx) + dx)] == '0' \
	|| eng->file->map[(int)((eng->player.posy + diry * movespeed) + dy)][(int) \
	((eng->player.posx) + dx)] == 'F'))
		eng->player.posy += diry * movespeed;
}

void	rc_event_a_d(t_eng *eng, double s)
{
	eng->event.olddirx = eng->player.dirx;
	eng->player.dirx = eng->player.dirx * cos(s) - eng->player.diry * sin(s);
	eng->player.diry = eng->event.olddirx * sin(s) + eng->player.diry * cos(s);
	eng->event.oldplanex = eng->player.planex;
	eng->player.planex = eng->player.planex * cos(s) - eng->player.planey * \
sin(s);
	eng->player.planey = eng->event.oldplanex * sin(s) + eng->player.planey * \
cos(s);
	rc_event_w_s(eng, eng->player.dirx, eng->player.diry, eng->event.movespeed \
	* 0.5);
	eng->event.olddirx = eng->player.dirx;
	eng->player.dirx = eng->player.dirx * cos(-s) - eng->player.diry * sin(-s);
	eng->player.diry = eng->event.olddirx * sin(-s) + eng->player.diry * \
cos(-s);
	eng->event.oldplanex = eng->player.planex;
	eng->player.planex = eng->player.planex * cos(-s) - eng->player.planey * \
sin(-s);
	eng->player.planey = eng->event.oldplanex * sin(-s) + eng->player.planey * \
cos(-s);
}

void	rc_event_rot(t_eng *eng, int key)
{
	if (eng->event.screen_x)
		eng->event.rotspeed = key * 0.0006;
	else
		eng->event.rotspeed = eng->event.rotspeed * key;
	eng->event.olddirx = eng->player.dirx;
	eng->player.dirx = eng->player.dirx * cos(-eng->event.rotspeed) - \
eng->player.diry * sin(-eng->event.rotspeed);
	eng->player.diry = eng->event.olddirx * sin(-eng->event.rotspeed) + \
eng->player.diry * cos(-eng->event.rotspeed);
	eng->event.oldplanex = eng->player.planex;
	eng->player.planex = eng->player.planex * cos(-eng->event.rotspeed) - \
eng->player.planey * sin(-eng->event.rotspeed);
	eng->player.planey = eng->event.oldplanex * sin(-eng->event.rotspeed) + \
eng->player.planey * cos(-eng->event.rotspeed);
	if (eng->event.screen_x)
		eng->event.screen_x = 0;
}

//This function update the pos and dir of player
void	rc_update_pos_dir(t_eng *eng)
{
	eng->event.movespeed = eng->event.frame_time * 0.003;
	if (eng->event.key_w && (eng->event.key_d || eng->event.key_a))
		eng->event.movespeed = eng->event.movespeed * 0.8;
	eng->event.rotspeed = eng->event.frame_time * 0.0004;
	if (eng->event.key_w && !eng->event.key_s)
		rc_event_w_s(eng, eng->player.dirx, eng->player.diry, \
eng->event.movespeed);
	else if (eng->event.key_s && !eng->event.key_w)
		rc_event_w_s(eng, -eng->player.dirx, -eng->player.diry, \
eng->event.movespeed * 0.7);
	if (eng->event.key_d && !eng->event.key_a)
		rc_event_a_d(eng, 1.57001);
	else if (eng->event.key_a && !eng->event.key_d)
		rc_event_a_d(eng, -1.57001);
	if (eng->event.key_left || eng->event.key_rigth)
		if (!eng->event.key_left || !eng->event.key_rigth)
			rc_event_rot(eng, eng->event.key_left + eng->event.key_rigth);
	if (eng->event.screen_x && !eng->event.key_rigth && !eng->event.key_left)
		rc_event_rot(eng, eng->event.screen_x);
}
