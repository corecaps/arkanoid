//
// Created by corecaps on 17/02/23.
//

#include "arkanoid.h"

int render(t_data *data)
{
	mlx_put_image_to_window(data->mlx,
							data->mlx_win,
							data->img_buffer->img,
							0 ,0);
	return (0);
}