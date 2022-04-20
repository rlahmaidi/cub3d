/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouali <ybouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:53:10 by ybouali           #+#    #+#             */
/*   Updated: 2022/04/19 22:46:42 by ybouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "../libft/libft.h"

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>

# define NO     21
# define SO     22
# define WE     23 
# define EA     24 
# define F      25 
# define C      26 
# define MAP    27

# define FOV_ANGLE (60 * (M_PI / 180))


typedef struct s_player
{
    float       x;
    float       y;
    float   with;
    float   height;
    int         turn_derection; // -1 left and 1 for right
    int         walk_derection; // -1 down and 1 for up
    float       rotation_angel;
    float       walk_speed;
    float       turn_speed;
}   t_player;

typedef struct s_ray
{
    float   ray_angle;
    float   wall_hit_x;
    float   wall_hit_y;
    float   distance;
    int     ray_id;
    int     was_hit_vertical;
    int     was_hit_horizontal;
    int     is_ray_facing_up;
    int     is_ray_facing_down;
    int     is_ray_facing_left;
    int     is_ray_facing_right;
    int     wall_hit_content;
    struct s_ray *next;
} t_ray;

typedef struct s_cub3d
{
    float   fov_angle;
    char    **info_of_map;
    char    *no;
    char    *so;
    char    *we;
    float   f_x;
    float   f_y;
    char    *ea;
    void    *no_texture;
    void    *so_texture;
    void    *we_texture;
    void    *ea_texture;
    void    *player_texture;
    void    *ground_texture;
    char    *f;
    char    *c;
    float     width;
    float     height;
    void            *ptr_init;
    void            *ptr_win;
    struct s_player *player;
    struct s_ray *rays;
}   t_cub3d;

typedef struct s_lexer
{
    unsigned int    index;
    char            c;
    char            *contents;
    int             no_bool;
    int             so_bool;
    int             we_bool;
    int             ea_bool;
    int             f_bool;
    int             c_bool;
    int             map_bool;
} t_lexer;

typedef struct s_token
{
    int             type;
    char            *value;
    struct s_token  *next;
} t_token;


// GET STARTED
void    cast_all_rays(t_cub3d *cub3d);
void    free_rays(t_ray **head);
t_ray   *init_ray(void);
void    push_ray(t_ray **head, t_ray *new);
void     launch(t_cub3d *cub3d);
int     length_of_map(char **table);
int max__with_in_map(char **table);
t_player    *init_player(t_cub3d *cub3d);
int     key_press(int key, t_cub3d *cub3d);
void	ft_p_y_player(t_cub3d *cub3d, int x, int y, int k);
void	ft_p_x_player(t_cub3d *cub3d, int x, int y, int k);
void    print_images(t_cub3d *cub3d);
char    **get_map_to_print(t_cub3d *cub3d);
void change_the_position_of_player(t_cub3d *cub3d);


double      rad2deg(double rad);

/* lexer */
t_lexer     *lexer_init(char *content);
void        lexer_advance(t_lexer *lexer);
void        lexer_skep_withespace(t_lexer *lexer);
t_token     *lexer_get_next_token(t_lexer *lexer);
char        *lexer_stock(t_lexer *lexer, char *value);
t_token     *lexer_collection_texture(t_lexer *lexer, int type);
t_token     *lexer_start(char *name_of_map);
t_token     *lexer_collection_map(t_lexer *lexer, int type);

void    get_one_info(t_lexer *lexer, int type);

t_cub3d    *init_cub3d_info();

/* token */
t_token     *init_token(int type, char *value);
void        push_back_token(t_token **list, t_token *new);
void        display_tokens(t_token **tokens);


void        free_info_map(t_cub3d **info_map);

t_cub3d     *check_for_syntax_map(char *name_of_file);

/* Errors */
int     err_args(void);
int     error_name(void);
int     error_fd(char *name_of_file);
int     error_malloc(void);
char    **error_map_empty(char *name_of_file);
int     error_number_of_player(void);


int     check_number_of_player(char **table);
int     check_lines_between(t_cub3d *cub3d_info, int n);

int     error_map_1(void);

int     error_expact_1(int i);
int     error_expact_2(int i);
int     error_expact_3(int i);
int     error_expact_4(int i);

int     error_len_map(int i);

int     error_space(int boolean);

int     error_the_first_char_on_line(int boolean);

int     check_first_line(t_cub3d *cub3d);
int     check_last_line(t_cub3d *cub3d, int len);
int     check_len_map(t_cub3d *cub3d_info);

int     error_syntax_no(void);
int     error_syntax_so(void);
int     error_syntax_we(void);
int     error_syntax_ea(void);
int     error_syntax_f(void);
int     error_syntax_c(void);
int     error_syntax_map(void);

t_token *error_on_map(void);


/* Check */
int     check_name_of_map(char *name_of_map);
char    *check_map(char *name_of_map);
int     check_sytax(t_cub3d **info_check);
int     check_map_errors(t_cub3d *cub3d_info);

/* Tools */
void    display_cub3d_info(t_cub3d **cub3d);
void    display_info_map(char **info);
void    display_string(char *str, char *stri, char *strin);

int     strlen_with(char *s, int c);
char	*get_next_line(int fd);
void    free_table(char **table);
char    *ft_table_dup_to_string(char **info_of_map);
// char    **alocate_2d_table(char *name_of_file);
char    **stock_info_map(char *name_of_map);

#endif