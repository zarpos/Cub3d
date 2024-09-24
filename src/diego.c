int check_chars(t_game *game, char value, int x, int y)
{
	if (value != '1' && value != '0' && value != 'N'
			&& value != 'S' && value != 'E' && value != 'W' && value != ' ')
		ft_error("Ivalid char detected");

	if (value == 'N' || value == 'S' || value == 'E' || value == 'W')
	{
		game->map_data.player_y = (y * WALL_SIZE) + (WALL_SIZE / 2);
		game->map_data.player_x = (x * WALL_SIZE) + (WALL_SIZE / 2);
		return (1);
	}
	return (0);
}

void check_map_chars(t_game *game, char **map)
{
	int x;
	int y;
	int player_flag;

	y = -1;
	player_flag = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			player_flag += check_chars(game, map[y][x], x, y);
	}
	if (player_flag > 1)
		ft_error("Multiple players found");
	if (!player_flag)
		ft_error("No player position found");
}

void parsing(int argc, char **argv, t_game *game)
{
	char **file_content;
	char **map;

	file_content = check_args(argc, argv);
	set_texture(game, file_content);
	map = file_content + 6;
	check_map_chars(game, map);
	check_closed_walls(map);
	game->map_data.map = map;
}

int	open_validated_file(char **argv)
{
	int		len;
	int		fd;
	char	*file_ext;
	char	buffer[1];

	len = ft_strlen(argv[1]);
	if (len < 4)
		ft_error("Argument too short to be valid");
	file_ext = ft_strrchr(argv[1], '.');
	if (!file_ext || ft_strncmp(file_ext + 1, "cub", 3) != 0)
		ft_error("Invalid extension, must be \".cub\"");
	if (access(argv[1], F_OK) == -1)
		ft_error("File does not exist");
	if (access(argv[1], R_OK) == -1)
		ft_error("File is not readable");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error("Error while opening file.");

	if (read(fd, buffer, 1) == 0)
		ft_error("Empty map file");
	return (fd);
}

char	**process_file(int fd)
{
	char	*file;
	char	**file_con;

	file = convert_lines(fd);
	close(fd);

	file_con = ft_split(file, '\n');
	free(file);

	return (file_con);
}

void	verify_blank_line(char *line)
{
	static unsigned int	count = 0;
	static int			enter = 0;
	static int			exit = 0;

	if (count == 6 && ft_strlen(line) > 1 && !enter)
		enter = 1;

	if (count < 6 && ft_strlen(line) > 1)
		count++;

	if (enter && ft_strlen(line) == 1 && !exit)
		exit++;

	if ((ft_strlen(line) > 1 || *line != '\n') && exit)
		ft_error("Empty line in map is not allowed.");
}

char	*convert_lines(int fd)
{
	char	*file;
	char	*line;

	line = get_next_line(fd);
	file = ft_calloc(1, 1);
	if (!file)
		exit(1);
	while (line != NULL)
	{
		verify_blank_line(line);
		file = ft_strjoin(file, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (file);
}

char	**check_args(int argc, char **argv)
{
	int		fd;
	char	**file_con;

	if (argc != 2)
		ft_error("Invalid number of arguments");
	fd = open_validated_file(argv);
	file_con = process_file(fd);

	return (file_con);
}

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