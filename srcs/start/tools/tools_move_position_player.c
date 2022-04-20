/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_move_position_player.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouali <ybouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 00:08:10 by ybouali           #+#    #+#             */
/*   Updated: 2022/04/19 23:53:06 by ybouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int     no_wall(t_cub3d *cub3d, float x, float y)
{
    int     x_map;
    int     y_map;

    if (x < 0 || x > cub3d->width || y < 0 || y > cub3d->height)
        return (0);
    x_map = floor(x / 50);
    y_map = floor(y / 50);
    if (cub3d->info_of_map[y_map][x_map] != '0')
        return (0);
    return (1);
}

void    move_player_new(t_cub3d *cub3d)
{
    float   move_step;
    float   x_p;
    float   y_p;
    
    cub3d->player->rotation_angel += (cub3d->player->turn_derection * cub3d->player->turn_speed);
    
    move_step = cub3d->player->walk_derection * cub3d->player->walk_speed;
    
    y_p = cub3d->player->y + sin(cub3d->player->rotation_angel) * move_step;
    x_p = cub3d->player->x + cos(cub3d->player->rotation_angel) * move_step;
    if (no_wall(cub3d, x_p, y_p))
    {
        cub3d->player->y = y_p;
        cub3d->player->x = x_p;
    }
}

void	ft_p_x_player(t_cub3d *cub3d, int x, int y, int k)
{
    if (cub3d->info_of_map[(x / 50)][(y / 50)] == 'N' && cub3d->info_of_map[(k / 50)][(y / 50)] == '0')
    {
        cub3d->info_of_map[(x / 50)][(y / 50)] = '0';
        cub3d->info_of_map[(k / 50)][(y / 50)] = 'N';
    }
}

void	ft_p_y_player(t_cub3d *cub3d, int x, int y, int k)
{
    if (cub3d->info_of_map[(x / 50)][(y / 50)] == 'N' && cub3d->info_of_map[(x / 50)][(k / 50)] == '0')
    {
        cub3d->info_of_map[(x / 50)][(y / 50)] = '0';
        cub3d->info_of_map[(x / 50)][(k / 50)] = 'N';
    }
}

void    protect_player_to_walk_into_wals(t_cub3d *cub3d)
{
    if (cub3d->player->walk_derection == 1)
        cub3d->player->x += 6;
    if (cub3d->player->walk_derection == -1)
        cub3d->player->x -= 6;
    if (cub3d->player->turn_derection == 1)
        cub3d->player->y -= 6;
    if (cub3d->player->turn_derection == -1)
        cub3d->player->y += 6;
}

void    print_player_info(t_cub3d *cub3d)
{
    printf ("\n\n|||||||||||||| START PRINTING INFO PLAYER ... ||||||||||||||||||||||||||||||||||||||\n");
    printf ("X_PLAYER [%f] Y_PLAYER [%f]\n\n", cub3d->player->x, cub3d->player->y);
    if (cub3d->player->turn_derection == 1)
        printf ("RIGHT\n");
    if (cub3d->player->turn_derection == -1)
        printf ("LEFT\n");
    if (cub3d->player->walk_derection == 1)
        printf ("FRONT\n");
    if (cub3d->player->walk_derection == -1)
        printf ("BACK\n");
    printf ("\n>>>>>>>>>>>>>>>>>>>{%f}\n", rad2deg(cub3d->player->rotation_angel));
    printf ("\n\n|||||||||||||| END PRINTING INFO PLAYER ... ||||||||||||||||||||||||||||||||||||||\n");
}

int abs (int n)
{
    return ( (n>0) ? n : ( n * (-1)));
}


void DDA(t_cub3d *cub3d , int Y1, int X1)
{
    // calculate dx & dy
    int     X0 = cub3d->player->x;
    int     Y0 = cub3d->player->y;
    int     dx = X1 - X0;
    int     dy = Y1 - Y0;
    
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
    float Xinc = dx / (float) steps;
    float Yinc = dy / (float) steps;
 
    // Put pixel for each step
    float X = X0;
    float Y = Y0;
    for (int i = 0; i <= steps; i++)
    {
        mlx_pixel_put(cub3d->ptr_init, cub3d->ptr_win, X, Y, 000);
        X += Xinc;
        Y += Yinc;
    }
}

void    print_player(t_cub3d *cub3d)
{
    float   x_start;
    float   y_start;
    float   x_end; 
    float   y_end;
    
    // move the player
    // move_player_new(cub3d);
    
    y_start = cub3d->player->y - 3;
    x_end = cub3d->player->x + 3;
    y_end = cub3d->player->y + 3;
    // print_player_info(cub3d);
    while (y_start < y_end)
    {
        x_start = cub3d->player->x - 3;
        while (x_start < x_end)
            mlx_pixel_put(cub3d->ptr_init, cub3d->ptr_win, x_start++, y_start, 125);
        y_start++;
    }
    DDA(
        cub3d,
        cub3d->player->y + sin(cub3d->player->rotation_angel) * 150,
        cub3d->player->x + cos(cub3d->player->rotation_angel) * 150 
    );
}

void    print_images(t_cub3d *cub3d)
{
    int  x;
    int  y;
    
    move_player_new(cub3d);
    // rays info
    // cast_all_rays(cub3d);
    y = 0;
    while (y < cub3d->height)
    {
        x = 0;
        while (x < cub3d->width)
        {
            
            // if (cub3d->info_of_map[(x / 50)][(y / 50)] == 'N')
            //     mlx_put_image_to_window(cub3d->ptr_init, cub3d->ptr_win, cub3d->player_texture, y, x);
            // else 
            if (cub3d->info_of_map[(y / 50)][(x / 50)] == '1')
                mlx_put_image_to_window(cub3d->ptr_init, cub3d->ptr_win, cub3d->we_texture, x, y);
            else
                mlx_put_image_to_window(cub3d->ptr_init, cub3d->ptr_win, cub3d->ground_texture, x, y);
            if (cub3d->info_of_map[(y / 50)][(x / 50)] == '\0')
                break;
            x += 50;
        }
        // if (cub3d->info_of_map[(y / 50)] == 0)
        //     break;
        y += 50;
    }
    print_player(cub3d);
    cast_all_rays(cub3d);
    // print_line_player(cub3d);
    // display_cub3d_info(&cub3d);
    // free_rays(&cub3d->rays);

    // player stop moving
    cub3d->player->walk_derection = 0;
    cub3d->player->turn_derection = 0;
    // print_player_info(cub3d);
}