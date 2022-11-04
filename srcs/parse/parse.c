/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:25:52 by ede-alme          #+#    #+#             */
/*   Updated: 2022/11/04 15:27:12 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	ft_get_map_alloc(t_file *file, int size)
{
	char	*temp;
	int		result;

	temp = get_next_line(file->fd);
	result = 0;
	while (size == 0 && ft_strisspace(temp))
	{
		free(temp);
		temp = get_next_line(file->fd);
	}
	if (!temp)
	{
		file->map = malloc(sizeof(char *) * (size + 1));
		if (!file->map)
			return (1);
	}
	else
		result = ft_get_map_alloc(file, (size + 1));
	if (result)
		free(temp);
	else
		file->map[size] = temp;
	return (result);
}

int	ft_file_map(t_file *file)
{
	char	**checkmap;

	checkmap = NULL;
	if (ft_get_map_alloc(file, 0) || ft_map_player_count(file->map))
		return (1);
	checkmap = utils().matrixdup((const char **)file->map);
	if (ft_check_map(checkmap, get_map_pos(file->map, 'x'), get_map_pos \
		(file->map, 'y')) && printf("Check map error!\t'Map not closed!'\n"))
	{
		utils().matrixfree(checkmap);
		return (1);
	}
	utils().matrixfree(checkmap);
	return (0);
}

int	ft_start_parse(t_file *file, char *file_path)
{
	if (ft_file_init(file, file_path) || ft_file_load_tiles(file))
		return (1);
	if (ft_check_file_colors(file) || ft_file_map(file))
		return (1);
	return (0);
}
