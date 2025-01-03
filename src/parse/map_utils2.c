/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 21:17:40 by daxferna          #+#    #+#             */
/*   Updated: 2025/01/01 02:52:17 by daxferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

int	count_fd_lines(int fd)
{
	char	*line;
	int		map_lines;

	map_lines = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		map_lines++;
		line = get_next_line(fd);
	}
	return (map_lines);
}

char	**dup_map(t_map game_map)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (game_map.height + 1));
	if (!new_map)
		return (NULL);
	i = 0;
	while (game_map.map[i])
	{
		new_map[i] = ft_strdup(game_map.map[i]);
		if (!new_map[i])
			return (free_map(new_map), NULL);
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

bool	is_map_rectangular(t_map *game_map)
{
	int		i;

	i = 0;
	while (game_map->map[i])
	{
		if (ft_strlen(game_map->map[i]) - 1 != game_map->width)
			return (false);
		i++;
	}
	return (true);
}

bool	is_map_closed(t_map *game_map)
{
	int	i;

	i = 0;
	if (!is_wall(game_map->map[0]))
		return (false);
	if (!is_wall(game_map->map[game_map->height - 1]))
		return (false);
	while (game_map->map[i])
	{
		if (game_map->map[i][0] != WALL)
			return (false);
		if (game_map->map[i][game_map->width - 1] != WALL)
			return (false);
		i++;
	}
	return (true);
}

void	dfs(char **map, int	pos_x, int pos_y, int *c, int *e)
{
	if (map[pos_y][pos_x] == '1' || map[pos_y][pos_x] == '#')
		return ;
	if (map[pos_y][pos_x] == 'C')
		(*c)++;
	if (map[pos_y][pos_x] == 'E')
		(*e)++;
	map[pos_y][pos_x] = '#';
	dfs(map, pos_x + 1, pos_y, c, e);
	dfs(map, pos_x - 1, pos_y, c, e);
	dfs(map, pos_x, pos_y + 1, c, e);
	dfs(map, pos_x, pos_y - 1, c, e);
}
