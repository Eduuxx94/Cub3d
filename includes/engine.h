/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:08:50 by ede-alme          #+#    #+#             */
/*   Updated: 2022/12/11 11:39:07 by ede-alme         ###   ########.fr       */
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


typedef struct s_eng
{
	struct timeval	fps_time;
	t_tex			tex;
	t_canva			canva;
	int				fps;
	t_file			*file;
	void			*mlx_ptr;
	void			*win_ptr;
	double			posX;
	double			posY;
	double			dirX;
	double			dirY;
	double			planeX;
	double			planeY;
	double			time;
	double			oldTime;
	int				key_W;
	int				key_S;
	int				key_D;
	int				key_A;
	int				key_rigth;
	int				key_left;
	int				key_shift;
	int				screen_y;
}	t_eng;

void	ft_start_engine(t_file *file);

#endif