/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:08:50 by ede-alme          #+#    #+#             */
/*   Updated: 2022/12/18 15:14:49 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "cub3d.h"
# include "sys/time.h"
# include <stdlib.h>
# include <math.h>

enum e_keys
{
	RATE_20 = 47500,
	RATE_35 = 27500,
	RATE_50 = 18500,
	RATE_75 = 12500,
	RATE_MAX = 1,
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

typedef struct s_tex
{
	void	*tex[4];
	char	*addr[4];
	int		img_width;
	int		img_height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_tex;

typedef struct s_canva
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_canva;

typedef struct s_player
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
}	t_player;

typedef struct s_raycast
{
	double	camerax;
	double	raydirx;
	double	raydiry;
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
	double	wallx;
	int		texture;
}	t_raycast;

typedef struct s_event
{
	int		key_w;
	int		key_s;
	int		key_d;
	int		key_a;
	int		key_rigth;
	int		key_left;
	int		key_shift;
	int		screen_y;
	int		screen_x;
	double	frame_time;
	double	movespeed;
	double	rotspeed;
	double	olddirx;
	double	oldplanex;
}	t_event;

typedef struct s_world
{
	struct timeval	timer;
	int				fps;
	int				frames_rate;
	int				fps_counter;
	double			world_time;
	double			last_time;
}	t_world;


typedef struct s_eng
{
	t_file			*file;
	t_player		player;
	t_world			world;
	t_event			event;
	t_tex			tex;
	t_canva			canva;
	t_raycast		raycast;
	void			*mlx_ptr;
	void			*win_ptr;
}	t_eng;

void	ft_start_engine(t_file *file);

#endif