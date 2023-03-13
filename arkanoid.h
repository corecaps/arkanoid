/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arkanoid.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 23:50:53 by jgarcia           #+#    #+#             */
/*   Updated: 2023/02/15 23:58:23 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARKANOID_H
# define ARKANOID_H
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <time.h>
# include <string.h>
# include <math.h>
# define RADIAN 0.0174532925
typedef struct s_point
{
	double x;
	double y;
} t_point;
typedef struct s_rgb
{
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char t;
}t_rgb;
typedef union u_color
{
	int		color;
	unsigned char	rgb[4];
	t_rgb			s_rgb;
} t_color;
typedef struct s_brick
{
	t_point	start;
	double	width;
	double	height;
	t_color	color;
	int		resistance;
}t_brick;
typedef struct s_brick_list
{
	t_brick brick;
	struct s_brick_list *next;
} t_brick_list;
typedef struct s_hitbox
{
	double start_x;
	double end_x;
	double start_y;
	double end_y;
} t_hitbox;
typedef struct player
{
	t_point	pos;
	double	width;
	double	height;
	double	velocity;
	int		score;

}t_player;
typedef struct s_ball
{
	t_point	pos;
	double	radius;
	double	angle;
	double	velocity;
	t_color	color;
}t_ball;
typedef struct s_buffer
{
	void	*img;
	char 	*address;
	int 	bit_per_pixel;
	int 	line_length;
	int 	endian;
} t_buffer;
typedef struct s_data
{
	void	*mlx;
	void	*mlx_win;
	t_buffer	*img_buffer;
	t_brick_list	*bricks;
	t_player	*player;
	t_ball		*ball;
	t_hitbox	brick_hitbox;
	t_hitbox	player_hitbox;
	long		last_frame;
} t_data;
int		render(t_data *data);
int		key_pressed(int keycode, t_data *data);
int		my_mlx_pixel_put(t_buffer *data, int x, int y, t_color color);
void	draw_brick(t_brick *brick, t_buffer *buffer);
void	draw_player(t_player *player, t_buffer *buffer);
void	draw_ball(t_ball *ball, t_buffer *buffer);
void	clear_buffer(t_data *data);
#endif