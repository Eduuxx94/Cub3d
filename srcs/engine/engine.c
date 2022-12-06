/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:07:35 by ede-alme          #+#    #+#             */
/*   Updated: 2022/12/06 21:32:26 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

#define screenHeight 900
#define screenWidth 1200
#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int	ft_close(t_eng *eng)
{
	mlx_loop_end(eng->mlx_ptr);
	mlx_clear_window(eng->mlx_ptr, eng->win_ptr);
	mlx_destroy_window(eng->mlx_ptr, eng->win_ptr);
	mlx_destroy_display(eng->mlx_ptr);
	ft_free_sfile(eng->file);
	free(eng->mlx_ptr);
	exit(0);
	return (0);
}

int	trigger(int keycode, t_eng *eng)
{
	if (keycode == ESC)
		ft_close(eng);
	return (0);
}

void	fps(t_eng *eng)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	if (current_time.tv_sec == eng->fps_time.tv_sec)
		eng->fps++;
	else if (printf("FPS: (%d)\n", eng->fps))
	{
		printf("\e[1;1H\e[2J");
		eng->fps = 0;
		gettimeofday(&eng->fps_time, NULL);
	}
}

void	verLine(t_eng *eng, int x, int drawStart, int drawEnd, int color)
{
	int	i;

	i = -1;
	while (++i <= screenHeight)
		if (i <= drawStart || i >= drawEnd)
			mlx_pixel_put(eng->mlx_ptr, eng->win_ptr, x, i, 0);
	while (drawStart < drawEnd)
	{
		mlx_pixel_put(eng->mlx_ptr, eng->win_ptr, x, drawStart, color);
		drawStart++;
	}
}

int	update(t_eng *eng)
{
	int	x = -1;//test

	//fps(eng);
	while (++x < screenWidth)
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
       		if(worldMap[mapX][mapY] > 0)
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
    	if(drawStart < 0)
			drawStart = 0;
    	int drawEnd = lineHeight / 2 + screenHeight / 2;
    	if(drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;

      	//choose wall color
    	int color;
    	switch(worldMap[mapX][mapY])
    	{
        	case 1:
				color = 16711680;
				break; //red
        	case 2:
				color = 65280;
				break; //green
        	case 3:
				color = 255;
				break; //blue
        	case 4:
				color = 16777215;
				break; //white
        	default:
				color = 16776960;
				break; //yellow
    	}

    	//give x and y sides different brightness
    	if(side == 1)
			color = color / 2;

    	//draw the pixels of the stripe as a vertical line
		//printf("Pos: %d		DrawStart: %d, DrawEnd: %d	Color: %d\n", x, drawStart, drawEnd, color);
    	verLine(eng, x, drawStart, drawEnd, color);
	}
	//timing for input and FPS counter
	struct timeval	current_time;
	gettimeofday(&current_time, NULL);
    eng->oldTime = eng->time;
    eng->time = 1000000 * current_time.tv_sec + current_time.tv_usec;//current_time.tv_usec;
    double frameTime = (eng->time - eng->oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
	//printf("Demorou %lf para desenhar tela\n", frameTime);
	//speed modifiers
    double moveSpeed = frameTime * 0.01; //the constant value is in squares/second
    double rotSpeed = frameTime * 0.002; //the constant value is in radians/second
	if(eng->key_down)//falta corrigir esta etapa
    {
    	if(worldMap[(int)(eng->posX + eng->dirX * moveSpeed)][(int)(eng->posY)] == 0)
	  		eng->posX += eng->dirX * moveSpeed;
    	if(worldMap[(int)(eng->posX)][(int)(eng->posY + eng->dirY * moveSpeed)] == 0)
			eng->posY += eng->dirY * moveSpeed;
		//eng->key_down = 0;
    }
	if(eng->key_back)//falta corrigir as direcoes
    {
    	if(worldMap[(int)(eng->posX - eng->dirX * moveSpeed)][(int)eng->posY] == 0)
			eng->posX -= eng->dirX * moveSpeed;
    	if(worldMap[(int)eng->posX][(int)(eng->posY - eng->dirY * moveSpeed)] == 0)
			eng->posY -= eng->dirY * moveSpeed;
		//eng->key_back = 0;
    }
	if(eng->key_rigth)
    {
    	//both camera direction and camera plane must be rotated
    	double oldDirX = eng->dirX;
    	eng->dirX = eng->dirX * cos(-rotSpeed) - eng->dirY * sin(-rotSpeed);
    	eng->dirY = oldDirX * sin(-rotSpeed) + eng->dirY * cos(-rotSpeed);
    	double oldPlaneX = eng->planeX;
    	eng->planeX = eng->planeX * cos(-rotSpeed) - eng->planeY * sin(-rotSpeed);
    	eng->planeY = oldPlaneX * sin(-rotSpeed) + eng->planeY * cos(-rotSpeed);
		//eng->key_rigth = 0;
    }
	if(eng->key_left)
    {
    	//both camera direction and camera plane must be rotated
    	double oldDirX = eng->dirX;
    	eng->dirX = eng->dirX * cos(rotSpeed) - eng->dirY * sin(rotSpeed);
    	eng->dirY = oldDirX * sin(rotSpeed) + eng->dirY * cos(rotSpeed);
    	double oldPlaneX = eng->planeX;
    	eng->planeX = eng->planeX * cos(rotSpeed) - eng->planeY * sin(rotSpeed);
    	eng->planeY = oldPlaneX * sin(rotSpeed) + eng->planeY * cos(rotSpeed);
		//eng->key_left = 0;
    }
	return (0);
}

int	keytest(int keycode, t_eng *eng)
{
	if (keycode == ESC)
		ft_close(eng);
	if (keycode == KEY_W)
	{
		eng->key_down = 1;
	}
	if (keycode == KEY_S)
		eng->key_back = 1;
	if (keycode == KEY_D)
		eng->key_rigth = 1;
	if (keycode == KEY_A)
		eng->key_left = 1;
	return (0);
}

int	keytestout(int keycode, t_eng *eng)
{
	if (keycode == ESC)
		ft_close(eng);
	if (keycode == KEY_W)
		eng->key_down = 0;
	if (keycode == KEY_S)
		eng->key_back = 0;
	if (keycode == KEY_D)
		eng->key_rigth = 0;
	if (keycode == KEY_A)
		eng->key_left = 0;
	return (0);
}

void	ft_start_engine(t_file *file)
{
	t_eng	eng;

	//all tests will be commented!
	eng.posX = 22;	//x and y start position
	eng.posY = 12;  //x and y start position
	eng.dirX = -1;	//initial direction vector
	eng.dirY = 0; 	//initial direction vector
	eng.planeX = 0;		//the 2d raycaster version of camera plane
	eng.planeY = 0.66; //the 2d raycaster version of camera plane
	eng.time = 0; //time of current frame
	eng.oldTime = 0; //time of previous frame

	eng.key_down = 0;
	eng.key_back = 0;
	eng.key_rigth= 0;
	eng.key_left = 0;
	eng.file = file;
	eng.fps = 0;
	eng.mlx_ptr = mlx_init();
	eng.win_ptr = mlx_new_window(eng.mlx_ptr, screenWidth, screenHeight, "Cub3D");
	mlx_hook(eng.win_ptr, 17, 0, ft_close, &eng);
	mlx_hook(eng.win_ptr, 2, 1L<<0, keytest, &eng);
	mlx_hook(eng.win_ptr, 3, 1L<<1, keytestout, &eng);
	//mlx_key_hook(eng.win_ptr, trigger, &eng);
	mlx_loop_hook(eng.mlx_ptr, update, &eng); //construcao do raycast
	mlx_loop(eng.mlx_ptr);
}
