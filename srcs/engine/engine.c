/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:07:35 by ede-alme          #+#    #+#             */
/*   Updated: 2022/12/13 22:56:07 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

#define screenHeight 1200
#define screenWidth 1920

int	ft_close(t_eng *eng)//Esta função é responsavel em dar free em todos os ponteiros do mlx e da struct file do parse
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

void	show_fps(t_eng *eng)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	if (current_time.tv_sec == eng->world.timer.tv_sec)//em quanto o segundo (current_time) for igual ao segundo do timer(relogio do jogo) vai contar os fps(frames por segundo)
		eng->world.fps_counter++;
	else if (printf("world.fps_counter: (%d)\n", eng->world.fps_counter))
	{
		printf("\e[1;1H\e[2J");
		eng->world.fps_counter = 0;
		gettimeofday(&eng->world.timer, NULL);//Rélogio do jogo vai atualizar pois um segundo se passou
	}
}

int	get_pixel_image(t_eng *eng, int x, int y, int tex)
{
	return (*(unsigned int*)(eng->tex.addr[tex] + (y * eng->tex.line_length + x * (eng->tex.bits_per_pixel / 8))));//esta função retorna a cor da textura na posição tex[y][x]
}

void	put_pixel_image(t_canva *canva, int x, int y, int color)
{
	char	*dst;

	dst = canva->addr + (y * canva->line_length + x * (canva->bits_per_pixel / 8));//esta função vai pintar um pixel numa imagem[y][x] consoante a referencia de um addr
	*(unsigned int*)dst = color;
}

int	rgb(int r, int g, int b)
{
	int	result;

	result = 0 | r;
	result = result << 8;
	result = result | g;
	result = result << 8;
	result = result | b;
	return (result);//esta função irá ser acrescentada no parse, função destinada à junção das cores R G B para uma unica variavel (int)
}

void	paint_vertical(t_eng *eng, int x, int drawstart, int drawend)//esta função pinta o canva(imagem) que será mostrada na tela 
{
	int		i;
	int		xpercentage;
	int		psize;

	i = -1;
	psize = drawend - drawstart;
	xpercentage = eng->raycast.wallx * 64;

	while (++i <= screenHeight)
	{
		if (i < drawstart)
			put_pixel_image(&eng->canva, x, i, eng->file->ceilling.rgb);//Será pintado um pixel[y][x] com a cor do ceiling no canva
		else if (i < drawend)
			put_pixel_image(&eng->canva, x, i, get_pixel_image(eng, xpercentage, (float)(i - drawstart) / psize * eng->tex.img_width, eng->raycast.texture));//será pintado um pixel[y][x] com a cor da textura[y][x] selecionada (int tex)
		else
			put_pixel_image(&eng->canva, x, i, eng->file->floor.rgb);//Será pintado um pixel[y][x] com a cor do floor no canva
	}
}


int	update(t_eng *eng)//função de atualização de tela
{
	int	x = screenWidth;//x corresponde à posição maxima x da tela, ou seja a imagem será pintada do fim ao inicio.
	struct timeval	current_time;

	//timing for input and fps_counter counter
	gettimeofday(&current_time, NULL);
    eng->world.world_time = 1000000 * current_time.tv_sec + current_time.tv_usec;//current_time.tv_usec;
	if (eng->world.world_time - eng->world.last_time > eng->world.frames_rate)
	{
		show_fps(eng);
		eng->event.frame_time = (eng->world.world_time - eng->world.last_time) / 1000.0; //eng->event.frame_time is the time this frame has taken, in seconds
		eng->world.last_time = eng->world.world_time;
		while (--x)
		{
			//calculate ray position and direction
			eng->raycast.camerax = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
			eng->raycast.raydirx = eng->player.dirx + eng->player.planex * eng->raycast.camerax;
			eng->raycast.raydiry = eng->player.diry + eng->player.planey * eng->raycast.camerax;
			//which box of the map we're in
			eng->raycast.mapx = eng->player.posx;
			eng->raycast.mapy = eng->player.posy;

			//length of ray from current position to next x or y-side
			if (eng->raycast.raydirx == 0)
				eng->raycast.deltadistx = 1e30;
			else
				eng->raycast.deltadistx = fabs(1 / eng->raycast.raydirx); //talvez esteja errado
			if (eng->raycast.raydiry == 0)
				eng->raycast.deltadisty = 1e30;
			else
				eng->raycast.deltadisty = fabs(1 / eng->raycast.raydiry); //talvez esteja errado
			//what direction to step in x or y-direction (either +1 or -1)
			eng->raycast.hit = 0; //was there a wall hit?
			//calculate step and initial sideDist
			if(eng->raycast.raydirx < 0)
			{
				eng->raycast.stepx = -1;
				eng->raycast.sidedistx = (eng->player.posx - (double)eng->raycast.mapx) * eng->raycast.deltadistx;
			}
			else
			{
				eng->raycast.stepx = 1;
				eng->raycast.sidedistx = ((double)eng->raycast.mapx + 1.0 - eng->player.posx) * eng->raycast.deltadistx;
			}
			if(eng->raycast.raydiry < 0)
			{
				eng->raycast.stepy = -1;
				eng->raycast.sidedisty = (eng->player.posy - (double)eng->raycast.mapy) * eng->raycast.deltadisty;
			}
			else
			{
				eng->raycast.stepy = 1;
				eng->raycast.sidedisty = ((double)eng->raycast.mapy + 1.0 - eng->player.posy) * eng->raycast.deltadisty;
			}
			//perform DDA
			while(eng->raycast.hit == 0)
			{
				//jump to next map square, either in x-direction, or in y-direction
				if(eng->raycast.sidedistx < eng->raycast.sidedisty)
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
				//Check if ray has hit a wall
				if(eng->file->map[eng->raycast.mapy][eng->raycast.mapx] != '0')
					eng->raycast.hit = 1;
			}
			//Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
			//hit to the camera plane. Euclidean to center camera point would give fisheye effect!
			//This can be computed as (eng->raycast.mapx - posX + (1 - eng->raycast.stepx) / 2) / eng->raycast.raydirx for side == 0, or same formula with Y
			//for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
			//because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
			//steps, but we subtract deltaDist once because one step more into the wall was taken above.
			if(eng->raycast.side == 0)
				eng->raycast.perpwalldist = (eng->raycast.sidedistx - eng->raycast.deltadistx);
			else
				eng->raycast.perpwalldist = (eng->raycast.sidedisty - eng->raycast.deltadisty);
			//Calculate height of line to draw on screen
			eng->raycast.lineheight = (screenHeight / eng->raycast.perpwalldist);
			//calculate lowest and highest pixel to fill in current stripe
			eng->raycast.drawstart = -eng->raycast.lineheight / 2 + screenHeight / 2;
			eng->raycast.drawend = eng->raycast.lineheight / 2 + screenHeight / 2;
			if(eng->raycast.side == 0)
				eng->raycast.wallx = eng->player.posy + eng->raycast.perpwalldist * eng->raycast.raydiry;
			else
				eng->raycast.wallx = eng->player.posx + eng->raycast.perpwalldist * eng->raycast.raydirx;
			eng->raycast.wallx -= floor((eng->raycast.wallx));
			//choose wall color
			if (eng->raycast.side) //Aqui sera escolhido qual textura sera mostrada exemplo: NO WE EA SO
			{
				if (eng->raycast.raydiry > 0)
						eng->raycast.texture = 0; // EA east texture
				else
					eng->raycast.texture = 1; //WE west texture
			}
			else
			{
				if (eng->raycast.raydirx > 0)
					eng->raycast.texture = 2; //SO south texture
				else
					eng->raycast.texture = 3; //NO north texture
			}
			paint_vertical(eng, x, eng->raycast.drawstart + eng->event.screen_y, eng->raycast.drawend + eng->event.screen_y);//draw the pixels of the stripe as a vertical line
		}
		mlx_put_image_to_window(eng->mlx_ptr, eng->win_ptr, eng->canva.img, 0, 0);
		//printf("Demorou %lf para desenhar tela\n", eng->event.frame_time);
		//speed modifiers
		eng->event.movespeed = eng->event.frame_time * 0.003; //the constant value is in squares/second
		eng->event.rotspeed = eng->event.frame_time * 0.00007; //the constant value is in radians/second
		if(eng->event.key_w)//falta corrigir esta etapa
		{
			if(eng->file->map[(int)(eng->player.posy)][(int)(eng->player.posx + eng->player.dirx * eng->event.movespeed)] == '0')
				eng->player.posx += eng->player.dirx * eng->event.movespeed;
			if(eng->file->map[(int)(eng->player.posy + eng->player.diry * eng->event.movespeed)][(int)(eng->player.posx)] == '0')
				eng->player.posy += eng->player.diry * eng->event.movespeed;
			//eng->event.key_down = 0;
		}
		if(eng->event.key_d)//falta corrigir as direcoes
		{
			eng->event.olddirx = eng->player.dirx;
			eng->player.dirx = eng->player.dirx * cos(1.57001) - eng->player.diry * sin(1.57001);
			eng->player.diry = eng->event.olddirx * sin(1.57001) + eng->player.diry * cos(1.57001);
			eng->event.oldplanex = eng->player.planex;
			eng->player.planex = eng->player.planex * cos(1.57001) - eng->player.planey * sin(1.57001);
			eng->player.planey = eng->event.oldplanex * sin(1.57001) + eng->player.planey * cos(1.57001);
			if(eng->file->map[(int)(eng->player.posy)][(int)(eng->player.posx + eng->player.dirx * eng->event.movespeed)] == '0')
				eng->player.posx += eng->player.dirx * (eng->event.movespeed * 0.5);
			if(eng->file->map[(int)(eng->player.posy + eng->player.diry * eng->event.movespeed)][(int)(eng->player.posx)] == '0')
				eng->player.posy += eng->player.diry * (eng->event.movespeed * 0.5);
			eng->event.olddirx = eng->player.dirx;
			eng->player.dirx = eng->player.dirx * cos(-1.57001) - eng->player.diry * sin(-1.57001);
			eng->player.diry = eng->event.olddirx * sin(-1.57001) + eng->player.diry * cos(-1.57001);
			eng->event.oldplanex = eng->player.planex;
			eng->player.planex = eng->player.planex * cos(-1.57001) - eng->player.planey * sin(-1.57001);
			eng->player.planey = eng->event.oldplanex * sin(-1.57001) + eng->player.planey * cos(-1.57001);
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
