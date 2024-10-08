/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-gu <fdiaz-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:05:45 by drubio-m          #+#    #+#             */
/*   Updated: 2024/09/27 16:01:31 by fdiaz-gu         ###   ########.fr       */
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
	while (!ft_strchr2(aux, '\n') && bytes != 0)
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
