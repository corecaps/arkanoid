/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 23:50:13 by jgarcia           #+#    #+#             */
/*   Updated: 2023/02/15 23:50:48 by jgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arkanoid.h"

int main(void)
{
	t_data	*data;

	data = malloc(sizeof (t_data));
	if (!data)
		return (1);
	data->img_buffer = malloc(sizeof(t_buffer));
	if (!data->img_buffer)
		return (1);
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx,800,600,"ARKANOID");
	data->img_buffer->img = mlx_new_image(data->mlx,
										  801,
										  601);
	data->img_buffer->address = mlx_get_data_addr(data->img_buffer->img,
												  &data->img_buffer->bit_per_pixel,
												  &data->img_buffer->line_length,
												  &data->img_buffer->endian);
	data->player = malloc(sizeof (t_player));
	data->player->pos.x = 400;
	data->player->pos.y = 550;
	data->player->width = 180;
	data->player->height = 20;
	data->player->velocity = 0.5;
	data->player->score = 42;
	data->ball = malloc(sizeof (t_ball));
	data->ball->pos.x = 400;
	data->ball->pos.y = 500;
	data->ball->radius = 10;
	data->ball->angle = M_PI / 4;
	data->ball->velocity = 0.8;
	data->ball->color.s_rgb.r = 255;
	data->ball->color.s_rgb.g = 0;
	data->ball->color.s_rgb.b = 0;

	data->bricks = malloc(sizeof (t_brick_list));
	t_brick_list *cursor = data->bricks;
	for (int j = 0; j < 8;j++)
	{
		for (int i = 0; i < (j * 2) + 3; i++)
		{
			cursor->brick.start.x = i * (800 / ((j * 2) + 3));
			cursor->brick.start.y = (j * 20) + 150 + (j * 4);
			cursor->brick.width = 800 / ((j * 2) + 3) - (j + 1);
			cursor->brick.height = 17;
			cursor->brick.color.s_rgb.r = (8 - j) * (255 / 8);
			cursor->brick.color.s_rgb.g = 0;
			cursor->brick.color.s_rgb.b = j * (255 / 8);
			cursor->brick.resistance = 1;

			if (i == 15 && j == 9)
				cursor->next = NULL;
			else
				cursor->next = malloc(sizeof(t_brick_list));
			cursor = cursor->next;
		}
	}
	cursor = data->bricks;
	data->brick_hitbox.start_x = cursor->brick.start.x;
	data->brick_hitbox.start_y = cursor->brick.start.y;
	data->brick_hitbox.end_x = cursor->brick.start.x + cursor->brick.width;
	data->brick_hitbox.end_y = cursor->brick.start.y + cursor->brick.height;
	while (cursor)
	{
		if (cursor->brick.start.x < data->brick_hitbox.start_x)
			data->brick_hitbox.start_x = cursor->brick.start.x;
		if (cursor->brick.start.y < data->brick_hitbox.start_y)
			data->brick_hitbox.start_y = cursor->brick.start.y;
		if (cursor->brick.start.x + cursor->brick.width > data->brick_hitbox.end_x)
			data->brick_hitbox.end_x = cursor->brick.start.x + cursor->brick.width;
		if (cursor->brick.start.y + cursor->brick.height > data->brick_hitbox.end_y)
			data->brick_hitbox.end_y = cursor->brick.start.y + 2 * cursor->brick.height;
		cursor = cursor->next;
	}
//	printf("brick hitbox start x: %f end x: %f start y: %f end y: %f",data->brick_hitbox.start_x,data->brick_hitbox.end_x,data->brick_hitbox.start_y,data->brick_hitbox.end_y);

	mlx_hook(data->mlx_win, 2, 1L << 0, key_pressed, data);
	mlx_loop_hook(data->mlx,render,data);
	mlx_loop(data->mlx);
//	mlx_destroy_image(data->mlx,data->img_buffer->img);
//	free(data->img_buffer);
//	mlx_destroy_window(data->mlx,data->mlx_win);
//	mlx_destroy_display(data->mlx);
//	free(data->mlx);
//	free(data);
	return (0);
}