/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drubio-m <drubio-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:55:30 by drubio-m          #+#    #+#             */
/*   Updated: 2024/08/20 19:29:01 by drubio-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include <unistd.h> // Para access

void check_args(int argc, char **argv)
{
	if (argc != 2)
		ft_error("Invalid number of arguments");

	int len = ft_strlen(argv[1]);
	if (len < 4)
		ft_error("Argument too short to be valid");

	if (ft_strncmp(argv[1] + len - 4, ".cub", 4))
		ft_error("Invalid extension, must be \".cub\"");

	if (access(argv[1], F_OK) == -1)
		ft_error("File does not exist");

	if (access(argv[1], R_OK) == -1)
		ft_error("File is not readable");
}

void convert_map(char *argv, t_map *map)
{
	int		fd;
	char	*line;
	char	*map1_arr;
	char	*map2_arr;

	fd = open(argv, O_RDONLY);	
	map1_arr = ft_strdup("");
	while(1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map2_arr = ft_strdup(map1_arr);
		free(map1_arr);
		map1_arr = ft_strjoin2(map2_arr, line);
		free(line);
	}
	map->map = ft_split(map1_arr, '\n');
	
	free(map1_arr);
	close(fd);
}
