static int	ft_get_longest_line(char **matrix)
{
	int	j;
	int	longest;

	longest = INT_MIN;
	while (*matrix)
	{
		j = 0;
		while ((*matrix)[j])
			j++;
		if (j > longest)
			longest = j;
		matrix++;
	}
	return (longest);
}

static void	add_og_map(char **map, char ***map_cpy)
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

static char	**get_map_cpy(char **map)
{
	int		i;
	int		j;
	int		map_heigh;
	int		map_width;
	char	**map_cpy;

	map_heigh = ft_get_matrix_size(map);
	map_width = ft_get_longest_line(map);
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
	add_og_map(map, &map_cpy);
	return (map_cpy);
}

static void	check_walls(char **map_cpy)
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
					raise_error("Map must not be open");
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

static enum e_values	identify_line_value(char *line)
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
	return (ERROR);
}

/**
 * Get the RGB value from the floor and ceiling parameters. If and invalid value
 * is found an error is raised.
*/
static t_color	get_color_value(char *line)
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
		raise_error("Empty value found for floor or ceiling.");
	values = ft_split(aux, ',');
	if (ft_get_matrix_size(values) != 3)
		raise_error("Value for colors must be in R,G,B");
	if (!ft_strisnum(values[0]) || !ft_strisnum(values[1])
		|| !ft_strisnum(values[2]))
		raise_error("Non numeric value found in floor or ceiling.");
	color.red = ft_atoi(values[0]);
	color.green = ft_atoi(values[1]);
	color.blue = ft_atoi(values[2]);
	if (color.red > 255 || color.green > 255 || color.blue > 255
		|| color.red < 0 || color.green < 0 || color.blue < 0)
		raise_error("Value for colors must be between 0 and 255");
	(free(aux), free_matrix(values));
	return (color);
}

static char	*get_texture_value(char *line)
{
	char	*texture_path;

	while (*line && (*line == ' ' || *line == '	'))
		line++;
	line += 2;
	texture_path = ft_strtrim(line, " 	");
	if (!ft_strlen(texture_path))
		raise_error("Empty value found for wall textures");
	return (texture_path);
}

/**
 * The first 6 rows must contain the map values: wall textures, floor and
 * ceiling colours. If an invalid value is found an error is raised.
 */
void	get_values(t_game *game, char **file_con)
{
	int				i;
	enum e_values	value_type;

	i = -1;
	while (++i < 6)
	{
		if (!file_con[i])
			raise_error("Missing values for textures and colors");
		value_type = identify_line_value(file_con[i]);
		if (value_type == ERROR)
			raise_error("Invalid value for textures and colors");
		if (value_type == NO)
			game->map_data.texture_no = get_texture_value(file_con[i]);
		else if (value_type == SO)
			game->map_data.texture_so = get_texture_value(file_con[i]);
		else if (value_type == WE)
			game->map_data.texture_we = get_texture_value(file_con[i]);
		else if (value_type == EA)
			game->map_data.texture_ea = get_texture_value(file_con[i]);
		else if (value_type == C)
			game->map_data.ceiling = get_color_value(file_con[i]);
		else if (value_type == F)
			game->map_data.floor = get_color_value(file_con[i]);
	}
}

static int	check_chars(t_game *game, char value, int x, int y)
{
	if (value != '1' && value != '0' && value != 'N'
		&& value != 'S' && value != 'E' && value != 'W' && value != ' ')
		raise_error("Invalid value found in map");
	if (value == 'N' || value == 'S' || value == 'E' || value == 'W')
	{
		game->player.y = (x * WALL_SIZE) + WALL_SIZE / 2;
		game->cam.grid_y = y;
		game->player.x = (y * WALL_SIZE) + WALL_SIZE / 2;
		game->cam.grid_x = x;
		return (1);
	}
	return (0);
}

static void	check_map_chars(t_game *game, char **map)
{
	int	x;
	int	y;
	int	player_flag;

	y = -1;
	player_flag = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			player_flag += check_chars(game, map[y][x], x, y);
	}
	if (player_flag > 1)
		raise_error("Mutiple players found");
	if (!player_flag)
		raise_error("No player position found");
}

void	parsing(char **argv, t_game *game)
{
	char	**file_content;
	char	**map;

	file_content = read_file(argv);
	get_values(game, file_content);
	map = file_content + 6;
	check_map_chars(game, map);
	check_closed_walls(map);
	game->map = map;
}

static void	check_extension(char **argv)
{
	char	*file_ext;

	file_ext = ft_strrchr(argv[1], '.');
	if (!file_ext || ft_strncmp(file_ext + 1, "cub", ft_strlen(argv[1])) != 0)
		raise_error("Map with invalid extension.");
}

static void	check_map_empty_line(char *line)
{
	static unsigned int	count = 0;
	static int			flag_enter = 0;
	static int			flag_exit = 0;

	if (count == 6 && ft_strlen(line) > 1 && !flag_enter)
		flag_enter = 1;
	if (count < 6 && ft_strlen(line) > 1)
		count++;
	if (flag_enter && ft_strlen(line) == 1 && !flag_exit)
		flag_exit++;
	if ((ft_strlen(line) > 1 || *line != '\n') && flag_exit)
		raise_error("Empty line in map");
}

static char	*get_lines(int fd)
{
	char	*file;
	char	*line;

	line = get_next_line(fd);
	file = ft_calloc(1, 1);
	if (!file)
		exit(1);
	while (line != NULL)
	{
		check_map_empty_line(line);
		file = ft_fstrjoin(file, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (file);
}

char	**read_file(char **argv)
{
	char	*file;
	int		fd;
	char	**file_con;

	check_extension(argv);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		raise_error("Error when opening file. Does the file exist?");
	if (read(fd, 0, 1) == 0)
		raise_error("Empty map file");
	file = get_lines(fd);
	close(fd);
	file_con = ft_split(file, '\n');
	free(file);
	return (file_con);
}