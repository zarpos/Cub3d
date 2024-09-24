/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drubio-m <drubio-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:05:45 by drubio-m          #+#    #+#             */
/*   Updated: 2024/09/24 18:41:08 by drubio-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

char	*ft_write_in_aux(int fd, char *aux)
{
	char	*buff;
	int		bytes;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(aux, '\n') && bytes != 0)
	{	
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free (buff);
			return (NULL);
		}
		buff[bytes] = '\0';
		aux = ft_strjoin2(aux, buff);
	}
	free(buff);
	return (aux);
}

char	*get_next_line(int fd)
{
	char				*str;
	static char			*aux[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	aux[fd] = ft_write_in_aux(fd, aux[fd]);
	if (!aux[fd])
		return (NULL);
	str = ft_print_line(aux[fd]);
	aux[fd] = ft_new_static(aux[fd]);
	return (str);
}

/* int main(void)
{
	int fd1;
	char	*str;
	
	fd1 = open("/Users/diegorubio/Documents/42Cursus/Cub3d/maps/arena.cub", O_RDONLY);
	str = get_next_line(fd1);
	printf("%s\n", str);
	//str = get_next_line(fd1);
	//printf("%s\n", str);
	//str = get_next_line(fd1);
	//printf("%s\n", str);
	//str = get_next_line(fd1);
	//printf("%s\n", str);
	close(fd1);
	return (0);
} */

