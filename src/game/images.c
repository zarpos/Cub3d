/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:18:12 by marvin            #+#    #+#             */
/*   Updated: 2024/09/19 16:18:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_foor_ceiling(t_game *game)
{
	game->map_data.ceil_hex = ((game->map_data.ceiling.red & 0xFF) << 16) | \
		(game->map_data.ceiling.green & 0xFF) << 8 | \
		(game->map_data.ceiling.blue & 0xFF);
	game->map_data.floor_hex = ((game->map_data.floor.red & 0xFF) << 16) | \
		(game->map_data.floor.green & 0xFF) << 8 | \
		(game->map_data.floor.blue & 0xFF);
}

void	load_xpm(t_game *game, int *tex, char *path, t_img *img)
{
	int	x;
	int	y;

	y = 0;
	img->img = mlx_xpm_file_to_image(game->mlx, path, \
	&img->width, &img->height);
	if (!img->img)
		ft_error("Error al cargar la imagen");
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, \
	&img->len, &img->endian);
	if (!img->data || img->width != TEXWIDTH || img->height != TEXHEIGHT)
		ft_error("Error en la imagen");
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			tex[img->width * y + x] = img->data[img->width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(game->mlx, img->img);
}

void	load_images(t_game *game)
{
	t_img	img;

	load_xpm(game, game->texture[0], game->map_data.so, &img);
	load_xpm(game, game->texture[1], game->map_data.no, &img);
	load_xpm(game, game->texture[2], game->map_data.we, &img);
	load_xpm(game, game->texture[3], game->map_data.ea, &img);
	free(game->map_data.so);
	free(game->map_data.no);
	free(game->map_data.we);
	free(game->map_data.ea);
}

void	handle_wall_imgs(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	game->texture = ft_calloc(5, sizeof(int *));
	if (!game->texture)
		return ;
	while (i < 4)
	{
		game->texture[i] = ft_calloc(sizeof(int), (TEXWIDTH * TEXHEIGHT + 1));
		if (!game->texture[i++])
			ft_error("Error en la texturas");
	}
	i = 0;
	while (j < 4)
	{
		j = 0;
		while (j < TEXHEIGHT * TEXWIDTH)
		{
			game->texture[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	load_imgs(t_game *game)
{
	handle_wall_imgs(game);
	load_images(game);
	draw_foor_ceiling(game);
}
