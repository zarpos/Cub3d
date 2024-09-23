/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drubio-m <drubio-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:22:17 by drubio-m          #+#    #+#             */
/*   Updated: 2024/09/23 19:53:03 by drubio-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture read_texture(char *line)
{
	while (*line && (*line == ' ' || *line == '	'))
		line++;
	if (ft_strnstr(line, "NO ", 3) || ft_strnstr(line, "NO	", 3))
		return (NO);
	if (ft_strnstr(line, "SO ", 3) || ft_strnstr(line, "SO	", 3))
		return (SO); 
	if (ft_strnstr(line, "WE ", 3) || ft_strnstr(line, "WE	", 3))
		return (WE); 
	if (ft_strnstr(line, "EA ", 3) || ft_strnstr(line, "EA	", 3))
		return (EA); 
	if (ft_strnstr(line, "F ", 2) || ft_strnstr(line, "F	", 2))
		return (F);  
	if (ft_strnstr(line, "C ", 2) || ft_strnstr(line, "C	", 2))
		return (C);  
	return (Error);     
}

char	*get_texture(char *line)
{
	char	*texture_path;

	while (*line && (*line == ' ' || *line == '	'))
		line++;
	line += 2;
	texture_path = ft_strtrim(line, " 	");
	if (!ft_strlen(texture_path))
		ft_error("There are not textures for the walls!");
	return (texture_path);
}

t_color	read_colors(char *line)
{
	t_color	color;
	char	*aux;
	char	**values;

	color.alpha = 0;
	while (*line && (*line == ' ' || *line == '	'))
		line++;
	line++;
	aux = ft_strtrim(line, " 	");
	if (ft_strlen(aux) == 0)
		ft_error("Empty value for floor or ceiling.");
	values = ft_split(aux, ',');
	if (ft_get_matrix_size(values) != 3)
		ft_error("Value for colors must be in R,G,B");
	if (!ft_strisnum(values[0]) || !ft_strisnum(values[1])
		|| !ft_strisnum(values[2]))
		ft_error("Floor or ceiling value's are not numbers");
	color.red = ft_atoi(values[0]);
	color.green = ft_atoi(values[1]);
	color.blue = ft_atoi(values[2]);
	if (color.red > 255 || color.green > 255 || color.blue > 255
		|| color.red < 0 || color.green < 0 || color.blue < 0)
		ft_error("Value for colors must be between 0 and 255");
	(free(aux), free_matrix(values));
	return (color);
}

void	set_texture(t_game *game, char **file_con)
{
	int				i;
	enum e_texture	texture_type;

	i = -1;
	while (++i < 6)
	{
		if (!file_con[i])
			ft_error("Missing values for textures and colors");
		texture_type = read_texture(file_con[i]);
		if (texture_type == Error)
			ft_error("Invalid value for textures and colors");
		if (texture_type == NO)
			game->map_data.texture_no = get_texture(file_con[i]);
		else if (texture_type == SO)
			game->map_data.texture_so = get_texture(file_con[i]);
		else if (texture_type == WE)
			game->map_data.texture_we = get_texture(file_con[i]);
		else if (texture_type == EA)
			game->map_data.texture_ea = get_texture(file_con[i]);
		else if (texture_type == C)
			game->map_data.ceiling = read_colors(file_con[i]);
		else if (texture_type == F)
			game->map_data.floor = read_colors(file_con[i]);
	}
}
