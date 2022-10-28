/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:39:46 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/28 10:43:41 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_free_sfile(t_file *file)
{
	if (file->map)
		free(file->map);
	if (file->_ea)
		free(file->_ea);
	if (file->_no)
		free(file->_no);
	if (file->_so)
		free(file->_so);
	if (file->_we)
		free(file->_we);
	if (file->file_path)
		free(file->file_path);
	if (file->fd != -1)
		close(file->fd);
	return (1);
}

int	main(int argc, char **argv)
{
	t_file	file;

	if (argc != 2)
		return (printf("Missing file path or to many arguments...\n"));
	if (!ft_start_parse(&file, argv[1]))
	{
		printf("Executou o mlx\n");
		ft_free_sfile(&file);
		exit(0);
	}
	ft_free_sfile(&file);
	return (0);
}
