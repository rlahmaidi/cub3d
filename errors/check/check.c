/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouali <ybouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 18:03:13 by ybouali           #+#    #+#             */
/*   Updated: 2022/04/10 20:19:15 by ybouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int     len_table(char **table)
{
    int     i;

    i = 0;
    while (table[i])
        i++;
    return (i);
}

int check_name_of_map(char *name_of_map)
{
    int     len;

    len = ft_strlen(name_of_map);
    len -= 4;
    if (name_of_map[len] == '\0')
        return (error_name());
    if (ft_strncmp(&name_of_map[len], ".cub", \
    ft_strlen(&name_of_map[len])) == 0)
        return (0);
    return (error_name());
}

char    *check_map(char *name_of_map)
{
    char    **info_of_map;
    
    if (check_name_of_map(name_of_map))
        return (NULL);
    info_of_map = stock_info_map(name_of_map);
    if (!info_of_map)
        return (NULL);
    return (ft_table_dup_to_string(info_of_map));
}

int     last_check(t_cub3d *cub3d_info, int n)
{
    int     i;
    int     j;

    i = 1;
    while (i < (n - 1))
    {
        j = 0;
        while (cub3d_info->info_of_map[i][j])
        {
            if (cub3d_info->info_of_map[i][j] == ' ')
            {
                if ((i - 1) > 0 && (i - 1) <= (n - 1))
                {
                    if (cub3d_info->info_of_map[i - 1][j] != '\0' &&\
                    cub3d_info->info_of_map[i - 1][j] != '1' && \
                    cub3d_info->info_of_map[i - 1][j] != ' ')
                        return (error_expact_3(i - 1));
                }
                if ((i + 1) > 0 && (i + 1) <= (n - 1))
                {
                    if (cub3d_info->info_of_map[i + 1][j] != '\0' && \
                    cub3d_info->info_of_map[i + 1][j] != '1' && \
                    cub3d_info->info_of_map[i + 1][j] != ' ')
                        return (error_expact_4(i + 1));
                }
            }
            j++;
        }
        i++;
    }
    return (0);
}

int     check_map_errors(t_cub3d *cub3d_info)
{
    int     i;
    int     n;

    i = 0;
    n = len_table(cub3d_info->info_of_map);
    if (n <= 4)
        return (error_map_1());
    if (check_first_line(cub3d_info))
        return (1);
    if (check_last_line(cub3d_info, n))
        return (1);
    if (check_lines_between(cub3d_info, n))
        return (1);
    if (last_check(cub3d_info, n))
        return (1);
    if (check_number_of_player(cub3d_info->info_of_map))
        return (1);
    // if (check_len_map(cub3d_info))
    //     return (1);
    return (0);
}