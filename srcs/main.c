/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:39:46 by ede-alme          #+#    #+#             */
/*   Updated: 2022/11/30 18:33:26 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_free_sfile(t_file *file)
{
	char	**temp;

	if (file->map)
	{
		temp = file->map;
		while (*file->map)
			free(*(file->map++));
		free(temp);
	}
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
	static t_file	file;
	t_game			game;

	ft_memset(&game, 0, sizeof(game));
	game.file = &file;
	if (argc != 2)
	{
		printf("Error.\nMissing file path or too many arguments.\n");
		exit(1);
	}
	//error check file?
	if (!ft_start_parse(game.file, argv[1]))
	{
		start_mlx(&game);
		hook_mlx(&game);
		mlx_loop(game.mlx.ptr);
		ft_free_sfile(game.file);
		return (0);
	}
	ft_free_sfile(game.file);
	return (0);
}
