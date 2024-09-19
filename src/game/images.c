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

void init_texture_paths(t_game *game)
{
    game->path_texture[0] = MOSSY;
    game->path_texture[1] = PURPLE;
    game->path_texture[2] = BRICK;
    game->path_texture[3] = WOOD;

    // Puedes agregar validaciones para asegurar que las rutas no sean NULL
    for (int i = 0; i < 4; i++)
    {
        if (!game->path_texture[i])
        {
            printf("Error: Texture path at index %d is NULL.\n", i);
            exit(1); // Sale del programa en caso de error
        }
    }
}


bool ft_create_texture_buffer_from_img(t_game *game,
                                       t_img *img, int dir)
{
    int *pixels;
    int i;
    int j;

    pixels = malloc(sizeof(int) *( img->width * img->height));
    if (!pixels)
        return (false);
    i = -1;
    while (++i < img->height)
    {
        j = -1;
        while (++j < img->width)
            pixels[i * img->width + j] = img->addr[i * img->width + j];
    }
    game->texture_buffer[dir] = pixels;
    return (true);
}
bool load_textures(t_game *game)
{
    t_img tmp;
    int i;

    i = -1;
    while (++i < 4)
    {
        if (!game->path_texture[i]) {
            printf("Texture path at index %d is NULL.\n", i);
            return false;
        }
        printf("Loading texture from: %s\n", game->path_texture[i]);
        tmp.img = mlx_xpm_file_to_image(game->mlx,
                                        game->path_texture[i], &tmp.width, &tmp.height);
        if (!tmp.img) {
            printf("Failed to load texture from %s\n", game->path_texture[i]);
            return false;
        }

        printf("Loaded texture with dimensions: %d x %d\n", tmp.width, tmp.height);

        tmp.addr = (int *)mlx_get_data_addr(tmp.img,
                                            &tmp.bpp, &tmp.len, &tmp.endian);
        if (!tmp.addr) {
            printf("Failed to get data address for texture %s\n", game->path_texture[i]);
            mlx_destroy_image(game->mlx, tmp.img);
            return false;
        }

        if (!ft_create_texture_buffer_from_img(game, &tmp, i)) {
            printf("Failed to create texture buffer for %s\n", game->path_texture[i]);
            mlx_destroy_image(game->mlx, tmp.img);
            return false;
        }

        mlx_destroy_image(game->mlx, tmp.img);
    }
    return true;
}


// int get_texture_color(t_game *game, int dir, int x, int y)
// {
//     char *texture_data;
//     int color;

//     texture_data = game->texture_data[dir];
//     color = *(int *)(texture_data + (y * game->size_line[dir] + x * (game->bits_per_pixel[dir] / 8)));
//     return color;
// }
