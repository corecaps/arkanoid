//
// Created by corecaps on 17/02/23.
//

#include "arkanoid.h"

int render(t_data *data)
{
	clear_buffer(data);
	data->player->pos.x += data->player->velocity;
	if (data->player->pos.x + data->player->width > 800 || data->player->pos.x < 0)
		data->player->velocity = data->player->velocity * -1;
	float distance_threshold = 0.1;
	// Calculate the ball's movement vector
	t_point vector = { sin(data->ball->angle) * data->ball->velocity,
					   cos(data->ball->angle) * data->ball->velocity };
	// Move the ball
	float distance_moved = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
	data->ball->pos.x += vector.x;
	data->ball->pos.y += vector.y;
	t_brick_list *cursor = data->bricks;
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
// Check for collisions if the ball has moved a significant distance
	if (distance_moved > distance_threshold) {
		if (data->ball->pos.x + data->ball->radius > 800) {
			data->ball->pos.x = 800 - data->ball->radius;
			data->ball->angle = 2 * M_PI - data->ball->angle;
		} else if (data->ball->pos.x - data->ball->radius < 0) {
			data->ball->pos.x = data->ball->radius;
			data->ball->angle = 2 * M_PI - data->ball->angle;
		} else if (data->ball->pos.y + data->ball->radius > 600) {
			// Ball falls out of screen, game over
			printf("Game over!\nScore : %d", data->player->score);
			exit(0);
		} else if (data->ball->pos.y - data->ball->radius < 0) {
			data->ball->pos.y = data->ball->radius;
			data->ball->angle = M_PI - data->ball->angle;
		}
		// Check for collision with player bar
		float player_left_edge = data->player->pos.x;
		float player_right_edge = data->player->pos.x + data->player->width;
		float ball_left_edge = data->ball->pos.x - data->ball->radius;
		float ball_right_edge = data->ball->pos.x + data->ball->radius;
		float ball_bottom_edge = data->ball->pos.y + data->ball->radius;
		float ball_top_edge = data->ball->pos.y - data->ball->radius;

		if (ball_bottom_edge >= data->player->pos.y && ball_top_edge <= data->player->pos.y + data->player->height
			&& ball_right_edge >= player_left_edge && ball_left_edge <= player_right_edge) {
			// Ball collided with player bar
			data->ball->pos.y = data->player->pos.y - data->ball->radius;
			data->ball->angle = M_PI - data->ball->angle;
		}
		if (data->bricks != NULL
			&& data->ball->pos.y - data->ball->radius > data->brick_hitbox.start_y
			&& data->ball->pos.y + data->ball->radius < data->brick_hitbox.end_y
			&& data->ball->pos.x - data->ball->radius > data->brick_hitbox.start_x
			&& data->ball->pos.x + data->ball->radius < data->brick_hitbox.end_x)
		{
			t_brick_list *curr_brick = data->bricks;
			while (curr_brick != NULL)
			{
				t_brick brick = curr_brick->brick;
				if (data->ball->pos.x + data->ball->radius >= brick.start.x
					&& data->ball->pos.x - data->ball->radius <=
					   brick.start.x + brick.width
					&& data->ball->pos.y + data->ball->radius >= brick.start.y
					&& data->ball->pos.y - data->ball->radius <=
					   brick.start.y + brick.height)
				{
					// Ball collided with brick
					brick.resistance--;
					if (brick.resistance <= 0)
					{
						data->player->score *= 1.5;
						data->player->score += 42;
						if (data->player->width > 50)
							data->player->width -= 2;
						// Remove brick from list
						if (data->bricks == curr_brick)
						{
							data->bricks = curr_brick->next;
							free(curr_brick);
							curr_brick = data->bricks;
						}
						else
						{
							t_brick_list *prev_brick = data->bricks;
							while (prev_brick->next != curr_brick)
							{
								prev_brick = prev_brick->next;
							}
							prev_brick->next = curr_brick->next;
							free(curr_brick);

							curr_brick = prev_brick->next;
						}
					}

					// Bounce ball off brick
					if (data->ball->pos.y + data->ball->radius >= brick.start.y
						&& data->ball->pos.y - data->ball->radius <=
						   brick.start.y + brick.height)
					{
						// Ball hit brick from the side
						data->ball->angle = M_PI - data->ball->angle;
					}
					else
					{
						// Ball hit brick from top/bottom
						data->ball->angle = 2 * M_PI - data->ball->angle;
					}
					data->ball->velocity += 0.05;
					break;
				}
				else
				{
					curr_brick = curr_brick->next;
				}
			}
		}
	}

// Clamp the ball's position to the screen bounds
	if (data->ball->pos.x + data->ball->radius > 800)
		data->ball->pos.x = 800 - data->ball->radius;
	if (data->ball->pos.x - data->ball->radius < 0)
		data->ball->pos.x = data->ball->radius;
	if (data->ball->pos.y + data->ball->radius > 600)
		data->ball->pos.y = 600 - data->ball->radius;
	if (data->ball->pos.y - data->ball->radius < 0)
		data->ball->pos.y = data->ball->radius;
	if (data->ball->angle > 2 * M_PI)
		data->ball->angle -= 2 * M_PI;
	else if (data->ball->angle < 0)
		data->ball->angle += 2 * M_PI;

//	vector.x = sin(data->ball->angle) * data->ball->velocity;
//	vector.y = cos(data->ball->angle) * data->ball->velocity;

	if (data->ball->pos.x + data->ball->radius > 800)
		data->ball->pos.x = 800 - data->ball->radius;
	if (data->ball->pos.x - data->ball->radius < 0)
		data->ball->pos.x = data->ball->radius;
	if (data->ball->pos.y + data->ball->radius > 600)
		data->ball->pos.y = 600 - data->ball->radius;
	if (data->ball->pos.y - data->ball->radius < 0)
		data->ball->pos.y = data->ball->radius;
	cursor = data->bricks;
	while (cursor)
	{
		draw_brick(&cursor->brick,data->img_buffer);
		cursor = cursor->next;
	}
	t_color white = {0xFFFFFF};

	for (int x = 0; x < 800; x++)
	{
		if (data->ball->pos.y + data->ball->radius >= 580)
		{
			white.s_rgb.g = 0;
			white.s_rgb.b = 0;
		}
		my_mlx_pixel_put(data->img_buffer, x, 580,white);
	}
	draw_player(data->player,data->img_buffer);
	draw_ball(data->ball,data->img_buffer);
	mlx_put_image_to_window(data->mlx,
							data->mlx_win,
							data->img_buffer->img,
							0 ,0);
//	printf("Brick hit box (%f,%f) (%f,%f)\n", data->brick_hitbox.start_x, data->brick_hitbox.start_y, data->brick_hitbox.end_x, data->brick_hitbox.end_y);
	char *str = malloc(sizeof(char) * 100);
	sprintf(str,"42NOID SCORE : %d", data->player->score);
	mlx_string_put(data->mlx, data->mlx_win, 350, 10, 0xFF0000, str);
	free(str);
	return (0);
}