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