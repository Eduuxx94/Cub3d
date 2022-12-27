/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:08:50 by ede-alme          #+#    #+#             */
/*   Updated: 2022/12/27 19:36:35 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# define SCREENHEIGHT 300
# define SCREENWIDTH 300

# include "cub3d.h"
# include <signal.h>
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
	KEY_F = 102,
	TAB = 65289,
	KEY_UP = 65362,
	KEY_DOWN =65364,
	KEY_RIGTH = 65363,
	KEY_LEFT = 65361
};

typedef struct s_tex
{
	int		id;
	void	*tex[9];
	char	*addr[9];
	int		img_width;
	double	timer;
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
	int		key_space;
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
	double			last_door;
}	t_world;

typedef struct s_eng
{
	t_file			*file;
	t_player		player;
	t_world			world;
	t_event			event;
	t_tex			tex;
	t_canva			canva;
	t_canva			minimap;
	t_tex			shot;
	t_raycast		raycast;
	void			*mlx_ptr;
	void			*win_ptr;
}	t_eng;

//engine.c file
void	ft_start_engine(t_file *file);
void	eng_load_sprites(t_eng *eng, int i);
void	eng_start_values(t_eng *eng);
void	eng_init(t_eng *eng);
void	eng_dir_plane(double dirx, double diry, double planex, double planey);

//engine_utils.c file
void	show_fps(t_eng *eng);
int		ft_close(t_eng *eng);
void	update_gametime(t_eng *eng);
t_eng	*engine(void);

//events.c file
int		mouse(int x, int y, t_eng *eng);
int		keytestout(int keycode, t_eng *eng);
int		keytest(int keycode, t_eng *eng);
int		update(t_eng *eng);
int		button_press(int keycode);

//raycast1.c file
void	rc_check_tex_hit(t_eng *eng);
void	rc_calc_cam_dir(t_eng *eng);
void	rc_check_wall_hit(t_eng *eng);
void	rc_calc_ray_dist(t_eng *eng);
void	rc_calc_ray_length(t_eng *eng, int x);

//raycast2.c file
void	rc_update_pos_dir(t_eng *eng);
void	rc_event_rot(t_eng *eng, int key);
void	rc_event_a_d(t_eng *eng, double s);
void	rc_event_w_s(t_eng *eng, double dirx, double diry, double movespeed);
void	rc_write_raycast(t_eng *eng);

//raycast_utils.c file
void	paint_vertical(t_eng *eng, int x, int drawstart, int drawend);
void	put_pixel_image(t_canva *canva, int x, int y, int color);
int		get_pixel_image(t_tex tex, int x, int y, int id);
int		get_dir(int value);

//anim.c file
int		get_anim_id(t_eng *eng);
void	create_data_anim(t_tex *anim);
void	load_bonus_sprites(t_eng *eng);
void	put_shot(t_eng *eng, int x, int y);
void	swap_door(t_eng *eng, int x);

//sound.c file
int		play_sound( char *file);

//minimap1.c file
int		render_minimap(t_eng *eng);
int		is_map(t_eng *eng, int x, int y);

//minimap2.c file
void	render_block(t_eng *eng, int x, int y, int color);
void	render_map(int y, int i, int x, int j);
void	render_player(t_eng *eng);
void	render_bg(t_eng *eng);
void	render_border(t_eng *eng);

//Loading.c files
int		put_loading(int i, char *loading);

#endif