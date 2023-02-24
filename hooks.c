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
	return (0);
}