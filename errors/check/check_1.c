/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouali <ybouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:59:59 by ybouali           #+#    #+#             */
/*   Updated: 2022/04/08 22:49:54 by ybouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int     check_first_line(t_cub3d *cub3d)
{
    int     i;
    
    i = 0;
    while (cub3d->info_of_map[0][i])
    {
        if (cub3d->info_of_map[0][i] == ' ')
        {
            while (cub3d->info_of_map[0][i] == ' ')
                i++;
            if (cub3d->info_of_map[0][i] != '\0' && \
            cub3d->info_of_map[0][i] != '1')
                return (error_space(0));    
        }
        else if (cub3d->info_of_map[0][i] != '1')
            return (error_space(0));
        i++;
    }
    return (0);
}

int     check_last_line(t_cub3d *cub3d, int len)
{
    int     i;
    
    i = 0;

    while (cub3d->info_of_map[len - 1][i])
    {
        if (cub3d->info_of_map[len - 1][i] == '\n')
            i++;
        if (cub3d->info_of_map[len - 1][i] == ' ')
        {
            while (cub3d->info_of_map[len - 1][i] == ' ')
                i++;
            if (cub3d->info_of_map[len - 1][i] == '\0')
                break ;
            if (cub3d->info_of_map[len - 1][i] != '1')
                return (error_space(1));
        }
        else if (cub3d->info_of_map[len - 1][i] != '1')
            return (error_space(1));
        i++;
    }
    return (0);
}

int     check_in( char *str, char c)
{
    int     i;

    i = -1;
    while (str[++i])
    {
        if (str[i] == c)
            return (1);
    }
    return (0);
}

int     check_lines_between(t_cub3d *cub3d_info, int n)
{
    int i = 0;
    int j = 0;
    
    while (++i < (n -  1))
    {
        if (cub3d_info->info_of_map[i][0] != ' ' && \
        cub3d_info->info_of_map[i][0] != '1')
            return (error_the_first_char_on_line(0));
        j = 0;
        while (cub3d_info->info_of_map[i][j])
        {
            if (cub3d_info->info_of_map[i][j] == ' ')
            {
                if ((j - 1) >= 0 && \
                cub3d_info->info_of_map[i][j - 1] != '1')
                    return (error_expact_2(i));
                while (cub3d_info->info_of_map[i][j] == ' ')
                    j++;
                if (cub3d_info->info_of_map[i][j] == '\0')
                    break ;
                if (cub3d_info->info_of_map[i][j] != '1')
                    return (error_expact_1(i));
            }
            else if (check_in("10N", cub3d_info->info_of_map[i][j]) == 1)
                j++;
            else
                return (1);
        }
    }
    return (0);
}