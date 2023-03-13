//
// Created by corecaps on 12/03/23.
//
#include "arkanoid.h"

/*******************************************************************************
** pixel put to image                                                          *
** found on : https://s.42l.fr/putpximg                                        *
*******************************************************************************/

int my_mlx_pixel_put(t_buffer *data, int x, int y, t_color color)
{
	char	*dst;
	dst = data->address + (y * data->line_length + x * (data->bit_per_pixel / 8));
	*(unsigned int*)dst = color.color;
	return (0);
}
void	clear_buffer(t_data *data)
{
	t_color black;
	black.s_rgb.r = 0;
	black.s_rgb.g = 0;
	black.s_rgb.b = 0;
	for (int y = 0; y < 600; y ++)
	{
		for (int x = 0;x < 800;x ++)
			my_mlx_pixel_put(data->img_buffer, x, y,black);
	}
}
void	draw_brick(t_brick *brick, t_buffer *buffer)
{
	int x;
	int y;

	x = brick->start.x;
	while (x < brick->start.x + brick->width)
	{
		y = brick->start.y;
		while (y < brick->start.y + brick->height)
		{
			my_mlx_pixel_put(buffer, x, y, brick->color);
			y++;
		}
		x++;
	}
}

void	draw_player(t_player *player, t_buffer *buffer)
{
	int x;
	int y;
	t_color color;

	x = player->pos.x;
	color.s_rgb.r = 255;
	color.s_rgb.g = 255;
	color.s_rgb.b = 255;
	while (x < player->pos.x + player->width)
	{
		y = player->pos.y;
		while (y < player->pos.y + player->height)
		{
			my_mlx_pixel_put(buffer, x, y, color);
			y++;
		}
		x++;
	}
}

void	draw_ball(t_ball *ball, t_buffer *buffer)
{
	int x;
	int y;

	x = ball->pos.x - ball->radius;
	while (x < ball->pos.x + ball->radius)
	{
		y = ball->pos.y - ball->radius;
		while (y < ball->pos.y + ball->radius)
		{
			if (sqrt(pow(x - ball->pos.x, 2) + pow(y - ball->pos.y, 2)) <= ball->radius)
				my_mlx_pixel_put(buffer, x, y, ball->color);
			y++;
		}
		x++;
	}
}