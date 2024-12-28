/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daxferna <daxferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:17:07 by daxferna          #+#    #+#             */
/*   Updated: 2024/12/28 20:46:44 by daxferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

bool	map_to_matrix(int fd, t_map *game_map)
{
	char	*line;
	int		i;
	int		line_len;

	game_map->map = malloc((sizeof(char *) * (game_map->height + 1)));
	if (!game_map->map)
		return (false);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		line_len = ft_strlen(line);
		(game_map->map)[i] = malloc(line_len + 1);
		if (!(game_map->map)[i])
			return (free_map(game_map->map), free(line), false);
		ft_strlcpy((game_map->map)[i++], line, line_len + 1);
		free(line);
		line = get_next_line(fd);
	}
	(game_map->map)[i] = NULL;
	game_map->width = line_len - 1;
	return (true);
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
	int		i;

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

bool	is_map_solvable(t_map *game_map)
{
	if (!has_exit_and_player(game_map))
		return (false);
	if (!has_collectibles(game_map))
		return (false);
	return (true);
}

bool	is_map_valid(char	*arg, t_map	*game_map)
{
	int		fd;
	int		map_lines;

	fd = open(arg, O_RDONLY);
	if (fd < 0)
		return (false);
	game_map->height = count_fd_lines(fd);
	close(fd);
	if (game_map->height < 3)
		return (false);
	fd = open(arg, O_RDONLY);
	if (fd < 0)
		return (false);
	if (!map_to_matrix(fd, game_map))
		return (close(fd), false);
	close(fd);
	if (!game_map->map)
		return (false);
	if (!is_map_rectangular(game_map) || !is_map_closed(game_map))
		return (free_map(game_map->map), false);
	if (!is_map_solvable(game_map))
		return (free_map(game_map->map), false);
	return (true);
}
