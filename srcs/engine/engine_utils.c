/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 20:01:53 by ede-alme          #+#    #+#             */
/*   Updated: 2022/12/27 19:33:24 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

//Retorna o endereço estatico da estrutura do mlx
t_eng	*engine(void)
{
	static t_eng	eng;

	return (&eng);
}

//Atualiza o tempo do jogo
void	update_gametime(t_eng *eng)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	eng->world.world_time = 1000000 * current_time.tv_sec + \
current_time.tv_usec;
}

void	destroy_anim_images(t_tex *anim)
{
	int	i;

	i = -1;
	while (++i < 9)
		mlx_destroy_image(engine()->mlx_ptr, anim->tex[i]);
}

//Dar free em todos os ponteiros do mlx e da struct file do parse
int	ft_close(t_eng *eng)
{
	mlx_destroy_image(eng->mlx_ptr, eng->tex.tex[0]);
	mlx_destroy_image(eng->mlx_ptr, eng->tex.tex[1]);
	mlx_destroy_image(eng->mlx_ptr, eng->tex.tex[2]);
	mlx_destroy_image(eng->mlx_ptr, eng->tex.tex[3]);
	mlx_destroy_image(eng->mlx_ptr, eng->tex.tex[4]);
	mlx_destroy_image(eng->mlx_ptr, eng->tex.tex[5]);
	mlx_destroy_image(eng->mlx_ptr, eng->tex.tex[6]);
	mlx_destroy_image(eng->mlx_ptr, eng->tex.tex[7]);
	mlx_destroy_image(eng->mlx_ptr, eng->canva.img);
	mlx_destroy_image(eng->mlx_ptr, eng->minimap.img);
	free(eng->file->id);
	destroy_anim_images(&eng->shot);
	mlx_loop_end(eng->mlx_ptr);
	mlx_clear_window(eng->mlx_ptr, eng->win_ptr);
	mlx_destroy_window(eng->mlx_ptr, eng->win_ptr);
	mlx_destroy_display(eng->mlx_ptr);
	ft_free_sfile(eng->file);
	free(eng->mlx_ptr);
	exit(0);
	return (0);
}

//Mostra no terminal os fps
void	show_fps(t_eng *eng)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	if (current_time.tv_sec == eng->world.timer.tv_sec)
		eng->world.fps_counter++;
	else if (printf("world.fps_counter: (%d)\n", eng->world.fps_counter))
	{
		printf("\e[1;1H\e[2J");
		eng->world.fps = eng->world.fps_counter;
		eng->world.fps_counter = 0;
		gettimeofday(&eng->world.timer, NULL);
	}
}
