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

	x = brick->start.x + 1;
	while (x < brick->start.x + brick->width)
	{
		y = brick->start.y ;
		while (y < brick->start.y + brick->height - 1)
		{
			if ((y == brick->start.y)
			 || (x == brick->start.x + brick->width - 1))
			{
				t_color white = {0xFFFFFF};
				my_mlx_pixel_put(buffer, x, y, white);
			}
			else
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
	color.s_rgb.r = 0;
	color.s_rgb.g = 0;
	color.s_rgb.b = 255;
	t_color white = {0xFFFFFF};
	while (x < player->pos.x + player->width)
	{
		y = player->pos.y;
		while (y < player->pos.y + player->height)
		{
			if (y == player->pos.y )
				my_mlx_pixel_put(buffer, x, y, white);
			else
				my_mlx_pixel_put(buffer, x, y, color);
			y++;

		}
		x++;
		color.s_rgb.r +=1;
//		color.s_rgb.g -=2;
		color.s_rgb.b -=1;
	}
}

void	draw_ball(t_ball *ball, t_buffer *buffer)
{
	int x;
	int y;

	x = ball->pos.x - ball->radius;
	t_color white = {0xFFFFFF};
	while (x < ball->pos.x + ball->radius)
	{
		y = ball->pos.y - ball->radius;
		while (y < ball->pos.y + ball->radius)
		{
			double d = sqrt(pow(x - ball->pos.x, 2) + pow(y - ball->pos.y, 2));
			if (d  <= ball->radius)
			{
				t_color c;
				c.color = ball->color.color;
				c.s_rgb.r = c.s_rgb.r * (1 - d / ball->radius);
				c.s_rgb.g = 255;
				c.s_rgb.b = 255;
				my_mlx_pixel_put(buffer, x, y, c);
			}
			y++;
		}
		x++;
	}
}