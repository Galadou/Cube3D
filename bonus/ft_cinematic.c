/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cinematic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <gmersch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:48:24 by gmersch           #+#    #+#             */
/*   Updated: 2024/09/21 16:46:28 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

//add_vol is the vol u want to add
char	*volume_change(char *str, int add_vol)
{
	int		i;
	char	**first_split;
	char	**second_split;
	char	*result;
	char	*free_str;
	int		nb;
	char	*nbc;

	nb = 0;
	i = 1;
	first_split = ft_split(str, '=');
	second_split = ft_split(first_split[1], ' ');
	nb = ft_atoi(second_split[0]) + add_vol;
	nbc = ft_itoa(nb);
	result = ft_strjoin(first_split[0], "=");
	free_str = result;
	result = ft_strjoin(result, nbc);
	free(free_str);
	free_str = result;
	while (second_split[i])
	{
		result = ft_strjoin(result, " ");
		free(free_str);
		free_str = result;
		result = ft_strjoin(result, second_split[i]);
		free(free_str);
		free_str = result;
		i++;
	}
	ft_arrfree(first_split);
	ft_arrfree(second_split);
	free(nbc);
	return (result);
}


static void	ft_redefine_cinematic_player(t_player *p)
{
	if (p->data->map.map)
		ft_arrfree(p->data->map.map);
	p->data->map.map = ft_calloc(sizeof(char *), ft_arrlen(p->data->map.map_copy) + 1);
	ft_arrcpy(p->data->map.map, p->data->map.map_copy);
	
	p->posx = p->buf_px;
	p->posy = p->buf_py;
	p->or = p->buf_or;
	p->fov = p->buf_fov;
}

void	ft_cinematic(t_player *p)
{
	char	*free_str;

	if (!p->freddy_walk)
		p->freddy_walk = ft_strdup("paplay --volume=10000 bonus/song/tjoc.wav &");
	if (p->posx < 35.5)
	{
		p->posx = p->posx + 0.1;
		if ((int)p->posx % 2 == 0)
		{
			free_str = p->freddy_walk;
			p->freddy_walk = volume_change(p->freddy_walk, 200);
			free(free_str);
			system(p->freddy_walk);
		}
		p->or = 0.0 * M_PI;

	}
	else if (p->posx > 35.5 && p->game->cinematic)
	{
		p->game->cinematic = false;
		ft_redefine_cinematic_player(p);
		system("paplay --volume=80000 bonus/song/ahah.wav &");
	}
}

void	ft_define_cinematic(t_player *p)
{
	if (p->data->map.map_copy)
	{
		ft_arrfree(p->data->map.map_copy);
		p->data->map.map_copy = NULL;
	}
	p->data->map.map_copy = ft_calloc(sizeof(char *), ft_arrlen(p->data->map.map) + 1);
	ft_arrcpy(p->data->map.map_copy, p->data->map.map);
	//if (!p->data->map.map_copy)
	//	printf("beteuuuh\n");
	p->data->map.map = ft_calloc(sizeof(char *), 4);
	p->data->map.map[0] = ft_strdup("1111111111111111111111111111111111111");
	p->data->map.map[1] = ft_strdup("1000000000000000000000000000000000001");
	p->data->map.map[2] = ft_strdup("1111111111111111111111111111111111111");
	
	p->buf_px = p->posx;
	p->buf_py = p->posy;
	p->buf_fov = p->fov;
	p->buf_or = p->or;
	
	p->posx = 1.5;
	p->posy = 1.5;
	p->or = 0.0 * M_PI;
	p->fov = 0.4 * M_PI;
}
