/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drubio-m <drubio-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:55:30 by drubio-m          #+#    #+#             */
/*   Updated: 2024/09/21 21:46:23 by drubio-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include <unistd.h> // Para access

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
