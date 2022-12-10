/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:07:35 by ede-alme          #+#    #+#             */
/*   Updated: 2022/12/10 15:04:46 by ede-alme         ###   ########.fr       */
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
  {1,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int	ft_close(t_eng *eng)
{
	mlx_destroy_image(eng->mlx_ptr, eng->tex.tex[0]);
	mlx_destroy_image(eng->mlx_ptr, eng->tex.tex[1]);
	mlx_destroy_image(eng->mlx_ptr, eng->tex.tex[2]);
	mlx_destroy_image(eng->mlx_ptr, eng->tex.tex[3]);
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

int	my_mlx_pixel_get(t_tex data, int x, int y, int tex)
{
	return (*(unsigned int*)(data.addr[tex] + (y * data.line_length + x * (data.bits_per_pixel / 8))));
}

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

void	verLine(t_eng *eng, int x, int drawStart, int drawEnd, int tex, double wallX)
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
		if (i <= drawStart)
			mlx_pixel_put(eng->mlx_ptr, eng->win_ptr, x, i, eng->file->ceilling.rgb);
		else if (i >= drawStart && i <= drawEnd)
			i = drawEnd;
		else
			mlx_pixel_put(eng->mlx_ptr, eng->win_ptr, x, i,  eng->file->floor.rgb);
	}
	if (drawStart >= 0)
		i = drawStart;
	else
		i = 0;
	while (i < screenHeight && i <= drawEnd)
	{
		percentage =  (float)(i - drawStart) / psize;
		mlx_pixel_put(eng->mlx_ptr, eng->win_ptr, x, i, my_mlx_pixel_get(eng->tex, xpercentage, percentage * 63, tex));
		i++;
	}
}


int	update(t_eng *eng)
{
	int	x = -1;//test

	fps(eng);
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
    	//if(drawStart < 0)
		//	drawStart = 0;
    	int drawEnd = lineHeight / 2 + screenHeight / 2;
    	//if(drawEnd >= screenHeight)
		//	drawEnd = screenHeight - 1;

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
					color = 3; // EA east texture
			else
				color = 2; //WE west texture
		}
		else
		{
			if (rayDirX > 0)
				color = 1; //SO south texture
			else
				color = 0; //NO north texture
		}
    	/*switch(worldMap[mapX][mapY])
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
    	}*/

    	//give x and y sides different brightness
    	//if(side == 1)
		//	color = color / 2;

    	//draw the pixels of the stripe as a vertical line
		//printf("Pos: %d		DrawStart: %d, DrawEnd: %d	Color: %d\n", x, drawStart, drawEnd, color);
    	verLine(eng, x, drawStart + eng->screen_y, drawEnd + eng->screen_y, color, wallX);
	}
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
    	if(worldMap[(int)(eng->posX + eng->dirX * moveSpeed)][(int)(eng->posY)] == 0)
	  		eng->posX += eng->dirX * moveSpeed;
    	if(worldMap[(int)(eng->posX)][(int)(eng->posY + eng->dirY * moveSpeed)] == 0)
			eng->posY += eng->dirY * moveSpeed;
		//eng->key_down = 0;
    }
	if(eng->key_S)//falta corrigir as direcoes
    {
    	if(worldMap[(int)(eng->posX - eng->dirX * moveSpeed)][(int)eng->posY] == 0)
			eng->posX -= eng->dirX * moveSpeed;
    	if(worldMap[(int)eng->posX][(int)(eng->posY - eng->dirY * moveSpeed)] == 0)
			eng->posY -= eng->dirY * moveSpeed;
		//eng->key_back = 0;
    }
	if(eng->key_D)
    {
    	//both camera direction and camera plane must be rotated
    	double oldDirX = eng->dirX;
    	eng->dirX = eng->dirX * cos(-rotSpeed * eng-> key_D) - eng->dirY * sin(-rotSpeed * eng-> key_D);
    	eng->dirY = oldDirX * sin(-rotSpeed * eng-> key_D) + eng->dirY * cos(-rotSpeed * eng-> key_D);
    	double oldPlaneX = eng->planeX;
    	eng->planeX = eng->planeX * cos(-rotSpeed * eng-> key_D) - eng->planeY * sin(-rotSpeed * eng-> key_D);
    	eng->planeY = oldPlaneX * sin(-rotSpeed * eng-> key_D) + eng->planeY * cos(-rotSpeed * eng-> key_D);
		//eng->key_D = 0;
    }
	if(eng->key_A)
    {
    	//both camera direction and camera plane must be rotated
    	double oldDirX = eng->dirX;
    	eng->dirX = eng->dirX * cos(rotSpeed * eng->key_A) - eng->dirY * sin(rotSpeed * eng->key_A);
    	eng->dirY = oldDirX * sin(rotSpeed * eng->key_A) + eng->dirY * cos(rotSpeed * eng->key_A);
    	double oldPlaneX = eng->planeX;
    	eng->planeX = eng->planeX * cos(rotSpeed * eng->key_A) - eng->planeY * sin(rotSpeed * eng->key_A);
    	eng->planeY = oldPlaneX * sin(rotSpeed * eng->key_A) + eng->planeY * cos(rotSpeed * eng->key_A);
		//eng->key_A = 0;
    }
	//mlx_mouse_move(eng->mlx_ptr, eng->win_ptr, screenWidth / 2, screenHeight / 2);
	//mlx_mouse_hide(eng->mlx_ptr, eng->win_ptr);
	return (0);
}

int	keytest(int keycode, t_eng *eng)
{
	if (keycode == SHIFT)
	{
		eng->key_shift = !eng->key_shift;
		if (eng->key_shift)
			mlx_mouse_show(eng->mlx_ptr, eng->win_ptr);
	}
	if (keycode == ESC)
		ft_close(eng);
	if (keycode == KEY_W)
		eng->key_W = 1;
	if (keycode == KEY_S)
		eng->key_S = 1;
	if (keycode == KEY_D)
		eng->key_D = 1;
	if (keycode == KEY_A)
		eng->key_A = 1;
	if (keycode == KEY_UP)
		eng->screen_y += 5;
	if (keycode == KEY_DOWN)
		eng->screen_y -= 5;
	return (0);
}

int	keytestout(int keycode, t_eng *eng)
{
	if (keycode == ESC)
		ft_close(eng);
	if (keycode == KEY_W)
		eng->key_W = 0;
	if (keycode == KEY_S)
		eng->key_S = 0;
	if (keycode == KEY_D)
		eng->key_D = 0;
	if (keycode == KEY_A)
		eng->key_A = 0;
	return (0);
}

int	mouse(int x, int y, t_eng *eng)
{
	if (eng->key_shift)
		return (1);
	mlx_mouse_hide(eng->mlx_ptr, eng->win_ptr);
	if (y != screenHeight / 2)
	{
		if (y > screenHeight / 2)
			eng->screen_y -= (y - screenHeight / 2) * 0.20 + 1;
		else
			eng->screen_y += (screenHeight / 2 - y) * 0.20 + 1;
		mlx_mouse_move(eng->mlx_ptr, eng->win_ptr, screenWidth / 2, screenHeight / 2);
	}
	if (x != screenWidth / 2)
	{
		if (x > screenWidth / 2)
			eng->key_D = (x - screenWidth / 2) * 0.10 + 1;
		else
			eng->key_A = (screenWidth / 2 - x) * 0.10 + 1;
		mlx_mouse_move(eng->mlx_ptr, eng->win_ptr, screenWidth / 2, screenHeight / 2);
	}
	else
	{
		eng->key_D = 0;
		eng->key_A = 0;
	}
	return(0);
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
	eng.file = file;
	eng.file->ceilling.rgb = rgb(eng.file->ceilling.red, eng.file->ceilling.green, eng.file->ceilling.blue);
	eng.file->floor.rgb = rgb(eng.file->floor.red, eng.file->floor.green, eng.file->floor.blue);

	eng.key_W = 0;
	eng.key_S = 0;
	eng.key_D= 0;
	eng.key_A = 0;
	eng.screen_y = 0;
	eng.fps = 0;
	eng.key_shift = 1;
	eng.mlx_ptr = mlx_init();
	eng.win_ptr = mlx_new_window(eng.mlx_ptr, screenWidth, screenHeight, "Cub3D");

	eng.tex.tex[0] = mlx_xpm_file_to_image(eng.mlx_ptr, eng.file->_no, &eng.tex.img_width, &eng.tex.img_height);
	eng.tex.addr[0] = mlx_get_data_addr(eng.tex.tex[0], &eng.tex.bits_per_pixel, &eng.tex.line_length, &eng.tex.endian);
	eng.tex.tex[1] = mlx_xpm_file_to_image(eng.mlx_ptr, eng.file->_so, &eng.tex.img_width, &eng.tex.img_height);
	eng.tex.addr[1] = mlx_get_data_addr(eng.tex.tex[1], &eng.tex.bits_per_pixel, &eng.tex.line_length, &eng.tex.endian);
	eng.tex.tex[2] = mlx_xpm_file_to_image(eng.mlx_ptr, eng.file->_we, &eng.tex.img_width, &eng.tex.img_height);
	eng.tex.addr[2] = mlx_get_data_addr(eng.tex.tex[2], &eng.tex.bits_per_pixel, &eng.tex.line_length, &eng.tex.endian);
	eng.tex.tex[3] = mlx_xpm_file_to_image(eng.mlx_ptr, eng.file->_ea, &eng.tex.img_width, &eng.tex.img_height);
	eng.tex.addr[3] = mlx_get_data_addr(eng.tex.tex[3], &eng.tex.bits_per_pixel, &eng.tex.line_length, &eng.tex.endian);
	
	//mlx_key_hook(eng.win_ptr, trigger, &eng);
	mlx_hook(eng.win_ptr, 6, (1L<<6), mouse, &eng);
	mlx_loop_hook(eng.mlx_ptr, update, &eng); //construcao do raycast
	mlx_hook(eng.win_ptr, 17, 0, ft_close, &eng);
	mlx_hook(eng.win_ptr, 2, 1L<<0, keytest, &eng);
	mlx_hook(eng.win_ptr, 3, 1L<<1, keytestout, &eng);
	mlx_loop(eng.mlx_ptr);
}
