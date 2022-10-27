/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:39:46 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/27 20:50:00 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (printf("Missing file path or to many arguments...\n"));
	if (ft_start_parse(argv[1]))
		exit(0);
	printf("Executou o mlx\n");
	//start_mlx;
	return (0);
}
