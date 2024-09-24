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

void	draw_foor_ceiling(t_game *game, t_parser *parser)
{
	game->map.ceil_hex = ((parser->ceil_col[0] & 0xFF) << 16) | \
		(parser->ceil_col[1] & 0xFF) << 8 | (parser->ceil_col[2] & 0xFF);
	game->map.floor_hex = ((parser->floor_col[0] & 0xFF) << 16) | \
		(parser->floor_col[1] & 0xFF) << 8 | (parser->floor_col[2] & 0xFF);
}

void	load_xpm(t_game *game, int *tex, char *path, t_img *img)
{
	int	x;
	int	y;

	y = 0;
	printf("PATH: %s\n", path);
	printf("W: %d\n", img->width);
	img->width = 64;
	printf("H: %d\n", img->height);
	img->height = 64;
	printf("MLX: %p\n", game->mlx);
	// exit(1);
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->width, \
		&img->height);
	if (!img->img)
		return ;
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->len, \
		&img->endian);
	if (!img->data || img->width != texWidth || img->height != texHeight)
		return ;
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

void	load_images(t_game *game, t_parser *data)
{
	t_img	img;

	load_xpm(game, game->texture[0], data->so, &img);
	load_xpm(game, game->texture[1], data->no, &img);
	load_xpm(game, game->texture[2], data->we, &img);
	load_xpm(game, game->texture[3], data->ea, &img);
}

void	handle_wall_imgs(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	game->texture = malloc(5 * sizeof(int *));
	if (!game->texture)
		return ;
	while (i < 4)
	{
		game->texture[i] = malloc(sizeof(int) * texWidth * texHeight + 1);
		if (!game->texture[i++])
			return ;
	}
	i = 0;
	while (j < 4)
	{
		j = 0;
		while (j < texHeight * texWidth)
		{
			game->texture[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	load_imgs(t_game *game, t_parser *parser)
{
	handle_wall_imgs(game);
	load_images(game, parser);
	draw_foor_ceiling(game, parser);
}
