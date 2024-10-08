/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:00:20 by gmersch           #+#    #+#             */
/*   Updated: 2024/09/22 22:06:04 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	ft_free_game_color_other(t_player *p)
{
	if (p->game->fps_max)
		mlx_delete_image(p->game->mlx, p->game->fps_max);
	if (p->game->color_east)
		free(p->game->color_east);
	if (p->game->color_north)
		free(p->game->color_north);
	if (p->game->color_south)
		free(p->game->color_south);
	if (p->game->color_west)
		free(p->game->color_west);
	if (p->game->mlx)
		mlx_terminate(p->game->mlx);
	if (p->game->fps_mini)
		free(p->game->fps_mini);
	if (p->game->fps_maxi)
		free(p->game->fps_maxi);
}

static void	ft_free_game(t_player *p)
{
	if (p->game)
	{
		if (p->game->dark_t)
			mlx_delete_texture(p->game->dark_t);
		if (p->game->flash_t)
			mlx_delete_texture(p->game->flash_t);
		if (p->game->image)
			mlx_delete_image(p->game->mlx, p->game->image);
		if (p->game->dark)
			mlx_delete_image(p->game->mlx, p->game->dark);
		if (p->game->flash)
			mlx_delete_image(p->game->mlx, p->game->flash);
		if (p->game->fps)
			mlx_delete_image(p->game->mlx, p->game->fps);
		if (p->game->fps_min)
			mlx_delete_image(p->game->mlx, p->game->fps_min);
		ft_free_game_color_other(p);
		free(p->game);
	}
}

void	ft_ultimate_free(t_player *p)
{
	if (p)
	{
		if (p->data)
		{
			if (p->data->map.t_we_path)
				mlx_delete_texture(p->data->map.t_we_path);
			if (p->data->map.t_ea_path)
				mlx_delete_texture(p->data->map.t_ea_path);
			if (p->data->map.t_no_path)
				mlx_delete_texture(p->data->map.t_no_path);
			if (p->data->map.t_so_path)
				mlx_delete_texture(p->data->map.t_so_path);
			if (p->data->map.map)
				ft_arrfree(p->data->map.map);
		}
		ft_free_game(p);
		if (p->rc)
			free(p->rc);
		free(p);
	}
	system("pkill -9 paplay");
	exit (1);
}
