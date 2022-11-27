/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:07:35 by ede-alme          #+#    #+#             */
/*   Updated: 2022/11/27 13:49:06 by ede-alme         ###   ########.fr       */
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
	exit(0);
	return (0);
}

int	trigger(int keycode, t_eng *eng)
{
	printf("Keycode:%d\n", keycode);
	if (keycode == 65307)
		ft_close(eng);
	return (0);
}

void	ft_start_engine(t_file *file)
{
	t_eng	eng;

	eng.file = file;
	eng.mlx_ptr = mlx_init();
	eng.win_ptr = mlx_new_window(eng.mlx_ptr, 800, 600, "Hello world!");

	mlx_hook(eng.win_ptr, 17, 0, ft_close, &eng);
	mlx_key_hook(eng.win_ptr, trigger, &eng);
	mlx_loop(eng.mlx_ptr);
}
