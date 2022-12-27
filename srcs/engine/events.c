/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 20:03:20 by ede-alme          #+#    #+#             */
/*   Updated: 2022/12/27 19:34:07 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

//Funcao que sera chamada pelo loop hook
int	update(t_eng *eng)
{
	update_gametime(eng);
	if (eng->world.world_time - eng->world.last_time > eng->world.frames_rate)
	{
		show_fps(eng);
		rc_write_raycast(eng);
		put_shot(eng, SCREENWIDTH * 0.48, SCREENHEIGHT * 0.48);
		mlx_put_image_to_window(eng->mlx_ptr, eng->win_ptr, eng->canva.img, \
0, 0);
		rc_update_pos_dir(eng);
		render_minimap(eng);
		mlx_put_image_to_window(eng->mlx_ptr, eng->win_ptr, eng->minimap.img, \
5, 5);
	}
	return (0);
}

//Esta função atualiza as variaveis para ativação de eventos mlx_m_hide leaks??
int	keytest(int keycode, t_eng *eng)
{
	if (keycode == SHIFT)
	{
		eng->event.key_shift = !eng->event.key_shift;
		if (eng->event.key_shift)
			mlx_mouse_show(eng->mlx_ptr, eng->win_ptr);
		else
			mlx_mouse_hide(eng->mlx_ptr, eng->win_ptr);
	}
	else if (keycode == ESC)
		ft_close(eng);
	else if ((keycode == KEY_W && ++eng->event.key_w) || (keycode == KEY_S \
	&& ++eng->event.key_s))
		;
	else if ((keycode == KEY_D && ++eng->event.key_d) || (keycode == KEY_A \
	&& ++eng->event.key_a))
		;
	else if (keycode == KEY_RIGTH)
		eng->event.key_rigth = -5;
	else if (keycode == KEY_LEFT)
		eng->event.key_left = 5;
	else if (keycode == KEY_UP && eng->event.screen_y < (SCREENHEIGHT * 0.5))
		eng->event.screen_y += 15;
	else if (keycode == KEY_DOWN && eng->event.screen_y > (SCREENHEIGHT * -0.5))
		eng->event.screen_y -= 15;
	return (0);
}

//esta função atualiza as variaveis para desativar eventos
int	keytestout(int keycode, t_eng *eng)
{
	if (keycode == KEY_F && !eng->shot.id && ++eng->shot.id && \
play_sound("paplay ./sounds/fire_shot.ogg"))
		eng->shot.timer = eng->world.world_time;
	else if (keycode == KEY_W)
		eng->event.key_w = 0;
	else if (keycode == KEY_S)
		eng->event.key_s = 0;
	else if (keycode == KEY_D)
		eng->event.key_d = 0;
	else if (keycode == KEY_A)
		eng->event.key_a = 0;
	else if (keycode == KEY_LEFT)
		eng->event.key_left = 0;
	else if (keycode == KEY_RIGTH)
		eng->event.key_rigth = 0;
	else if (keycode == SPACE)
		eng->event.key_space = 1;
	return (0);
}

//Função que ativa movimentos do mouse e atualiza a posição da camera
int	mouse(int x, int y, t_eng *eng)
{
	if (eng->event.key_shift)
		return (1);
	if (y != SCREENHEIGHT / 2 || x != SCREENWIDTH / 2)
	{
		if (y != SCREENHEIGHT / 2)
			eng->event.screen_y += (SCREENHEIGHT / 2 - y);
		if (x != SCREENWIDTH / 2)
			eng->event.screen_x = SCREENWIDTH / 2 - x;
		mlx_mouse_move(eng->mlx_ptr, eng->win_ptr, SCREENWIDTH / 2, \
SCREENHEIGHT / 2);
	}
	if (eng->event.screen_y < (SCREENHEIGHT * -0.5))
		eng->event.screen_y = SCREENHEIGHT * -0.5;
	if (eng->event.screen_y > (SCREENHEIGHT * 0.5))
		eng->event.screen_y = SCREENHEIGHT * 0.5;
	return (0);
}

int	button_press(int keycode)
{
	if (keycode == 1 && !engine()->shot.id && ++engine()->shot.id && \
play_sound("paplay ./sounds/fire_shot.ogg"))
		engine()->shot.timer = engine()->world.world_time;
	return (0);
}
