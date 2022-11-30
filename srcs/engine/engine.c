/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:07:35 by ede-alme          #+#    #+#             */
/*   Updated: 2022/11/30 18:24:04 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int*)pixel = color;
}

void game_clear(t_game *game)
{
	mlx_clear_window(game->mlx.ptr, game->mlx.win);
	mlx_destroy_window(game->mlx.ptr, game->mlx.win);
	mlx_destroy_display(game->mlx.ptr);
	ft_free_sfile(game->file);
	free(game->mlx.ptr);
}

int	game_quit(t_game *game)
{
	mlx_loop_end(game->mlx.ptr);
	game_clear(game);
	exit(0);
	return (0);
}

int	key_press(int key, t_game *game)
{
	if (key == ESC)
		game_quit(game);
	return (0);
}

void	render_bg(t_game *game, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
		{
			my_mlx_pixel_put(&game->mlx.img, j, i, color);
		}
	}
}

int	render(t_game *game)
{
	render_bg(game, 0xFFFFFF);//test
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->mlx.img.ptr, 0, 0);
	return (0);
}

void	hook_mlx(t_game *game)
{
	mlx_loop_hook(game->mlx.ptr, render, game);
	mlx_hook(game->mlx.win, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx.win, 17, 0, game_quit, game);
}

void	start_mlx(t_game *game)
{
	game->mlx.ptr = mlx_init();
	if (!game->mlx.ptr)
	{
		perror("Error starting mlx.\n");
		game_clear(game);
		exit(2);
	}
	game->mlx.win = mlx_new_window(game->mlx.ptr, WIDTH, HEIGHT, "Cub3D");
	if (!game->mlx.win)
	{
		perror("Error creating window.\n");
		game_clear(game);
		exit(2);
	}
	game->mlx.img.ptr = mlx_new_image(game->mlx.ptr, WIDTH, HEIGHT);
	if (!game->mlx.img.ptr)
	{
		perror("Error creating image.\n");
		game_clear(game);
		exit(2);
	}
	game->mlx.img.addr = mlx_get_data_addr(game->mlx.img.ptr, &game->mlx.img.bpp, &game->mlx.img.line_length,&game->mlx.img.endian);
	game->mlx.img.width = WIDTH;
	game->mlx.img.height = HEIGHT;
}
