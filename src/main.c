/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-gu <fdiaz-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:55:51 by drubio-m          #+#    #+#             */
/*   Updated: 2024/09/27 12:32:38 by fdiaz-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int activate_key(int key, t_game *game)
{
	if (key == K_ESC)
		end_program(game);
	if (key == A)
		game->keys.a = 1;
	if (key == W)
		game->keys.w = 1;
	if (key == D)
		game->keys.d = 1;
	if (key == S)
		game->keys.s = 1;
	if (key == LEFT)
		game->keys.left = 1;
	if (key == RIGHT)
		game->keys.right = 1;
	return (0);
}

int	deactivate_key(int key, t_game *game)
{	
	if (key == A)
		game->keys.a = 0;
	if (key == W)
		game->keys.w = 0;
	if (key == D)
		game->keys.d = 0;
	if (key == S)
		game->keys.s = 0;
	if (key == LEFT)
		game->keys.left = 0;
	if (key == RIGHT)
		game->keys.right = 0;
	return (0);
}

void ft_game(t_game *game)
{
	init_values(game);
	initialize_tex_buff(game);
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, SCREEN_X, SCREEN_Y, NAME);
	load_imgs(game);
	game->image.img = mlx_new_image(game->mlx, SCREEN_X, SCREEN_Y);
	game->image.data = (int *)mlx_get_data_addr(game->image.img,
												&game->image.bpp, &game->image.len, &game->image.endian);
	mlx_loop_hook(game->mlx, &main_loop, game);
	mlx_hook(game->mlx_win, DESTROY, 0, &end_program, game);
	mlx_hook(game->mlx_win, KEY_PRESS, (1L << 0), &activate_key, game);
	mlx_hook(game->mlx_win, KEY_OFF, (1L << 1), &deactivate_key, game);
	mlx_loop(game->mlx);
}
int main(int argc, char **argv)
{
	t_game *game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		ft_error("Game Memory allocation error");
	parsing(argc, argv, game);
	printf("\n If you have reached here, congrats \n");
	ft_game(game);
	return (0);
}
