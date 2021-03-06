/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msessa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 18:49:26 by msessa            #+#    #+#             */
/*   Updated: 2021/04/22 19:08:52 by msessa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ft_cub3d.h"

/* Offset variable could be removed because used on only one occasion right now
** Leaving because it may be useful in the future */
static void	ft_set_line_offset(t_vert_line *line, int scene_h)
{
	if (line->line_h > scene_h)
	{
		line->tex_h = scene_h;
		line->offset = (line->line_h - scene_h) / 2.0;
		line->skip_texels = line->offset * line->tex_step_h_f;
		line->tex_addr += line->tex->size_line * (int)(line->skip_texels);
		line->next_step_h = (line->skip_texels - (int)(line->skip_texels))
			* TEX_PRECISION;
	}
	else
	{
		line->next_step_h = line->step_precision;
		line->tex_h = line->line_h;
		line->offset = 0;
	}
}

static void	ft_init_line(t_vert_line *line, t_ray *ray, int scene_h, int pos_x)
{
	line->ray = ray;
	line->scene_h = scene_h;
	if (ray->dist <= 0)
		line->line_h = scene_h * 20;
	else
		line->line_h = scene_h / ray->dist;
	line->tex_addr = line->tex->img_addr
		+ 4 * (int)(line->tex->width * ray->tex_pos);
	line->tex_step_h_f = (double)line->tex->height / line->line_h;
	line->tex_step_h = line->tex->size_line * (int)line->tex_step_h_f;
	line->step_precision = (line->tex_step_h_f
			- (int)line->tex_step_h_f) * TEX_PRECISION;
	line->next_step_h = line->step_precision;
	ft_set_line_offset(line, scene_h);
	line->pos.x = pos_x;
	line->pos.y = (scene_h - line->tex_h) / 2;
	if (ray->dist <= 1)
		line->tex_alpha = 0;
	if (ray->dist > 12.75)
		line->tex_alpha = 255 << 24;
	else
		line->tex_alpha = (unsigned int)(ray->dist * 20) << 24;
}

void	ft_scene(t_game *game)
{
	t_vert_line	*line;
	t_ray		*ray_sel;
	int			i;

	line = &game->line;
	ray_sel = game->rays;
	i = 0;
	while (i < game->res.x)
	{
		line->tex = &game->tex[ray_sel->tex];
		ft_init_line(line, ray_sel, game->res.y, i);
		ft_draw_line(game, line);
		ray_sel++;
		i++;
	}
	if (game->sprites)
	{
		ft_draw_rect(&game->obj, (t_size){.x = 0, .y = 0}, game->res,
			0xFF000000);
		ft_set_sprites(game);
		if (game->sprites->in_fov)
			ft_draw_sprites(game);
	}
}
