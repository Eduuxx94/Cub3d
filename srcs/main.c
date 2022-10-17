/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:39:46 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/17 20:22:08 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(void)
{
    void	*mlx;
	void	*mlx_win;

	(void)mlx_win;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1200, 800, "Hello world!");
	mlx_loop(mlx);

}
