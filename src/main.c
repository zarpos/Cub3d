/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drubio-m <drubio-m@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:55:51 by drubio-m          #+#    #+#             */
/*   Updated: 2024/09/24 18:13:53 by drubio-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		ft_error("Game Memory allocation error");
	parsing(argc, argv, game);
	printf("\n If you have reached here, congrats \n");

	init_values(game);
	initialize_tex_buff(game);
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, SCREEN_X, SCREEN_Y, NAME);
	load_imgs(game);
	game->image.img = mlx_new_image(game->mlx, SCREEN_X, SCREEN_Y);
	game->image.data = (int *)mlx_get_data_addr(game->image.img, \
		&game->image.bpp, &game->image.len, &game->image.endian);
	mlx_loop_hook(game->mlx, &main_loop, &game);
	mlx_hook(game->mlx_win, DESTROY, 0, &end_program, &game);
	mlx_hook(game->mlx_win, KEY_PRESS, (1L << 0), &handle_keys, &game);
	mlx_loop(game->mlx);
	return (0);
}
