/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freddy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:20:18 by gmersch           #+#    #+#             */
/*   Updated: 2024/09/22 12:56:00 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"


void	ft_print_freddy(t_player *p)
{
	float dist_x = p->f->posx - p->posx;
	float dist_y = p->f->posy - p->posy;
	float distance = sqrt(dist_x * dist_x + dist_y * dist_y);
	

	
	
	float angle_to_freddy = atan2(dist_y, dist_x);
	float player_angle = p->or;

	// Si Freddy est dans le champ de vision du joueur, on le dessine
	if (fabs(player_angle - angle_to_freddy) < p->fov / 2)
	{
		p->f->visible = true;
	}
	else
	{
		p->f->visible = false;
	}




	if (p->f->visible)
	{
		int sprite_screen_x = (p->game->width / 2) * (1 + (dist_x / dist_y));
		int sprite_height = abs((int)(p->game->height / distance));  // Plus Freddy est proche, plus il sera grand

		// Dessiner l'image de Freddy à la position calculée
		mlx_image_to_window(p->game->mlx, p->f->fl, sprite_screen_x, (p->game->height / 2) - sprite_height / 2);
	}


	//update pos whem not looking
    // if (!p->f->visible) {
    //     // Déplacer Freddy dans la direction définie
    // 	p->f->posx += 0.01 * cos(game->freddy->direction);
    //     p->f->posy += 0.01 * sin(game->freddy->direction);
    // }
}













