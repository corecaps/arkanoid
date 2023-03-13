//
// Created by corecaps on 17/02/23.
//

#include "arkanoid.h"

int key_pressed(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		mlx_destroy_image(data->mlx,data->img_buffer->img);
		free(data->img_buffer);
		mlx_destroy_window(data->mlx,data->mlx_win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		free(data);
		exit(0);
	}
	if (keycode == 97 || keycode == 65361)
	{
		if (data->player->velocity > 0)
			data->player->velocity = -0.5;
		else
			data->player->velocity -= 0.1;
	}
	if (keycode == 100 || keycode == 65363)
	{
		if (data->player->velocity < 0)
			data->player->velocity = 0.5;
		else
			data->player->velocity += 0.1;
	}
	return (0);
}