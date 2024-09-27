/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-gu <fdiaz-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 22:00:45 by drubio-m          #+#    #+#             */
/*   Updated: 2024/09/27 15:43:20 by fdiaz-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_big_line(char **matrix)
{
	int	j;
	int	big_line;

	big_line = INT_MIN;
	while (*matrix)
	{
		j = 0;
		while ((*matrix)[j])
			j++;
		if (j > big_line)
			big_line = j;
		matrix++;
	}
	return (big_line);
}

void	set_map(char **map, char ***map_cpy)
{
	int	i;
	int	j;
	int	map_heigh;

	map_heigh = ft_get_matrix_size(map);
	i = 0;
	while (++i < map_heigh + 1)
	{
		j = 0;
		while (++j < (int)ft_strlen(map[i - 1]) + 1)
			(*map_cpy)[i][j] = map[i - 1][j - 1];
	}
}

char	**get_map_cpy(char **map)
{
	int		i;
	int		j;
	int		map_heigh;
	int		map_width;
	char	**map_cpy;

	map_heigh = ft_get_matrix_size(map);
	map_width = get_big_line(map);
	map_cpy = ft_calloc(map_heigh + 3, sizeof(char *));
	if (!map_cpy)
		exit(1);
	i = -1;
	while (++i < map_heigh + 2)
	{
		map_cpy[i] = ft_calloc(map_width + 3, sizeof(char));
		if (!map_cpy[i])
			exit(1);
		j = -1;
		while (++j < map_width + 2)
			map_cpy[i][j] = ' ';
		map_cpy[i][j] = '\0';
	}
	map_cpy[i] = NULL;
	set_map(map, &map_cpy);
	return (map_cpy);
}

void	check_walls(char **map_cpy)
{
	int	i;
	int	j;

	i = -1;
	while (++i < ft_get_matrix_size(map_cpy))
	{
		j = -1;
		while (++j < (int)ft_strlen(map_cpy[i]))
		{
			if (map_cpy[i][j] == '0' || map_cpy[i][j] == 'N' || map_cpy[i][j]
				== 'S' || map_cpy[i][j] == 'E' || map_cpy[i][j] == 'W')
			{
				if (map_cpy[i + 1][j] == ' ' || map_cpy[i - 1][j] == ' ' ||
					map_cpy[i][j + 1] == ' ' || map_cpy[i][j - 1] == ' ')
					ft_error("Map must be closed");
			}
		}
	}
}

void	check_closed_walls(char **map)
{
	char	**map_cpy;

	map_cpy = get_map_cpy(map);
	check_walls(map_cpy);
	free_matrix(map_cpy);
}
