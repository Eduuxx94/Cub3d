/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-alme <ede-alme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:18:47 by ede-alme          #+#    #+#             */
/*   Updated: 2022/10/30 18:05:48 by ede-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

//'0' for walls and 'D' for doors// '.' for check player steps
int	ft_check_map(char **map, int x, int y)
{
	int	result;

	result = 0;
	map[y][x] = '.';
	if (map[y][x + 1] && map[y][x + 1] == ' ')
		return (printf("Check map error!\tline: '%s'\n", map[y]));
	if (map[y + 1][x] && map[y + 1][x] == ' ')
		return (printf("Check map error!\tline: '%s'\n", map[y + 1]));
	if (x - 1 >= 0 && map[y][x - 1] && map[y][x - 1] == ' ')
		return (printf("Check map error!\tline: '%s'\n", map[y]));
	if (y - 1 >= 0 && map[y - 1][x] && map[y - 1][x] == ' ')
		return (printf("Check map error!\tline: '%s'\n", map[y - 1]));
	if (map[y][x + 1] && (map[y][x + 1] == '0' || map[y][x + 1] == 'D'))
		result += ft_check_map(map, x + 1, y);
	if (map[y + 1][x] && (map[y + 1][x] == '0' || map[y + 1][x] == 'D'))
		result += ft_check_map(map, x, y + 1);
	if (y - 1 >= 0 && map[y - 1][x] && (map[y - 1][x] == '0' || \
		map[y - 1][x] == 'D'))
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

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	is_valid_map_obj(char c)
{
	if (c == '0' || c == ' ' || c == '1' || c == 'N' || c == 'S' || c == 'E' || \
		c == 'W')
		return (0);
	return (1);
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
	if (player == 0)
		return (printf("Check map error!\t'No player was found'\n"));
	else if (player > 1)
		return (printf("Check map error!\t'Was found %i players'\n", player));
	return (0);
}
