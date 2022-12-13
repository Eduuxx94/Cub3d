/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:07:35 by ede-alme          #+#    #+#             */
/*   Updated: 2022/12/13 17:39:09 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

#define screenHeight 900
#define screenWidth 1200

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

void	fps(t_eng *eng)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	if (current_time.tv_sec == eng->timer.tv_sec)//em quanto o segundo (current_time) for igual ao segundo do timer(relogio do jogo) vai contar os fps(frames por segundo)
		eng->fps++;
	else if (printf("FPS: (%d)\n", eng->fps))
	{
		printf("\e[1;1H\e[2J");
		eng->fps = 0;
		gettimeofday(&eng->timer, NULL);//Rélogio do jogo vai atualizar pois um segundo se passou
	}
}

int	my_mlx_pixel_get(t_tex data, int x, int y, int tex)
{
	return (*(unsigned int*)(data.addr[tex] + (y * data.line_length + x * (data.bits_per_pixel / 8))));//esta função retorna a cor da textura na posição tex[y][x]
}

void	my_mlx_canva_put(t_canva *canva, int x, int y, int color)
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

void	verLine(t_eng *eng, int x, int drawStart, int drawEnd, int tex, double wallX)//esta função pinta o canva(imagem) que será mostrada na tela 
{
	float	percentage;
	int		i;
	int		xpercentage;
	int		psize;

	i = -1;
	psize = drawEnd - drawStart;
	xpercentage = wallX * 64;

	while (++i <= screenHeight)
	{
		if (i < drawStart)
			my_mlx_canva_put(&eng->canva, x, i, eng->file->ceilling.rgb);//Será pintado um pixel[y][x] com a cor do ceiling no canva
		else if (i >= drawStart && i < drawEnd)
		{
			percentage =  (float)(i - drawStart) / psize;
			my_mlx_canva_put(&eng->canva, x, i, my_mlx_pixel_get(eng->tex, xpercentage, percentage * eng->tex.img_width, tex));//será pintado um pixel[y][x] com a cor da textura[y][x] selecionada (int tex)
		}
		else
			my_mlx_canva_put(&eng->canva, x, i, eng->file->floor.rgb);//Será pintado um pixel[y][x] com a cor do floor no canva
	}
}


int	update(t_eng *eng)//função de atualização de tela
{
	int	x = screenWidth;//x corresponde à posição maxima x da tela, ou seja a imagem será pintada do fim ao inicio.

	fps(eng);
	while (--x)
	{
		//calculate ray position and direction
    	double cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
		double rayDirX = eng->dirX + eng->planeX * cameraX;
    	double rayDirY = eng->dirY + eng->planeY * cameraX;
    	//which box of the map we're in
    	int mapX = eng->posX;
    	int mapY = eng->posY;

    	//length of ray from current position to next x or y-side
    	double sideDistX;
    	double sideDistY;

		//length of ray from one x or y-side to next x or y-side
    	//these are derived as:
    	//deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
    	//deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
    	//which can be simplified to abs(|rayDir| / rayDirX) and abs(|rayDir| / rayDirY)
    	//where |rayDir| is the length of the vector (rayDirX, rayDirY). Its length,
    	//unlike (dirX, dirY) is not 1, however this does not matter, only the
    	//ratio between deltaDistX and deltaDistY matters, due to the way the DDA
    	//stepping further below works. So the values can be computed as below.
    	// Division through zero is prevented, even though technically that's not
    	// needed in C++ with IEEE 754 floating point values.
    	double deltaDistX;
    	double deltaDistY;
		if (rayDirX == 0)
			deltaDistX = 1e30;
		else
			deltaDistX = fabs(1 / rayDirX); //talvez esteja errado
		if (rayDirY == 0)
			deltaDistY = 1e30;
		else
			deltaDistY = fabs(1 / rayDirY); //talvez esteja errado
    	double perpWallDist; //testes aqui
		//what direction to step in x or y-direction (either +1 or -1)
    	int stepX;
    	int stepY;

      	int hit = 0; //was there a wall hit?
    	int side; //was a NS or a EW wall hit?
    	//calculate step and initial sideDist
    	if(rayDirX < 0)
      	{
        	stepX = -1;
    		sideDistX = (eng->posX - (double)mapX) * deltaDistX;
      	}
    	else
    	{
        	stepX = 1;
        	sideDistX = ((double)mapX + 1.0 - eng->posX) * deltaDistX;
      	}
    	if(rayDirY < 0)
    	{
        	stepY = -1;
       		sideDistY = (eng->posY - (double)mapY) * deltaDistY;
    	}
    	else
      	{
        	stepY = 1;
       		sideDistY = ((double)mapY + 1.0 - eng->posY) * deltaDistY;
      	}
		//perform DDA
		while(hit == 0)
    	{
        	//jump to next map square, either in x-direction, or in y-direction
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
        	//Check if ray has hit a wall
       		if(eng->file->map[mapY][mapX] != '0')
				hit = 1;
    	}
		//Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
    	//hit to the camera plane. Euclidean to center camera point would give fisheye effect!
    	//This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
    	//for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
    	//because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
    	//steps, but we subtract deltaDist once because one step more into the wall was taken above.
    	if(side == 0)
			perpWallDist = (sideDistX - deltaDistX);
    	else
			perpWallDist = (sideDistY - deltaDistY);
		//Calculate height of line to draw on screen
    	int lineHeight = (screenHeight / perpWallDist);
    	//calculate lowest and highest pixel to fill in current stripe
    	int drawStart = -lineHeight / 2 + screenHeight / 2;
    	int drawEnd = lineHeight / 2 + screenHeight / 2;
		double wallX; //where exactly the wall was hit
    	if(side == 0)
			wallX = eng->posY + perpWallDist * rayDirY;
		else
			wallX = eng->posX + perpWallDist * rayDirX;
    	wallX -= floor((wallX));
		if (x == 0)
		{
			x = 0;
			//printf("O valor da textura: %f\n", wallX); //o x da textura a ser pintado
		}
      	//choose wall color
    	int color;
		if (side)//Aqui sera escolhido qual textura sera mostrada exemplo: NO WE EA SO
		{
			if (rayDirY > 0)
					color = 0; // EA east texture
			else
				color = 1; //WE west texture
		}
		else
		{
			if (rayDirX > 0)
				color = 2; //SO south texture
			else
				color = 3; //NO north texture
		}
    	verLine(eng, x, drawStart + eng->screen_y, drawEnd + eng->screen_y, color, wallX);//draw the pixels of the stripe as a vertical line
	}
	mlx_put_image_to_window(eng->mlx_ptr, eng->win_ptr, eng->canva.img, 0, 0);
	//timing for input and FPS counter
	struct timeval	current_time;
	gettimeofday(&current_time, NULL);
    eng->oldTime = eng->time;
    eng->time = 1000000 * current_time.tv_sec + current_time.tv_usec;//current_time.tv_usec;
    double frameTime = (eng->time - eng->oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
	//printf("Demorou %lf para desenhar tela\n", frameTime);
	//speed modifiers
    double moveSpeed = frameTime * 0.005; //the constant value is in squares/second
    double rotSpeed = frameTime * 0.001; //the constant value is in radians/second
	if(eng->key_W)//falta corrigir esta etapa
    {
    	if(eng->file->map[(int)(eng->posY)][(int)(eng->posX + (eng->dirX * 15) * moveSpeed)] == '0')
	  		eng->posX += eng->dirX * moveSpeed;
    	if(eng->file->map[(int)(eng->posY + (eng->dirY * 15) * moveSpeed)][(int)(eng->posX)] == '0')
			eng->posY += eng->dirY * moveSpeed;
		//eng->key_down = 0;
    }
	if(eng->key_D)//falta corrigir as direcoes
    {
		double oldDirX = eng->dirX;
    	eng->dirX = eng->dirX * cos(1.57001) - eng->dirY * sin(1.57001);
    	eng->dirY = oldDirX * sin(1.57001) + eng->dirY * cos(1.57001);
    	double oldPlaneX = eng->planeX;
    	eng->planeX = eng->planeX * cos(1.57001) - eng->planeY * sin(1.57001);
    	eng->planeY = oldPlaneX * sin(1.57001) + eng->planeY * cos(1.57001);
		if(eng->file->map[(int)(eng->posY)][(int)(eng->posX + (eng->dirX * 15) * moveSpeed)] == '0')
	  		eng->posX += eng->dirX * (moveSpeed * 0.5);
    	if(eng->file->map[(int)(eng->posY + (eng->dirY * 15) * moveSpeed)][(int)(eng->posX)] == '0')
			eng->posY += eng->dirY * (moveSpeed * 0.5);
		oldDirX = eng->dirX;
    	eng->dirX = eng->dirX * cos(-1.57001) - eng->dirY * sin(-1.57001);
    	eng->dirY = oldDirX * sin(-1.57001) + eng->dirY * cos(-1.57001);
    	oldPlaneX = eng->planeX;
    	eng->planeX = eng->planeX * cos(-1.57001) - eng->planeY * sin(-1.57001);
    	eng->planeY = oldPlaneX * sin(-1.57001) + eng->planeY * cos(-1.57001);
    }
	if(eng->key_A)//falta corrigir esta etapa
    {
		double oldDirX = eng->dirX;
    	eng->dirX = eng->dirX * cos(-1.57001) - eng->dirY * sin(-1.57001);
    	eng->dirY = oldDirX * sin(-1.57001) + eng->dirY * cos(-1.57001);
    	double oldPlaneX = eng->planeX;
    	eng->planeX = eng->planeX * cos(-1.57001) - eng->planeY * sin(-1.57001);
    	eng->planeY = oldPlaneX * sin(-1.57001) + eng->planeY * cos(-1.57001);
		if(eng->file->map[(int)(eng->posY)][(int)(eng->posX + (eng->dirX * 15) * moveSpeed)] == '0')
	  		eng->posX += eng->dirX * (moveSpeed * 0.5);
    	if(eng->file->map[(int)(eng->posY + (eng->dirY * 15) * moveSpeed)][(int)(eng->posX)] == '0')
			eng->posY += eng->dirY * (moveSpeed * 0.5);
		oldDirX = eng->dirX;
    	eng->dirX = eng->dirX * cos(1.57001) - eng->dirY * sin(1.57001);
    	eng->dirY = oldDirX * sin(1.57001) + eng->dirY * cos(1.57001);
    	oldPlaneX = eng->planeX;
    	eng->planeX = eng->planeX * cos(1.57001) - eng->planeY * sin(1.57001);
    	eng->planeY = oldPlaneX * sin(1.57001) + eng->planeY * cos(1.57001);
    }
	if(eng->key_S)//falta corrigir as direcoes
    {
    	if(eng->file->map[(int)eng->posY][(int)(eng->posX - (eng->dirX * 15) * moveSpeed)] == '0')
			eng->posX -= eng->dirX * moveSpeed;
    	if(eng->file->map[(int)(eng->posY - (eng->dirY * 15) * moveSpeed)][(int)eng->posX] == '0')
			eng->posY -= eng->dirY * moveSpeed;
		//eng->key_back = 0;
    }
	if(eng->key_left)
    {
    	//both camera direction and camera plane must be rotated
    	double oldDirX = eng->dirX;
    	eng->dirX = eng->dirX * cos(-rotSpeed * eng-> key_left) - eng->dirY * sin(-rotSpeed * eng-> key_left);
    	eng->dirY = oldDirX * sin(-rotSpeed * eng-> key_left) + eng->dirY * cos(-rotSpeed * eng-> key_left);
    	double oldPlaneX = eng->planeX;
    	eng->planeX = eng->planeX * cos(-rotSpeed * eng-> key_left) - eng->planeY * sin(-rotSpeed * eng-> key_left);
    	eng->planeY = oldPlaneX * sin(-rotSpeed * eng-> key_left) + eng->planeY * cos(-rotSpeed * eng-> key_left);
		eng->key_left = 0;
    }
	if(eng->key_rigth)
    {
    	//both camera direction and camera plane must be rotated
    	double oldDirX = eng->dirX;
    	eng->dirX = eng->dirX * cos(rotSpeed * eng->key_rigth) - eng->dirY * sin(rotSpeed * eng->key_rigth);
    	eng->dirY = oldDirX * sin(rotSpeed * eng->key_rigth) + eng->dirY * cos(rotSpeed * eng->key_rigth);
    	double oldPlaneX = eng->planeX;
    	eng->planeX = eng->planeX * cos(rotSpeed * eng->key_rigth) - eng->planeY * sin(rotSpeed * eng->key_rigth);
    	eng->planeY = oldPlaneX * sin(rotSpeed * eng->key_rigth) + eng->planeY * cos(rotSpeed * eng->key_rigth);
		eng->key_rigth = 0;
    }
	//mlx_mouse_move(eng->mlx_ptr, eng->win_ptr, screenWidth / 2, screenHeight / 2);
	//mlx_mouse_hide(eng->mlx_ptr, eng->win_ptr);
	return (0);
}

int	keytest(int keycode, t_eng *eng) //Esta função atualiza as variaveis para ativação de eventos
{
	if (keycode == SHIFT)
	{
		eng->key_shift = !eng->key_shift;
		if (eng->key_shift)
			mlx_mouse_show(eng->mlx_ptr, eng->win_ptr);
	}
	else if (keycode == ESC)
		ft_close(eng);
	else if (keycode == KEY_W)
		eng->key_W = 1;
	else if (keycode == KEY_S)
		eng->key_S = 1;
	else if (keycode == KEY_D)
		eng->key_D = 1;
	else if (keycode == KEY_A)
		eng->key_A = 1;
	else if (keycode == KEY_RIGTH)
		eng->key_rigth = 1;
	else if (keycode == KEY_LEFT)
		eng->key_left = 1;
	else if (keycode == KEY_UP && eng->screen_y < 400)
		eng->screen_y += 5;
	else if (keycode == KEY_DOWN && eng->screen_y > -400)
		eng->screen_y -= 5;
	return (0);
}

int	keytestout(int keycode, t_eng *eng)//esta função atualiza as variaveis para desativar eventos
{
	if (keycode == KEY_W)
		eng->key_W = 0;
	if (keycode == KEY_S)
		eng->key_S = 0;
	if (keycode == KEY_D)
		eng->key_D = 0;
	if (keycode == KEY_A)
		eng->key_A = 0;
	if (keycode == KEY_LEFT)
		eng->key_left = 0;
	if (keycode == KEY_RIGTH)
		eng->key_rigth = 0;
	return (0);
}

int	mouse(int x, int y, t_eng *eng) //função que deteta movimentos do mouse
{
	if (eng->key_shift)
		return (1);
	mlx_mouse_hide(eng->mlx_ptr, eng->win_ptr);
	if (y != screenHeight / 2 || x != screenWidth / 2)
	{
		if (y > screenHeight / 2 && eng->screen_y > -400)
			eng->screen_y -= (y - screenHeight / 2) * 0.20 + 1;
		else if (y < screenHeight / 2 && eng->screen_y < 400)
			eng->screen_y += (screenHeight / 2 - y) * 0.20 + 1;
		if (x > screenWidth / 2)
			eng->key_rigth += (x - screenWidth / 2) * 0.10 + 1;
		else if (x < screenWidth / 2)
			eng->key_left += (screenWidth / 2 - x) * 0.10 + 1;
		mlx_mouse_move(eng->mlx_ptr, eng->win_ptr, screenWidth / 2, screenHeight / 2);
	}
	return(0);
}

void	ft_start_engine(t_file *file)
{
	t_eng	eng;

	//Inicialização de variaveis
	eng.file = file;
	eng.posX = get_map_pos(eng.file->map, 'x') + 0.5;	//x start position + 0.5 to center
	eng.posY = get_map_pos(eng.file->map, 'y') + 0.5;  //y start position + 0.5 to center
	if (eng.file->map[(int)eng.posY][(int)eng.posX] == 'N')
	{
		eng.dirX = 0;	//initial direction vector
		eng.dirY = -1; 	//initial direction vector
		eng.planeX = 0.66;		//the 2d raycaster version of camera plane
		eng.planeY = 0; //the 2d raycaster version of camera plane
	}
	if (eng.file->map[(int)eng.posY][(int)eng.posX] == 'S')
	{
		eng.dirX = 0;	//initial direction vector
		eng.dirY = 1; 	//initial direction vector
		eng.planeX = -0.66;		//the 2d raycaster version of camera plane
		eng.planeY = 0; //the 2d raycaster version of camera plane
	}
	if (eng.file->map[(int)eng.posY][(int)eng.posX] == 'W')
	{
		eng.dirX = -1;	//initial direction vector
		eng.dirY = 0; 	//initial direction vector
		eng.planeX = 0;		//the 2d raycaster version of camera plane
		eng.planeY = -0.66; //the 2d raycaster version of camera plane
	}
	if (eng.file->map[(int)eng.posY][(int)eng.posX] == 'E')
	{
		eng.dirX = 1;	//initial direction vector
		eng.dirY = 0; 	//initial direction vector
		eng.planeX = 0;		//the 2d raycaster version of camera plane
		eng.planeY = 0.66; //the 2d raycaster version of camera plane
	}
	eng.file->map[(int)eng.posY][(int)eng.posX] = '0';// Apaga o jogador no map file pois já temos as posições do mesmo
	eng.time = 0; //time of current frame
	eng.oldTime = 0; //time of previous frame
	eng.file->ceilling.rgb = rgb(eng.file->ceilling.red, eng.file->ceilling.green, eng.file->ceilling.blue); //junta a cor de 3 variavel em uma so
	eng.file->floor.rgb = rgb(eng.file->floor.red, eng.file->floor.green, eng.file->floor.blue); //junta a cor de 3 variavel em uma so
	eng.key_W = 0;
	eng.key_S = 0;
	eng.key_D = 0;
	eng.key_A = 0;
	eng.key_left = 0;
	eng.key_rigth = 0;
	eng.screen_y = 0;
	eng.fps = 0;
	eng.key_shift = 1;
	
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
