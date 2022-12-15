/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:07:35 by ede-alme          #+#    #+#             */
/*   Updated: 2022/12/15 23:53:07 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

#define screenHeight 740
#define screenWidth 900

//Dar free em todos os ponteiros do mlx e da struct file do parse
int	ft_close(t_eng *eng)
{
	mlx_destroy_image(eng->mlx_ptr, eng->tex.tex[0]);
	mlx_destroy_image(eng->mlx_ptr, eng->tex.tex[1]);
	mlx_destroy_image(eng->mlx_ptr, eng->tex.tex[2]);
	mlx_destroy_image(eng->mlx_ptr, eng->tex.tex[3]);
	mlx_destroy_image(eng->mlx_ptr, eng->canva.img);
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

//Retorna a cor da imagem na posição tex[y][x]
int	get_pixel_image(t_eng *eng, int x, int y, int tex)
{
	return (*(unsigned int *)(eng->tex.addr[tex] + (y * eng->tex.line_length + \
x * (eng->tex.bits_per_pixel / 8))));
}

//Adiciona um pixel na imagem da posicao imagem[x][y] com a o valor color
void	put_pixel_image(t_canva *canva, int x, int y, int color)
{
	char	*dst;

	dst = canva->addr + (y * canva->line_length + x * (canva->bits_per_pixel \
	/ 8));
	*(unsigned int *)dst = color;
}

//Vai juntar as cores RED GREEN BLUE em uma unica variavel int rgb
int	rgb(int r, int g, int b)
{
	int	result;

	result = 0 | r;
	result = result << 8;
	result = result | g;
	result = result << 8;
	result = result | b;
	return (result);
}

//Pinta uma linha vertical na posicao x do canva(imagem) com texturas e tamanhos
void	paint_vertical(t_eng *eng, int x, int drawstart, int drawend)
{
	int		i;
	int		xpercentage;
	int		psize;

	i = -1;
	psize = drawend - drawstart;
	xpercentage = eng->raycast.wallx * eng->tex.img_width;

	while (++i <= screenHeight)
	{
		if (i < drawstart)
			put_pixel_image(&eng->canva, x, i, eng->file->ceilling.rgb);
		else if (i < drawend)
			put_pixel_image(&eng->canva, x, i, get_pixel_image(eng, xpercentage \
, (float)(i - drawstart) / psize * eng->tex.img_height, eng->raycast.texture));
		else
			put_pixel_image(&eng->canva, x, i, eng->file->floor.rgb);
	}
}

//Atualiza o tempo do jogo
void	update_gametime(t_eng *eng)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	eng->world.world_time = 1000000 * current_time.tv_sec + \
current_time.tv_usec;
}

//length of ray from one x or y-side to next x or y-side
void	rc_calc_ray_length(t_eng *eng, int x)
{
	eng->raycast.camerax = 2 * x / (double)screenWidth - 1;
	eng->raycast.raydirx = eng->player.dirx + eng->player.planex * \
eng->raycast.camerax;
	eng->raycast.raydiry = eng->player.diry + eng->player.planey * \
eng->raycast.camerax;
	eng->raycast.mapx = eng->player.posx;
	eng->raycast.mapy = eng->player.posy;
	if (eng->raycast.raydirx == 0)
		eng->raycast.deltadistx = 1e30;
	else
		eng->raycast.deltadistx = fabs(1 / eng->raycast.raydirx);
	if (eng->raycast.raydiry == 0)
		eng->raycast.deltadisty = 1e30;
	else
		eng->raycast.deltadisty = fabs(1 / eng->raycast.raydiry);
}

//calculate step and initial sideDist
void rc_calc_ray_dist(t_eng *eng)
{
	if (eng->raycast.raydirx < 0)
	{
		eng->raycast.stepx = -1;
		eng->raycast.sidedistx = (eng->player.posx - \
	(double)eng->raycast.mapx) * eng->raycast.deltadistx;
	}
	else
	{
		eng->raycast.stepx = 1;
		eng->raycast.sidedistx = ((double)eng->raycast.mapx + 1.0 - \
eng->player.posx) * eng->raycast.deltadistx;
	}
	if (eng->raycast.raydiry < 0)
	{
		eng->raycast.stepy = -1;
		eng->raycast.sidedisty = (eng->player.posy - (double)eng->raycast.mapy) \
	* eng->raycast.deltadisty;
	}
	else
	{
		eng->raycast.stepy = 1;
		eng->raycast.sidedisty = ((double)eng->raycast.mapy + 1.0 - \
eng->player.posy) * eng->raycast.deltadisty;
	}
}

//check where ray hit a wall
void	rc_check_wall_hit(t_eng *eng)
{
	eng->raycast.hit = 0;
	while (eng->raycast.hit == 0)
	{
		if (eng->raycast.sidedistx < eng->raycast.sidedisty)
		{
			eng->raycast.sidedistx += eng->raycast.deltadistx;
			eng->raycast.mapx += eng->raycast.stepx;
			eng->raycast.side = 0;
		}
		else
		{
			eng->raycast.sidedisty += eng->raycast.deltadisty;
			eng->raycast.mapy += eng->raycast.stepy;
			eng->raycast.side = 1;
		}
		if (eng->file->map[eng->raycast.mapy][eng->raycast.mapx] != '0')
			eng->raycast.hit = 1;
	}
}

//Calculate distance projected on camera direction.
void	rc_calc_cam_dir(t_eng *eng)
{
	if (eng->raycast.side == 0)
		eng->raycast.perpwalldist = (eng->raycast.sidedistx - \
eng->raycast.deltadistx);
	else
		eng->raycast.perpwalldist = (eng->raycast.sidedisty - \
eng->raycast.deltadisty);
	eng->raycast.lineheight = (screenHeight / eng->raycast.perpwalldist);
	eng->raycast.drawstart = -eng->raycast.lineheight / 2 + screenHeight / 2;
	eng->raycast.drawend = eng->raycast.lineheight / 2 + screenHeight / 2;
	if (eng->raycast.side == 0)
		eng->raycast.wallx = eng->player.posy + eng->raycast.perpwalldist \
	* eng->raycast.raydiry;
	else
		eng->raycast.wallx = eng->player.posx + eng->raycast.perpwalldist \
	* eng->raycast.raydirx;
	eng->raycast.wallx -= floor((eng->raycast.wallx));
}

//choose wall tex: EA=0 WE=1 SO=2 NO=3
void	rc_check_tex_hit(t_eng *eng)
{
	if (eng->raycast.side)
	{
		if (eng->raycast.raydiry > 0)
				eng->raycast.texture = 0;
		else
			eng->raycast.texture = 1;
	}
	else
	{
		if (eng->raycast.raydirx > 0)
			eng->raycast.texture = 2;
		else
			eng->raycast.texture = 3;
	}
}

//This functions will write vertical lines in canva image
void	rc_write_raycast(t_eng *eng)
{
	int	x;

	x = screenWidth;
	eng->event.frame_time = (eng->world.world_time - \
eng->world.last_time) / 1000.0;
	eng->world.last_time = eng->world.world_time;
	while (--x)
	{
		rc_calc_ray_length(eng, x);
		rc_calc_ray_dist(eng);
		rc_check_wall_hit(eng);
		rc_calc_cam_dir(eng);
		rc_check_tex_hit(eng);
		paint_vertical(eng, x, eng->raycast.drawstart + eng->event.screen_y, \
eng->raycast.drawend + eng->event.screen_y);
	}
}

void	rc_event_w(t_eng *eng)
{
	if (eng->file->map[(int)(eng->player.posy)][(int)(eng->player.posx + \
eng->player.dirx * eng->event.movespeed)] == '0')
		eng->player.posx += eng->player.dirx * eng->event.movespeed;
	if (eng->file->map[(int)(eng->player.posy + eng->player.diry * \
eng->event.movespeed)][(int)(eng->player.posx)] == '0')
		eng->player.posy += eng->player.diry * eng->event.movespeed;
}

void	rc_event_d(t_eng *eng, int s)
{
	eng->event.olddirx = eng->player.dirx;
	eng->player.dirx = eng->player.dirx * cos(s) - eng->player.diry * sin(s);
	eng->player.diry = eng->event.olddirx * sin(s) + eng->player.diry * cos(s);
	eng->event.oldplanex = eng->player.planex;
	eng->player.planex = eng->player.planex * cos(s) - eng->player.planey * \
sin(s);
	eng->player.planey = eng->event.oldplanex * sin(s) + eng->player.planey * \
cos(s);
	if (eng->file->map[(int)(eng->player.posy)][(int)(eng->player.posx + \
eng->player.dirx * eng->event.movespeed)] == '0')
		eng->player.posx += eng->player.dirx * (eng->event.movespeed * 0.5);
	if (eng->file->map[(int)(eng->player.posy + eng->player.diry * \
eng->event.movespeed)][(int)(eng->player.posx)] == '0')
		eng->player.posy += eng->player.diry * (eng->event.movespeed * 0.5);
	eng->event.olddirx = eng->player.dirx;
	eng->player.dirx = eng->player.dirx * cos(-s) - eng->player.diry * sin(-s);
	eng->player.diry = eng->event.olddirx * sin(-s) + eng->player.diry * \
cos(-s);
	eng->event.oldplanex = eng->player.planex;
	eng->player.planex = eng->player.planex * cos(-s) - eng->player.planey * \
sin(-s);
	eng->player.planey = eng->event.oldplanex * sin(-s) + eng->player.planey * \
cos(-s);
}

//This function update the pos and dir of player
void	rc_update_pos_dir(t_eng *eng)
{
	eng->event.movespeed = eng->event.frame_time * 0.003;
	eng->event.rotspeed = (log(pow(eng->event.frame_time, 0.9) + 0.5)) * 0.0009;
	if(eng->event.key_w)
		rc_event_w(eng);
	if (eng->event.key_d)
		rc_event_d(eng, 1.57001);
}

//Funcao que sera chamada pelo loop hook
int	update(t_eng *eng)
{
	update_gametime(eng);
	if (eng->world.world_time - eng->world.last_time > eng->world.frames_rate)
	{
		show_fps(eng);
		rc_write_raycast(eng);
		mlx_put_image_to_window(eng->mlx_ptr, eng->win_ptr, eng->canva.img, 0, 0);
		rc_update_pos_dir(eng);
		if(eng->event.key_d)//falta corrigir as direcoes
		{
		}
		if(eng->event.key_a)//falta corrigir esta etapa
		{
			eng->event.olddirx = eng->player.dirx;
			eng->player.dirx = eng->player.dirx * cos(-1.57001) - eng->player.diry * sin(-1.57001);
			eng->player.diry = eng->event.olddirx * sin(-1.57001) + eng->player.diry * cos(-1.57001);
			eng->event.oldplanex = eng->player.planex;
			eng->player.planex = eng->player.planex * cos(-1.57001) - eng->player.planey * sin(-1.57001);
			eng->player.planey = eng->event.oldplanex * sin(-1.57001) + eng->player.planey * cos(-1.57001);
			if(eng->file->map[(int)(eng->player.posy)][(int)(eng->player.posx + eng->player.dirx * eng->event.movespeed)] == '0')
				eng->player.posx += eng->player.dirx * (eng->event.movespeed * 0.5);
			if(eng->file->map[(int)(eng->player.posy + eng->player.diry * eng->event.movespeed)][(int)(eng->player.posx)] == '0')
				eng->player.posy += eng->player.diry * (eng->event.movespeed * 0.5);
			eng->event.olddirx = eng->player.dirx;
			eng->player.dirx = eng->player.dirx * cos(1.57001) - eng->player.diry * sin(1.57001);
			eng->player.diry = eng->event.olddirx * sin(1.57001) + eng->player.diry * cos(1.57001);
			eng->event.oldplanex = eng->player.planex;
			eng->player.planex = eng->player.planex * cos(1.57001) - eng->player.planey * sin(1.57001);
			eng->player.planey = eng->event.oldplanex * sin(1.57001) + eng->player.planey * cos(1.57001);
		}
		if(eng->event.key_s)//falta corrigir as direcoes
		{
			if(eng->file->map[(int)eng->player.posy][(int)(eng->player.posx - eng->player.dirx * eng->event.movespeed)] == '0')
				eng->player.posx -= eng->player.dirx * eng->event.movespeed;
			if(eng->file->map[(int)(eng->player.posy - eng->player.diry * eng->event.movespeed)][(int)eng->player.posx] == '0')
				eng->player.posy -= eng->player.diry * eng->event.movespeed;
			//eng->key_back = 0;
		}
		if(eng->event.key_left)
		{
			//both camera direction and camera plane must be rotated
			eng->event.olddirx = eng->player.dirx;
			eng->player.dirx = eng->player.dirx * cos(-eng->event.rotspeed * eng->event.key_left) - eng->player.diry * sin(-eng->event.rotspeed * eng->event.key_left);
			eng->player.diry = eng->event.olddirx * sin(-eng->event.rotspeed * eng->event.key_left) + eng->player.diry * cos(-eng->event.rotspeed * eng->event.key_left);
			eng->event.oldplanex = eng->player.planex;
			eng->player.planex = eng->player.planex * cos(-eng->event.rotspeed * eng->event.key_left) - eng->player.planey * sin(-eng->event.rotspeed * eng->event.key_left);
			eng->player.planey = eng->event.oldplanex * sin(-eng->event.rotspeed * eng->event.key_left) + eng->player.planey * cos(-eng->event.rotspeed * eng->event.key_left);
			eng->event.key_left = 0;
		}
		if(eng->event.key_rigth)
		{
			//both camera direction and camera plane must be rotated
			eng->event.olddirx = eng->player.dirx;
			eng->player.dirx = eng->player.dirx * cos(eng->event.rotspeed * eng->event.key_rigth) - eng->player.diry * sin(eng->event.rotspeed * eng->event.key_rigth);
			eng->player.diry = eng->event.olddirx * sin(eng->event.rotspeed * eng->event.key_rigth) + eng->player.diry * cos(eng->event.rotspeed * eng->event.key_rigth);
			eng->event.oldplanex = eng->player.planex;
			eng->player.planex = eng->player.planex * cos(eng->event.rotspeed * eng->event.key_rigth) - eng->player.planey * sin(eng->event.rotspeed * eng->event.key_rigth);
			eng->player.planey = eng->event.oldplanex * sin(eng->event.rotspeed * eng->event.key_rigth) + eng->player.planey * cos(eng->event.rotspeed * eng->event.key_rigth);
			eng->event.key_rigth = 0;
		}
		//mlx_mouse_move(eng->mlx_ptr, eng->win_ptr, screenWidth / 2, screenHeight / 2);
		//mlx_mouse_hide(eng->mlx_ptr, eng->win_ptr);
	}
	return (0);
}

int	keytest(int keycode, t_eng *eng) //Esta função atualiza as variaveis para ativação de eventos
{
	if (keycode == SHIFT)
	{
		eng->event.key_shift = !eng->event.key_shift;
		if (eng->event.key_shift)
			mlx_mouse_show(eng->mlx_ptr, eng->win_ptr);
	}
	else if (keycode == ESC)
		ft_close(eng);
	else if (keycode == KEY_W)
		eng->event.key_w = 1;
	else if (keycode == KEY_S)
		eng->event.key_s = 1;
	else if (keycode == KEY_D)
		eng->event.key_d = 1;
	else if (keycode == KEY_A)
		eng->event.key_a = 1;
	else if (keycode == KEY_RIGTH)
		eng->event.key_rigth = 15;
	else if (keycode == KEY_LEFT)
		eng->event.key_left = 15;
	else if (keycode == KEY_UP && eng->event.screen_y < (screenHeight * 0.5))
		eng->event.screen_y += 15;
	else if (keycode == KEY_DOWN && eng->event.screen_y > (screenHeight * -0.5))
		eng->event.screen_y -= 15;
	return (0);
}

int	keytestout(int keycode, t_eng *eng)//esta função atualiza as variaveis para desativar eventos
{
	if (keycode == KEY_W)
		eng->event.key_w = 0;
	if (keycode == KEY_S)
		eng->event.key_s = 0;
	if (keycode == KEY_D)
		eng->event.key_d = 0;
	if (keycode == KEY_A)
		eng->event.key_a = 0;
	if (keycode == KEY_LEFT)
		eng->event.key_left = 0;
	if (keycode == KEY_RIGTH)
		eng->event.key_rigth = 0;
	return (0);
}

int	mouse(int x, int y, t_eng *eng) //função que deteta movimentos do mouse
{
	if (eng->event.key_shift)
		return (1);
	mlx_mouse_hide(eng->mlx_ptr, eng->win_ptr);
	if (y != screenHeight / 2 || x != screenWidth / 2)
	{
		if (y > screenHeight / 2 && eng->event.screen_y > (screenHeight * -0.5))
			eng->event.screen_y -= (y - screenHeight / 2);
		else if (y < screenHeight / 2 && eng->event.screen_y < (screenHeight * 0.5))
			eng->event.screen_y += (screenHeight / 2 - y);
		if (x > screenWidth / 2)
			eng->event.key_rigth = x - screenWidth / 2;
		else if (x < screenWidth / 2)
			eng->event.key_left = screenWidth / 2 - x;
		mlx_mouse_move(eng->mlx_ptr, eng->win_ptr, screenWidth / 2, screenHeight / 2);
	}
	return(0);
}

void	ft_start_engine(t_file *file)
{
	t_eng	eng;

	//Inicialização de variaveis
	eng.file = file;
	eng.player.posx = get_map_pos(eng.file->map, 'x') + 0.5;	//x start position + 0.5 to center
	eng.player.posy = get_map_pos(eng.file->map, 'y') + 0.5;  //y start position + 0.5 to center
	if (eng.file->map[(int)eng.player.posy][(int)eng.player.posx] == 'N')
	{
		eng.player.dirx = 0;	//initial direction vector
		eng.player.diry = -1; 	//initial direction vector
		eng.player.planex = 0.66;		//the 2d raycaster version of camera plane
		eng.player.planey = 0; //the 2d raycaster version of camera plane
	}
	if (eng.file->map[(int)eng.player.posy][(int)eng.player.posx] == 'S')
	{
		eng.player.dirx = 0;	//initial direction vector
		eng.player.diry = 1; 	//initial direction vector
		eng.player.planex = -0.66;		//the 2d raycaster version of camera plane
		eng.player.planey = 0; //the 2d raycaster version of camera plane
	}
	if (eng.file->map[(int)eng.player.posy][(int)eng.player.posx] == 'W')
	{
		eng.player.dirx = -1;	//initial direction vector
		eng.player.diry = 0; 	//initial direction vector
		eng.player.planex = 0;		//the 2d raycaster version of camera plane
		eng.player.planey = -0.66; //the 2d raycaster version of camera plane
	}
	if (eng.file->map[(int)eng.player.posy][(int)eng.player.posx] == 'E')
	{
		eng.player.dirx = 1;	//initial direction vector
		eng.player.diry = 0; 	//initial direction vector
		eng.player.planex = 0;		//the 2d raycaster version of camera plane
		eng.player.planey = 0.66; //the 2d raycaster version of camera plane
	}
	eng.file->map[(int)eng.player.posy][(int)eng.player.posx] = '0';// Apaga o jogador no map file pois já temos as posições do mesmo
	eng.world.world_time = 0; //time of current frame
	eng.world.last_time = 0; //time of previous frame
	eng.file->ceilling.rgb = rgb(eng.file->ceilling.red, eng.file->ceilling.green, eng.file->ceilling.blue); //junta a cor de 3 variavel em uma so
	eng.file->floor.rgb = rgb(eng.file->floor.red, eng.file->floor.green, eng.file->floor.blue); //junta a cor de 3 variavel em uma so
	eng.event.key_w = 0;
	eng.event.key_s = 0;
	eng.world.frames_rate = RATE_MAX;
	eng.event.key_d = 0;
	eng.event.key_a = 0;
	eng.event.key_left = 0;
	eng.event.key_rigth = 0;
	eng.event.key_shift = 1;
	eng.event.screen_y = 0;
	eng.world.fps_counter = 0;

	//começo do mlx
	eng.mlx_ptr = mlx_init();
	eng.win_ptr = mlx_new_window(eng.mlx_ptr, screenWidth, screenHeight, "Cub3D");

	//carregamento e criação de imagens e criado addr de cada imagem para obter a cor dos pixeis consoante a posição[y][x]
	eng.tex.tex[0] = mlx_xpm_file_to_image(eng.mlx_ptr, eng.file->_no, &eng.tex.img_width, &eng.tex.img_height);
	eng.tex.addr[0] = mlx_get_data_addr(eng.tex.tex[0], &eng.tex.bits_per_pixel, &eng.tex.line_length, &eng.tex.endian);
	eng.tex.tex[1] = mlx_xpm_file_to_image(eng.mlx_ptr, eng.file->_so, &eng.tex.img_width, &eng.tex.img_height);
	eng.tex.addr[1] = mlx_get_data_addr(eng.tex.tex[1], &eng.tex.bits_per_pixel, &eng.tex.line_length, &eng.tex.endian);
	eng.tex.tex[2] = mlx_xpm_file_to_image(eng.mlx_ptr, eng.file->_we, &eng.tex.img_width, &eng.tex.img_height);
	eng.tex.addr[2] = mlx_get_data_addr(eng.tex.tex[2], &eng.tex.bits_per_pixel, &eng.tex.line_length, &eng.tex.endian);
	eng.tex.tex[3] = mlx_xpm_file_to_image(eng.mlx_ptr, eng.file->_ea, &eng.tex.img_width, &eng.tex.img_height);
	eng.tex.addr[3] = mlx_get_data_addr(eng.tex.tex[3], &eng.tex.bits_per_pixel, &eng.tex.line_length, &eng.tex.endian);
	eng.canva.img = mlx_new_image(eng.mlx_ptr, screenWidth, screenHeight); //Esta imagem é o que será apresentado na tela no final do update()
	eng.canva.addr = mlx_get_data_addr(eng.canva.img, &eng.canva.bits_per_pixel, &eng.canva.line_length, &eng.canva.endian);
	
	//Funções de eventos
	mlx_hook(eng.win_ptr, 6, (1L<<6), mouse, &eng); //ativa sistema de movimentação do mouse
	mlx_loop_hook(eng.mlx_ptr, update, &eng); //construcao do raycast
	mlx_hook(eng.win_ptr, 17, 0, ft_close, &eng); //ativa o evento de botão fechar
	mlx_hook(eng.win_ptr, 2, 1L<<0, keytest, &eng); //ativa as variaveis das teclas
	mlx_hook(eng.win_ptr, 3, 1L<<1, keytestout, &eng); //desativa as variaveis das teclas
	mlx_loop(eng.mlx_ptr);
}
