/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:07:35 by ede-alme          #+#    #+#             */
/*   Updated: 2022/11/30 20:11:59 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	ft_close(t_eng *eng)
{
	mlx_loop_end(eng->mlx_ptr);
	mlx_clear_window(eng->mlx_ptr, eng->win_ptr);
	mlx_destroy_window(eng->mlx_ptr, eng->win_ptr);
	mlx_destroy_display(eng->mlx_ptr);
	ft_free_sfile(eng->file);
	free(eng->mlx_ptr);
	exit(0);
	return (0);
}

int	trigger(int keycode, t_eng *eng)
{
	printf("Keycode:%d\n", keycode);
	if (keycode == ESC)
		ft_close(eng);
	return (0);
}

void	fps(t_eng *eng)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	if (current_time.tv_sec == eng->fps_time.tv_sec)
		eng->fps++;
	else if (printf("FPS: (%d)\n", eng->fps))
	{
		printf("\e[1;1H\e[2J");
		eng->fps = 0;
		gettimeofday(&eng->fps_time, NULL);
	}
}

int	update(t_eng *eng)
{
	fps(eng);
	return (0);
}

void	ft_start_engine(t_file *file)
{
	t_eng	eng;

	eng.file = file;
	eng.fps = 0;
	eng.mlx_ptr = mlx_init();
	eng.win_ptr = mlx_new_window(eng.mlx_ptr, 1200, 900, "Cub3D");
	mlx_hook(eng.win_ptr, 17, 0, ft_close, &eng);
	mlx_key_hook(eng.win_ptr, trigger, &eng);
	mlx_loop_hook(eng.mlx_ptr, update, &eng); //construcao do raycast
	mlx_loop(eng.mlx_ptr);
}
