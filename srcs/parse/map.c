/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:18:47 by ede-alme          #+#    #+#             */
/*   Updated: 2022/11/04 15:24:16 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	ft_player_range(char **map)
{
	int	pos_x;
	int	pos_y;
	int	y;
	int	x;

	y = -1;
	pos_x = get_map_pos(map, 'x');
	pos_y = get_map_pos(map, 'y');
	while (map[++y] && y <= pos_y)
	{
		x = -1;
		while (map[y][++x])
			;
		if (y == pos_y && y > 0 && pos_x > (int)utils().strlen(map[y - 1]))
			return (printf("Check map error!\t'Check top of player edges.'\n"));
	}
	x = -1;
	if (!map[y] || pos_y == 0 || pos_x == 0)
		return (printf("Check map error!\t'Player cannot stand on the edges'\n"));
	while (map[y][++x])
		if (x >= pos_x)
			return (0);
	return (printf("Check map error!\t'Check bottom of player edges.'\n"));
}

//'0' for walls and 'D' for doors// '.' for check player steps
int	ft_check_map(char **map, int x, int y)
{
	int	result;

	result = 0;
	map[y][x] = '.';
	if (map[y][x + 1] && map[y][x + 1] == ' ')
		return (1);
	if (map[y + 1] && ((int)ft_strlen(map[y + 1]) < x || map[y + 1][x] == ' '))
		return (1);
	if (x - 1 >= 0 && map[y][x - 1] && map[y][x - 1] == ' ')
		return (1);
	if (y - 1 >= 0 && ((int)ft_strlen(map[y - 1]) < x || map[y - 1][x] == ' '))
		return (1);
	if (map[y][x + 1] && (map[y][x + 1] == '0' || map[y][x + 1] == 'D'))
		result += ft_check_map(map, x + 1, y);
	if (map[y + 1] && (int)ft_strlen(map[y + 1]) > x && (map[y + 1][x] == '0' \
		|| map[y + 1][x] == 'D'))
		result += ft_check_map(map, x, y + 1);
	if (y - 1 >= 0 && (int)ft_strlen(map[y - 1]) > x && (map[y - 1][x] == '0' \
		|| map[y - 1][x] == 'D'))
		result += ft_check_map(map, x, y - 1);
	if (x - 1 >= 0 && map[y][x - 1] && (map[y][x - 1] == '0' || \
		map[y][x - 1] == 'D'))
		result += ft_check_map(map, x - 1, y);
	return (result);
}

int	get_map_pos(char **map, char pos)
{
	int	x;
	int	y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (is_player(map[y][x]))
			{
				if (pos == 'y')
					return (y);
				else if (pos == 'x')
					return (x);
			}
		}
	}
	return (0);
}

int	ft_map_player_count(char **map)
{
	int	x;
	int	y;
	int	player;

	y = -1;
	player = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '\n')
				map[y][x] = ' ';
			if (is_valid_map_obj(map[y][x]))
				return (printf("Check map error!\t'%c' Is invalid\n", map[y][x]));
			if (is_player(map[y][x]))
				player++;
		}
	}
	if (player == 1 && ft_player_range(map))
		return (1);
	else if (player != 1)
		return (printf("Check map error!\t'Player chars in map: %i!'\n", player));
	return (0);
}
