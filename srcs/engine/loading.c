/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 23:14:16 by ede-alme          #+#    #+#             */
/*   Updated: 2022/12/27 19:34:22 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

char	*ft_str_rep(char *str, int times)
{
	char	*load;
	int		i;

	i = -1;
	load = malloc(sizeof(char) * (ft_strlen(str) + times + 1));
	load[ft_strlen(str) + times] = 0;
	while (str[++i])
		load[i] = str[i];
	while (--times >= 0)
		load[ft_strlen(str) + times] = '.';
	return (load);
}

int	put_loading(int i, char *loading)
{
	static int	time;
	int			x;
	int			y;

	y = -1;
	time += (SCREENWIDTH * 0.1);
	loading = ft_str_rep("LOADING .", i);
	while (++y < SCREENHEIGHT)
	{
		x = -1;
		while (++x < SCREENWIDTH && y > SCREENHEIGHT * 0.4 && y < SCREENHEIGHT \
	* 0.5)
		{
			if (x < time)
				put_pixel_image(&engine()->canva, x, y, 16737280);
		}
	}
	usleep(100000);
	mlx_clear_window(engine()->mlx_ptr, engine()->win_ptr);
	mlx_put_image_to_window(engine()->mlx_ptr, engine()->win_ptr, \
engine()->canva.img, 0, 0);
	mlx_string_put(engine()->mlx_ptr, engine()->win_ptr, SCREENWIDTH * \
0.1, SCREENHEIGHT * 0.39, 16737280, loading);
	free(loading);
	return (1);
}
