/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 19:36:29 by msessa            #+#    #+#             */
/*   Updated: 2021/04/18 17:49:13 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ft_cub3d.h"

static void	ft_game_update(t_game *game)
{
	t_size	move;

	move = ft_ply_set_move(game->player->dir, game->player->moving);
	ft_ply_set_cell_x(game->map, game->player, move);
	ft_ply_set_cell_y(game->map, game->player, move);
	if (game->player->rotating[r_left] || game->player->rotating[r_right])
		ft_ply_set_dir(game->player);
	ft_rays_set(game, game->rays, game->res.x, game->rays_info.step);
	// To test
	// ft_print_rays(game->rays, game->res.x);
	// Bottleneck on movement
	ft_scene(game);
	if (game->settings[show_minimap])
		ft_mini_map(game);
	// To test
	// printf("player dir: %f\n", game->player->dir);
}

void	ft_print_fps(t_game *game)
{
	char	*fps;
	double	frame_time;

	frame_time = (game->new_time.tv_sec + (game->new_time.tv_usec / 1000000.0))
		- (game->old_time.tv_sec + (game->old_time.tv_usec / 1000000.0));
	if (frame_time < 0.001)
		fps = ft_strdup("> 1000"); 
	else
		fps = ft_itoa(1.0 / frame_time);
	// ft_draw_rect(&game->scene, (t_size){x : 6, y : 20}, (t_size){x : 100, y : 24}, 0x00FFFFFF);
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFF0000, "FPS: ");
	mlx_string_put(game->mlx, game->win, 60, 20, 0xFFFF0000, fps);
	// printf("fps: %s", fps);
	free(fps);
}

static void	ft_game_print(t_game *game)
{
	// Black bg for transparency, flickering on linux, ok on mac
	mlx_put_image_to_window(game->mlx, game->win, game->bg.img_ref, 0, 0);
	if (ft_player_moved(game->player))
		ft_game_update(game);
	mlx_put_image_to_window(game->mlx, game->win, game->scene.img_ref, 0, 0);
	// Extra layer for objects, don't sure it will be useful
	// Maybe for putting black on scene and transparency on objects
	// mlx_put_image_to_window(game->mlx, game->win, game->obj.img_ref, 0, 0);
	if (game->settings[show_minimap])
	{
		mlx_put_image_to_window(game->mlx, game->win, game->mm_img.img_ref,
			game->mm_pos.x, game->mm_pos.y);
		mlx_put_image_to_window(game->mlx, game->win, game->lb.img.img_ref,
			game->lb.pos.x, game->lb.pos.y);
	}
	else
		mlx_put_image_to_window(game->mlx, game->win, game->lb.img.img_ref,
			game->lb.pos.x, game->mm_pos.y + game->mini_map.size.y / 2);
	ft_update_time(game);
	if (game->settings[show_fps])
		ft_print_fps(game);
}

int	ft_render_game(void *game_void)
{
	t_game	*game;

	game = (t_game *)game_void;
	ft_game_print(game);
	return (1);
}

void	ft_run_game(t_map *map)
{
	t_game	game;

	if (!ft_init_game(&game, map))
		return ;
	ft_set_events(&game);
	ft_game_update(&game);
	ft_lifeb_update(&game);
	mlx_loop(game.mlx);
}