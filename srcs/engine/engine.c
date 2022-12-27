/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:07:35 by ede-alme          #+#    #+#             */
/*   Updated: 2022/12/27 19:38:51 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

//This function is called in begin to put values in player variables
void	eng_dir_plane(double dirx, double diry, double planex, double planey)
{
	engine()->player.dirx = dirx;
	engine()->player.diry = diry;
	engine()->player.planex = planex;
	engine()->player.planey = planey;
}

//This function will put the first values to init raycast
void	eng_init(t_eng *eng)
{
	eng->player.posx = get_map_pos(eng->file->map, 'x') + 0.5;
	eng->player.posy = get_map_pos(eng->file->map, 'y') + 0.5;
	if (eng->file->map[(int)eng->player.posy][(int)eng->player.posx] == 'N')
		eng_dir_plane(0, -1, 0.66, 0);
	if (eng->file->map[(int)eng->player.posy][(int)eng->player.posx] == 'S')
		eng_dir_plane(0, 1, -0.66, 0);
	if (eng->file->map[(int)eng->player.posy][(int)eng->player.posx] == 'W')
		eng_dir_plane(-1, 0, 0, -0.66);
	if (eng->file->map[(int)eng->player.posy][(int)eng->player.posx] == 'E')
		eng_dir_plane(1, 0, 0, 0.66);
	eng->file->map[(int)eng->player.posy][(int)eng->player.posx] = '0';
}

//This function will put beggin values
void	eng_start_values(t_eng *eng)
{
	eng->world.frames_rate = RATE_MAX;
	eng->event.key_shift = 1;
	eng->mlx_ptr = mlx_init();
	eng->win_ptr = mlx_new_window(eng->mlx_ptr, SCREENWIDTH, \
SCREENHEIGHT, "Cub3D");
}

//Load sprites of mandatory game
void	eng_load_sprites(t_eng *eng, int i)
{
	eng->canva.img = mlx_new_image(eng->mlx_ptr, SCREENWIDTH, SCREENHEIGHT);
	eng->canva.addr = mlx_get_data_addr(eng->canva.img, \
&eng->canva.bits_per_pixel, &eng->canva.line_length, &eng->canva.endian);
	while (++i < 4 && put_loading(i, NULL))
	{
		eng->tex.tex[i] = mlx_xpm_file_to_image(eng->mlx_ptr, eng->file->id[i], \
&eng->tex.img_width, &eng->tex.img_height);
		eng->tex.addr[i] = mlx_get_data_addr(eng->tex.tex[i], \
&eng->tex.bits_per_pixel, &eng->tex.line_length, &eng->tex.endian);
	}
	eng->tex.tex[i--] = mlx_xpm_file_to_image(eng->mlx_ptr, \
"./tiles/D1_1024.xpm", &eng->tex.img_width, &eng->tex.img_height);
	eng->tex.tex[5] = mlx_xpm_file_to_image(eng->mlx_ptr, \
"./tiles/D2_1024.xpm", &eng->tex.img_width, &eng->tex.img_height);
	eng->tex.tex[6] = mlx_xpm_file_to_image(eng->mlx_ptr, \
"./tiles/D3_1024.xpm", &eng->tex.img_width, &eng->tex.img_height);
	eng->tex.tex[7] = mlx_xpm_file_to_image(eng->mlx_ptr, \
"./tiles/D4_1024.xpm", &eng->tex.img_width, &eng->tex.img_height);
	while (++i < 8 && put_loading(i, NULL))
		eng->tex.addr[i] = mlx_get_data_addr(eng->tex.tex[i], \
&eng->tex.bits_per_pixel, &eng->tex.line_length, &eng->tex.endian);
	eng->minimap.img = mlx_new_image(eng->mlx_ptr, 144, 144);
	eng->minimap.addr = mlx_get_data_addr(eng->minimap.img, \
&eng->minimap.bits_per_pixel, &eng->minimap.line_length, &eng->minimap.endian);
	load_bonus_sprites(eng);
}

//MLX init here
void	ft_start_engine(t_file *file)
{
	t_eng	*eng;

	eng = engine();
	eng->file = file;
	eng_init(eng);
	eng_start_values(eng);
	eng_load_sprites(eng, -1);
	mlx_hook(eng->win_ptr, 6, (1L << 6), mouse, eng);
	mlx_loop_hook(eng->mlx_ptr, update, eng);
	mlx_hook(eng->win_ptr, 17, 0, ft_close, eng);
	mlx_hook(eng->win_ptr, 2, 1L << 0, keytest, eng);
	mlx_hook(eng->win_ptr, 3, 1L << 1, keytestout, eng);
	mlx_hook(eng->win_ptr, 3, 1L << 1, keytestout, eng);
	mlx_hook(eng->win_ptr, 4, 1L << 2, button_press, NULL);
	mlx_loop(eng->mlx_ptr);
}
