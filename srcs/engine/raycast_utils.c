/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 20:11:16 by ede-alme          #+#    #+#             */
/*   Updated: 2022/12/27 18:57:30 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

//Retorna a cor da imagem na posição tex[y][x]
int	get_pixel_image(t_tex tex, int x, int y, int id)
{
	return (*(unsigned int *)(tex.addr[id] + (y * tex.line_length + \
x * (tex.bits_per_pixel / 8))));
}

//Adiciona um pixel na imagem da posicao imagem[x][y] com a o valor color
void	put_pixel_image(t_canva *canva, int x, int y, int color)
{
	char	*dst;

	dst = canva->addr + (y * canva->line_length + x * (canva->bits_per_pixel \
	/ 8));
	*(unsigned int *)dst = color;
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
	while (++i <= SCREENHEIGHT)
	{
		if (i < drawstart)
			put_pixel_image(&eng->canva, x, i, eng->file->ceilling.rgb);
		else if (i < drawend)
			put_pixel_image(&eng->canva, x, i, get_pixel_image(eng->tex, \
xpercentage, (float)(i - drawstart) / psize * eng->tex.img_height, \
eng->raycast.texture));
		else
			put_pixel_image(&eng->canva, x, i, eng->file->floor.rgb);
	}
}

int	get_dir(int value)
{
	int	dir;

	if (value >= 0)
		dir = 1 * 0.1;
	else
		dir = -1 * 0.1;
	return (dir);
}
