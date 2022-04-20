/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouali <ybouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 21:29:18 by ybouali           #+#    #+#             */
/*   Updated: 2022/04/19 21:33:21 by ybouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void    ft_exit(t_cub3d *cub3d)
{
    mlx_clear_window(cub3d->ptr_init, cub3d->ptr_win);
	mlx_destroy_window(cub3d->ptr_init, cub3d->ptr_win);
    exit (0);
}

int     key_press(int key, t_cub3d *cub3d)
{
    if (key == 126 || key == 13)
    {
        //  printf ("FRONT\n");
        // ft_p_x_player(cub3d, cub3d->player->x, cub3d->player->y, cub3d->player->x - 6);
        cub3d->player->turn_derection = 0;
        cub3d->player->walk_derection = 1;
        // cub3d->player->x -= 6;
    }
	else if (key == 125 || key == 1)
	{
        // printf ("BACK\n");
        // ft_p_x_player(cub3d, cub3d->player->x, cub3d->player->y, cub3d->player->x + 6);
        cub3d->player->turn_derection = 0;
        cub3d->player->walk_derection = -1;
        // cub3d->player->x += 6;
    }
	else if (key == 124 || key == 2)
	{
        // printf ("RIGHT\n");
        // ft_p_y_player(cub3d, cub3d->player->x, cub3d->player->y, cub3d->player->y + 6);
        cub3d->player->turn_derection = 1;
        cub3d->player->walk_derection = 0;
        // cub3d->player->y += 6;
    }
	else if (key == 123 || key == 0)
	{
        // printf ("LEFT\n");
        // ft_p_y_player(cub3d, cub3d->player->x, cub3d->player->y, cub3d->player->y - 6);
        cub3d->player->turn_derection = -1;
        cub3d->player->walk_derection = 0;
        // cub3d->player->y -= 6;
    }
	else if (key == 53)
        ft_exit(cub3d);
    else
        return (1);
    print_images(cub3d);
    return (1);
}

double      rad2deg(double rad)
{
    return ((rad * 180) / M_PI);
}

// double      deg2rad(double rad)
// {
//     return ((rad * 180) / M_PI);
// }