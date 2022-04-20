/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouali <ybouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 20:57:57 by ybouali           #+#    #+#             */
/*   Updated: 2022/04/19 22:29:34 by ybouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

t_player    *init_player(t_cub3d *cub3d)
{
    t_player    *player_new;
    
    player_new = malloc(sizeof(t_player));
    player_new->x = cub3d->f_x;
    player_new->y = cub3d->f_y;
    player_new->height = 1;
    player_new->with = 1;
    player_new->turn_derection = 0;
    player_new->walk_derection = 0;
    player_new->rotation_angel = (M_PI / 2);
    player_new->walk_speed = 45;
    player_new->turn_speed = (15 * (M_PI / 180));
    return (player_new);
}
