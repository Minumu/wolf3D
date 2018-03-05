/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshevchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 15:18:05 by tshevchu          #+#    #+#             */
/*   Updated: 2018/02/07 15:18:06 by tshevchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	putpixel_case3(t_draw *draw, int i, int j)
{
	*(draw->img + (j * draw->size_l + i *
			(draw->bpp / 8))) = (char)(66);
	*(draw->img + (j * draw->size_l + i *
			(draw->bpp / 8)) + 1) = (char)(244);
	*(draw->img + (j * draw->size_l + i *
			(draw->bpp / 8)) + 2) = (char)(98);
}

void	putpixel_case1(t_draw *draw, int i, int j)
{
	*(draw->img + (j * draw->size_l + i *
			(draw->bpp / 8))) = (char)(244);
	*(draw->img + (j * draw->size_l + i *
			(draw->bpp / 8)) + 1) = (char)(203);
	*(draw->img + (j * draw->size_l + i *
			(draw->bpp / 8)) + 2) = (char)(66);
}

void	putpixel_case4(t_draw *draw, int i, int j)
{
	*(draw->img + (j * draw->size_l + i *
			(draw->bpp / 8))) = (char)(244);
	*(draw->img + (j * draw->size_l + i *
			(draw->bpp / 8)) + 1) = (char)(66);
	*(draw->img + (j * draw->size_l + i *
			(draw->bpp / 8)) + 2) = (char)(155);
}

void	putpixel_case2(t_draw *draw, int i, int j)
{
	*(draw->img + (j * draw->size_l + i *
			(draw->bpp / 8))) = (char)(244);
	*(draw->img + (j * draw->size_l + i *
			(draw->bpp / 8)) + 1) = (char)(66);
	*(draw->img + (j * draw->size_l + i *
			(draw->bpp / 8)) + 2) = (char)(179);
}

int		key_processing_release(int keycode, t_wolf *wolf)
{
	if (keycode == 126 || keycode == 13)
		wolf->move->up = 0;
	else if (keycode == 125 || keycode == 1)
		wolf->move->down = 0;
	else if (keycode == 124 || keycode == 2)
		wolf->move->right = 0;
	else if (keycode == 123 || keycode == 0)
		wolf->move->left = 0;
	image(wolf);
	if (keycode == 53)
	{
		mlx_destroy_window(wolf->draw->mlx, wolf->draw->win);
		clean_all(wolf);
		exit(0);
	}
	return (0);
}

int		key_processing(int keycode, t_wolf *wolf)
{
	if (keycode == 126 || keycode == 13)
		wolf->move->up = 1;
	else if (keycode == 125 || keycode == 1)
		wolf->move->down = 1;
	else if (keycode == 124 || keycode == 2)
		wolf->move->right = 1;
	else if (keycode == 123 || keycode == 0)
		wolf->move->left = 1;
	image(wolf);
	 if (keycode == 53)
	{
		mlx_destroy_window(wolf->draw->mlx, wolf->draw->win);
		clean_all(wolf);
		exit(0);
	}
	return (0);
}

void	dda_line(t_wolf *wolf, int x)
{
	int line_height;
	int line_start;
	int line_end;
	int i;

	line_height = (int)(HEIGHT / wolf->raycast->perp_dist);
	line_start = -line_height / 2 + HEIGHT / 2;
	if (line_start < 0)
		line_start = 0;
	line_end = line_height / 2 + HEIGHT / 2;
	if (line_end >= HEIGHT)
		line_end = HEIGHT - 1;
	i = 0;
	while (i < line_start)
	{
		putpixel_case1(wolf->draw, x, i); //above
		i++;
	}
	while (i <= line_end)
	{
		if (wolf->raycast->wall_side == 1)
			putpixel_case2(wolf->draw, x, i);
		else
			putpixel_case4(wolf->draw, x, i);
		i++;
	}
	while ( i < HEIGHT)
	{
		putpixel_case3(wolf->draw, x, i); // below
		i++;
	}
}

void	find_wall(t_wolf *wolf)
{
	int wall;

	wall = 0;
	while (wall == 0)
	{
		if (wolf->raycast->side_x < wolf->raycast->side_y)
		{
			wolf->raycast->side_x += wolf->raycast->del_dist_x;
			wolf->raycast->map_x += wolf->raycast->step_x;
			wolf->raycast->wall_side = 0;
		}
		else
		{
			wolf->raycast->side_y += wolf->raycast->del_dist_y;
			wolf->raycast->map_y += wolf->raycast->step_y;
			wolf->raycast->wall_side = 1;
		}
		if (wolf->valid->wolf_map[wolf->raycast->map_x][wolf->raycast->map_y] != 0)
			wall = 1;
	}
	if (wolf->raycast->wall_side == 0)
		wolf->raycast->perp_dist = (wolf->raycast->map_x - wolf->raycast->pos_x
		+ (1 - wolf->raycast->step_x) / 2) / wolf->raycast->ray_x;
	else
		wolf->raycast->perp_dist = (wolf->raycast->map_y - wolf->raycast->pos_y
		+ (1 - wolf->raycast->step_y) / 2) / wolf->raycast->ray_y;
}

void	calculate_step_side_distance(t_raycast *raycast)
{
	if (raycast->ray_x < 0)
	{
		raycast->step_x = -1;
		raycast->side_x = (raycast->pos_x - raycast->map_x) * raycast->del_dist_x;
	}
	else
	{
		raycast->step_x = 1;
		raycast->side_x = (raycast->map_x + 1 - raycast->pos_x) * raycast->del_dist_x;
	}
	if (raycast->ray_y < 0)
	{
		raycast->step_y = -1;
		raycast->side_y = (raycast->pos_y - raycast->map_y) * raycast->del_dist_y;
	}
	else
	{
		raycast->step_y = 1;
		raycast->side_y = (raycast->map_y + 1 - raycast->pos_y) * raycast->del_dist_y;
	}
}

void	calculate_ray_direction(t_raycast *raycast, int x)
{
	raycast->camera_x = 2 * x / (double)(WIDTH) - 1;
	raycast->ray_x = raycast->dir_x + raycast->plane_x * raycast->camera_x;
	raycast->ray_y = raycast->dir_y + raycast->plane_y * raycast->camera_x;
	raycast->map_x = (int)raycast->pos_x;
	raycast->map_y = (int)raycast->pos_y;
	raycast->del_dist_x = sqrt(1 + (raycast->ray_y * raycast->ray_y) /
						(raycast->ray_x * raycast->ray_x));
	raycast->del_dist_y = sqrt(1 + (raycast->ray_x * raycast->ray_x) /
						(raycast->ray_y * raycast->ray_y));
}

int 	image(t_wolf *wolf)
{
	int x;

	x = 0;
	wolf->raycast->prev_frame = clock();
	if (wolf->move->up == 1)
		move_up(wolf);
	else if (wolf->move->down == 1)
		move_down(wolf);
	else if (wolf->move->right == 1)
		move_right(wolf);
	else if (wolf->move->left == 1)
		move_left(wolf);
	while (x < WIDTH)
	{
		calculate_ray_direction(wolf->raycast, x);
		calculate_step_side_distance(wolf->raycast);
		find_wall(wolf);
		dda_line(wolf, x);
		x++;
	}
	wolf->raycast->curr_frame = wolf->raycast->prev_frame + (CLOCKS_PER_SEC / 100);
	wolf->raycast->curr_frame = clock();
//	printf("%lf\n", wolf->raycast->curr_frame);
	wolf->raycast->frame_time = (wolf->raycast->curr_frame - wolf->raycast->prev_frame) / CLOCKS_PER_SEC;
//	printf("%lf\n", wolf->raycast->frame_time);
	wolf->raycast->move_speed = wolf->raycast->frame_time * 2;
	wolf->raycast->rot_speed = wolf->raycast->frame_time * 2;
	printf("%lf\n", wolf->raycast->move_speed);
//	printf("%lf\n", wolf->raycast->pos_x);
//	printf("%lf\n", wolf->raycast->pos_y);
	mlx_put_image_to_window(wolf->draw->mlx, wolf->draw->win,
							wolf->draw->img_w, 0, 0);
	return (1);
}



int 	main(int ac, char **av)
{
	t_wolf	*wolf;
	int		fd;

	if (ac != 2)
	{
		ft_printf("Please, choose one map :)\n");
		return (0);
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		ft_printf("Oh man, this map isn't exist :(\n");
		return (0);
	}
	wolf = init_wolf();
	if (check_map(fd, wolf) == 0)
	{
		clean_all(wolf);
		return (0);
	}
	if (wolf->valid->wolf_map[(int)wolf->raycast->pos_x][(int)wolf->raycast->pos_y] != 0)
	{
		ft_printf("Oh man, change your start position, please\n");
		clean_all(wolf);
		return (0);
	}
	wolf->draw->mlx = mlx_init();
	wolf->draw->win = mlx_new_window(wolf->draw->mlx,
									WIDTH, HEIGHT, "wolf");
	wolf->draw->img_w = mlx_new_image(wolf->draw->mlx, WIDTH,
									 HEIGHT);
	wolf->draw->img = mlx_get_data_addr(wolf->draw->img_w, &wolf->draw->bpp,
									   &wolf->draw->size_l, &wolf->draw->en);
	image(wolf);
	mlx_hook(wolf->draw->win, 2, 0, key_processing, wolf);
	mlx_hook(wolf->draw->win, 3, 0, key_processing_release, wolf);
	mlx_loop(wolf->draw->mlx);
	return (0);
}