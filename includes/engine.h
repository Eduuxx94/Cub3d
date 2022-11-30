/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:08:50 by ede-alme          #+#    #+#             */
/*   Updated: 2022/11/30 20:55:24 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "cub3d.h"

# define WIDTH 800
# define HEIGHT 600

enum e_keys
{
	ESC = 65307,
	SPACE = 32,
	ENTER = 65293,
	SHIFT = 65505,
	KEY_D = 100,
	KEY_A = 97,
	KEY_W = 119,
	KEY_S = 115,
	KEY_M = 109,
	TAB = 65289,
	KEY_UP = 65362,
	KEY_DOWN =65364,
	KEY_RIGTH = 65363,
	KEY_LEFT = 65361
};

typedef struct	s_pos
{
	int	x;
	int	y;
}				t_pos;


typedef struct	s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
//	int		width;
//	int		height;
//	char	*path;
}				t_img;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	t_img	img;
}				t_mlx;

typedef struct s_game
{
	t_mlx	mlx;
	t_file	*file;
	t_pos	player;
}				t_game;

void		start_mlx(t_game *game);
void		hook_mlx(t_game *game);
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
void		game_clear(t_game *game);
int			game_quit(t_game *game);
int			key_press(int key, t_game *game);
//tests
void		player_move(int	key, t_game *game);
void		render_player(t_game *game, int x, int y, int color);
void		render_bg(t_game *game, int color);
int			render(t_game *game);

#endif
