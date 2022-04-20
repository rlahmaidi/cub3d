/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouali <ybouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 23:45:18 by ybouali           #+#    #+#             */
/*   Updated: 2022/04/20 01:31:33 by ybouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

// void    get_vertical_des(t_cub3d *cub3d, int raysId, float ray_angle)
// {
//     long    x_step;
//     long    y_step;
//     // long    step;

//     (void) cub3d;
//     (void) raysId;
//     // x_step = 50;
//     // y_step = (50 / tan(ray_angle));
//     // y_step = (x_step + ((y_step - y_step) / tan(ray_angle)));
//     // x_step = (floor(y_step / 50) * 50);
//     // step = (tan(ray_angle) / 50);
//     // x_step = cub3d->player->x * 50;
//     // y_step = cub3d->player->y * 50;
//     // while (x_step < cub3d->height && y_step < cub3d->width)
//     // {
//     //     if (cub3d->info_of_map[x_step / 50][y_step / 50] == '1')
//     //         break;
//     //     printf (">>>>>>>>>>>>>>>>>>>>X(%ld)Y(%ld)[%d]>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n", x_step, y_step, raysId);
//     //     mlx_string_put(cub3d->ptr_init, cub3d->ptr_win, y_step, x_step, 128, "O");
//     //     x_step += 50;
//     //     y_step += (x_step / tan(ray_angle));
//     // }
//     // x_step = cub3d->player->x * 50;
//     // y_step = cub3d->player->y * 50;
//     // while (x_step > 0 && y_step > 0)
//     // {
//     //     if (cub3d->info_of_map[x_step / 50][y_step / 50] == '1')
//     //         break;
//     //     printf (">>>>>>>>>>>>>>>>>>>>X(%ld)Y(%ld)[%d]>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n", x_step, y_step, raysId);
//     //     mlx_string_put(cub3d->ptr_init, cub3d->ptr_win, y_step, x_step, 128, "O");
//     //     x_step -= 50;
//     //     y_step -= (x_step / tan(ray_angle));
//     // }
    
// }



// void    get_horizontal_des(t_cub3d *cub3d, int raysId, float ray_angle, t_ray *ray)
// {
//     long    x_step;
//     long    y_step;
//     long    x_intercepte;
//     long    y_intercepte;

//     (void) raysId;
//     y_intercepte = (floor((cub3d->player->y * 50) / 50) * 50);
//     // if (ray->is_ray_facing_down)
//     //     y_intercepte += 50;
//     y_intercepte += ray->is_ray_facing_down ? 50 : 0;
//     x_intercepte = ((cub3d->player->x * 50) + ((y_intercepte - (cub3d->player->y * 50)) / tan(ray_angle)));
//     x_step = 50;
//     x_step *= ray->is_ray_facing_up ? -1 : 1;
//     y_step = (50 / tan(ray_angle));
//     y_step = (ray->is_ray_facing_left && y_step > 0) ? -1 : 1;
//     y_step = (ray->is_ray_facing_right && y_step < 0) ? -1 : 1;
//     printf ("\n\nx_intercepte[%ld]y_intercepte[%ld]\nx_step{%ld}y_step{%ld}\n\n", x_intercepte, y_intercepte, x_step, y_step);
//     // while (x_step < cub3d->height)
//     // {
            
//     // }
    
// }

int ab_s (int n)
{
    return ( (n>0) ? n : ( n * (-1)));
}

void DDA_ray(t_cub3d *cub3d , int Y1, int X1)
{
    // calculate dx & dy
    int     X0 = cub3d->player->x;
    int     Y0 = cub3d->player->y;
    int     dx = X1 - X0;
    int     dy = Y1 - Y0;
    
    int steps = ab_s(dx) > ab_s(dy) ? ab_s(dx) : ab_s(dy);
 
    float Xinc = dx / (float) steps;
    float Yinc = dy / (float) steps;
 
    // Put pixel for each step
    float X = X0;
    float Y = Y0;
    for (int i = 0; i <= steps; i++)
    {
        mlx_pixel_put(cub3d->ptr_init, cub3d->ptr_win, X, Y, 100);
        X += Xinc;
        Y += Yinc;
    }
}

float   normalize_angle(float ray_angle)
{
    ray_angle = remainder(ray_angle, (M_PI * 2));
    if (ray_angle < 0)
        ray_angle = (M_PI * 2) + ray_angle;
    return (ray_angle);
}

static void     cast_ray(t_cub3d *cub3d, float ray_angle, int ray_id)
{
    float   y_intercept;
    float   x_intercept;
    float   y_step;
    float   x_step;
    t_ray   *ray;
    
    ray_angle = normalize_angle(ray_angle);
    DDA_ray(
        cub3d,
        cub3d->player->y + sin(ray_angle) * 90,
        cub3d->player->x + cos(ray_angle) * 90
        );
    ray = init_ray();
    push_ray(&cub3d->rays, ray);
    ray->ray_id = ray_id;
    if (ray_angle > 0 && ray_angle < M_PI)
        ray->is_ray_facing_down = 1;
    ray->is_ray_facing_up = !ray->is_ray_facing_down;
    if (ray_angle < 0.5 || ray_angle > 1.5 * M_PI)
        ray->is_ray_facing_right = 1;
    ray->is_ray_facing_left = !ray->is_ray_facing_right;
    y_intercept = floor(cub3d->player->y / 50) * 50;
    y_intercept += ray->is_ray_facing_down ? 50 : 0;
    
    x_intercept = (cub3d->player->x + ((y_intercept - cub3d->player->y) / tan(ray_angle)));
    y_step = 50;
    y_step *= ray->is_ray_facing_up ? -1 : 1;

    x_step = (50 / tan(ray_angle));
    x_step *= (ray->is_ray_facing_left && x_step > 0) ? -1 : 1;
    x_step *= (ray->is_ray_facing_right && x_step < 0) ? -1 : 1;
}

void    cast_all_rays(t_cub3d *cub3d)
{
    float   ray_angle = cub3d->player->rotation_angel - (FOV_ANGLE / 2);
    int     rayId;
    
    rayId = -1;
    while (++rayId < (cub3d->width / 50))
    {
        cast_ray(cub3d, ray_angle, rayId);
        ray_angle += (FOV_ANGLE / (cub3d->width / 50));
    }
}