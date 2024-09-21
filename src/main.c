/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drubio-m <drubio-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:55:51 by drubio-m          #+#    #+#             */
/*   Updated: 2024/09/21 21:37:25 by drubio-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void print_map(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (map->map[i][j])
		{
			ft_putchar_fd(map->map[i][j], 1); // Usa ft_putchar_fd para imprimir cada carácter.
			j++;
		}
		ft_putchar_fd('\n', 1); // Imprime un salto de línea después de cada fila.
		i++;
	}
}

/* int main(int argc, char **argv)
{
	t_map map;

	check_args(argc, argv);
	convert_map(argv[1], &map);
	print_map(&map);
	return (0);
} */

int main(int argc, char **argv)
{
	char **file_content;
	//int i = 0;

	// Llama a check_args para procesar el archivo.
	file_content = check_args(argc, argv);

	// Imprime el contenido del archivo procesado.
/* 	for (i = 0; file_content[i] != NULL; i++)
	{
		printf("%s\n", file_content[i]);
		free(file_content[i]); // Libera la memoria de cada línea.
	} */
	free(file_content); // Libera el arreglo de punteros.

	return 0;
}
