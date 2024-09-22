/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 15:25:10 by gmersch           #+#    #+#             */
/*   Updated: 2024/09/22 12:55:47 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	ft_define_text_and_ray_color(t_player *p)
{
	if (p->rc->stepx == -1)
	{
		p->game->text = p->data->map.t_we_path;
		p->game->color_ray_text = p->game->color_west;
	}
	else
	{
		p->game->text = p->data->map.t_ea_path;
		p->game->color_ray_text = p->game->color_east;
	}
}

//define draw start and draw end, its were we should drow on the y line
static void	ft_define_print_wall(t_player *p)
{
	if (p->rc->side == 0)
		p->rc->perp_wall_dist = (p->rc->side_distx - p->rc->delta_distx);
	else
		p->rc->perp_wall_dist = (p->rc->side_disty - p->rc->delta_disty);
	p->rc->wall_height = ((float)p->game->height / (p->rc->perp_wall_dist * \
	(float)cos(p->or - p->rc->angle)));
	p->rc->wall_height = (float)floor(p->rc->wall_height * 10.0) / 10.0;
	p->rc->draw_end = p->rc->wall_height / 2.0 + (float)p->game->mid_sy + (float)p->game->mid_sy * 0.5;
	p->rc->draw_start = -p->rc->wall_height / 2.0 + (float)p->game->mid_sy + floor(((float)p->game->mid_sy * p->p_look_angle + p->rc->wall_height * p->p_height) * 1000) / 1000;
	p->rc->draw_end = p->rc->wall_height / 2.0 + (float)p->game->mid_sy + floor(((float)p->game->mid_sy * p->p_look_angle + p->rc->wall_height * p->p_height) * 1000) / 1000;
	if (p->rc->side == 1)
	{
		if (p->rc->stepy == -1)
		{
			p->game->text = p->data->map.t_no_path;
			p->game->color_ray_text = p->game->color_north;
		}
		else
		{
			p->game->text = p->data->map.t_so_path;
			p->game->color_ray_text = p->game->color_south;
		}
	}
	else
		ft_define_text_and_ray_color(p);
}

//known what side of the wall we'r talking
static void	ft_find_side(t_player *p)
{
	while (p->rc->hit == 0)
	{
		if (p->rc->side_distx < p->rc->side_disty)
		{
			p->rc->side_distx += p->rc->delta_distx;
			p->rc->mapx += p->rc->stepx;
			p->rc->side = 0;
		}
		else
		{
			p->rc->side_disty += p->rc->delta_disty;
			p->rc->mapy += p->rc->stepy;
			p->rc->side = 1;
		}
		if (p->rc->mapy < 0 || p->rc->mapy >= p->data->map.height_map \
		|| p->rc->mapx < 0 || p->rc->mapx >= \
		(int)ft_strlen(p->data->map.map[p->rc->mapy]))
			p->rc->hit = 1;
		if (!p->rc->hit && p->data->map.map[p->rc->mapy][p->rc->mapx] == '1')
			p->rc->hit = 1;
	}
}

static void	ft_walk_movement(t_player *p)
{
	float value;
	if (!p->last_px)
		p->last_px = p->posx;
	if (!p->last_py)
		p->last_py = p->posy;
	value = sqrt(pow(p->posx - p->last_px, 2) + pow(p->posy - p->last_py, 2));
	if (!p->last_value)
		p->last_value = value;
	if (value != p->last_value && !p->up)
	{
		p->p_height += -0.006;
		if (p->p_height < -0.03)
		{
			p->p_height = -0.03;
			p->up = true;
		}
	}
	else if (value != p->last_value && p->up)
	{
		p->p_height += 0.006;
		if (p->p_height > 0.03)
		{
			p->p_height = 0.03;
			p->up = false;
		}
	}
	p->last_value = value;		
	if (value >= 1.0)
	{
		if (p->footstep == true)
		{
			system("paplay --volume=30000 bonus/song/footstep1.wav &");
			p->footstep = false;
		}
		else
		{
			system("paplay --volume=30000 bonus/song/footstep2.wav &");
			p->footstep = true;
		}
		p->last_px = p->posx;
		p->last_py = p->posy;
	}
}

void	ft_ray_casting(void *param)
{
	t_player		*p;
	int				sx;
	struct timeval	time;
	suseconds_t		usec;
	time_t			sec;

	p = (t_player *)param;
	sx = 0;
	if (p->game->pause)
		return ;
	ft_walk_movement(p);
	if (p->game->cinematic)
		ft_cinematic(p);
	gettimeofday(&time, NULL);
	usec = time.tv_usec;
	sec = time.tv_sec;
	if (!p->game->cinematic)
		ft_move_wasd(p);
	while (sx < p->game->width)
	{
		ft_define_rc(p, sx);
		ft_find_side(p);
		ft_define_print_wall(p);
		ft_print_ray(p, sx);
		sx++;
	}
	ft_print_freddy(p);
	gettimeofday(&time, NULL);
	ft_print_fps(p, usec, sec, time);
	ft_mouse_move(p);
}
