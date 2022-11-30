/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:08:50 by ede-alme          #+#    #+#             */
/*   Updated: 2022/11/30 20:08:42 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "cub3d.h"
# include "sys/time.h"
# include <stdlib.h>

enum e_keys
{
	ESC = 65307,
	SPACE = 32,
	ENTER = 65293,
	SHIFT = 65505,
	kEY_D = 100,
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

typedef struct s_eng
{
	struct timeval	fps_time;
	int				fps;
	t_file			*file;
	void			*mlx_ptr;
	void			*win_ptr;
}	t_eng;

void	ft_start_engine(t_file *file);

#endif