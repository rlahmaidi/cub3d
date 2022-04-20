/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_change_player_position.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouali <ybouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:55:31 by ybouali           #+#    #+#             */
/*   Updated: 2022/04/18 23:03:07 by ybouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"


static void remove_the_player_into_the_map(t_cub3d *cub3d)
{
    int i;
    int j;

    i = -1;
    while (cub3d->info_of_map[++i] != 0)
    {
        j = -1;
        while (cub3d->info_of_map[i][++j] != '\0')
        {
            if (cub3d->info_of_map[i][j] == 'N')
            {
                cub3d->info_of_map[i][j] = '0';
                return;
            }
        }
    }
}

static int top_left_or_right(t_cub3d *cub3d)
{
    int i;
    int j;

    i = ((cub3d->height / 50) / 2);
    while (i > 0)
    {
        j = (ft_strlen(cub3d->info_of_map[i]) / 2);
        while (j > 0)
        {
            if (cub3d->info_of_map[i][j] == '0')
            {
                cub3d->info_of_map[i][j] = 'N';
                cub3d->f_x = j * 50;
                cub3d->f_y = i * 50;
                return (1);
            }
            j--;
        }
        j = (ft_strlen(cub3d->info_of_map[i]) / 2);
        while (cub3d->info_of_map[i][j] != '\0')
        {
            if (cub3d->info_of_map[i][j] == '0')
            {
                cub3d->info_of_map[i][j] = 'N';
                cub3d->f_x = j * 50;
                cub3d->f_y = j * 50;
                return (1);
            }
            j++;
        }
        i--;
    }
    return (0);
}

static int buttom_left_or_right(t_cub3d *cub3d)
{
    int i;
    int j;

    i = ((cub3d->height / 50) / 2);
        while (cub3d->info_of_map[i] != 0)
        {
            j = (ft_strlen(cub3d->info_of_map[i]) / 2);
            while (j > 0)
            {
                if (cub3d->info_of_map[i][j] == '0')
                {
                    cub3d->info_of_map[i][j] = 'N';
                    cub3d->f_x = i * 50;
                    cub3d->f_y = j * 50;
                    return (1);
                }
                j--;
            }
            j = (ft_strlen(cub3d->info_of_map[i]) / 2);
            while (cub3d->info_of_map[i][j] != '\0')
            {
                if (cub3d->info_of_map[i][j] == '0')
                {
                    cub3d->info_of_map[i][j] = 'N';
                    cub3d->f_x = i * 50;
                    cub3d->f_y = j * 50;
                    return (1);
                }
                j++;
            }
            i++;
        }
        return (0);
}

void change_the_position_of_player(t_cub3d *cub3d)
{
    remove_the_player_into_the_map(cub3d);
    cub3d->f_x = cub3d->width / 2;
    cub3d->f_y = cub3d->height / 2;
    if (cub3d->info_of_map[(int)(cub3d->height / 50) / 2][(int)(cub3d->width / 50) / 2] == '0')
    {
        cub3d->info_of_map[(int)(cub3d->height / 50) / 2][(int)(cub3d->width / 50) / 2] = 'N';
        return ;
    }
    else
    {
        if (top_left_or_right(cub3d))
            return ;
        if (buttom_left_or_right(cub3d))
            return ;
    }
}