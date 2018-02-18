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

void	putpixel_black_case2(t_draw *draw, int i, int j)
{
	*(draw->img + (j * draw->size_l + i *
			(draw->bpp / 8))) = (char)(255);
	*(draw->img + (j * draw->size_l + i *
			(draw->bpp / 8)) + 1) = (char)(255);
	*(draw->img + (j * draw->size_l + i *
			(draw->bpp / 8)) + 2) = (char)(255);
}

int		key_processing(int keycode, t_draw *draw)
{
	if (keycode == 53)
	{
		mlx_destroy_window(draw->mlx, draw->win);
//		clean_all(all);
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
	i = line_start;
	while (i <= line_end && i < HEIGHT)
	{
		putpixel_black_case2(wolf->draw, x, i);
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
		if (wolf->valid->map[wolf->raycast->map_x][wolf->raycast->map_y] != '0')
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
	raycast->camera_x = 2 * x / WIDTH - 1;
	raycast->ray_x = raycast->dir_x + raycast->plane_x * raycast->camera_x;
	raycast->ray_y = raycast->dir_y + raycast->plane_y * raycast->camera_x;
	raycast->map_x = (int)raycast->pos_x;
	raycast->map_y = (int)raycast->pos_y;
	raycast->del_dist_x = sqrt(1 + (raycast->ray_y * raycast->ray_y) /
								   (raycast->ray_x * raycast->ray_x));
	raycast->del_dist_y = sqrt(1 + (raycast->ray_x * raycast->ray_x) /
								   (raycast->ray_y * raycast->ray_y));
}

void 	image(t_wolf *wolf)
{
	int x;

	x = 0;
	while (x < WIDTH)
	{
		calculate_ray_direction(wolf->raycast, x);
		calculate_step_side_distance(wolf->raycast);
		find_wall(wolf);
		dda_line(wolf, x);
		x++;
	}
}

int 	main(int ac, char **av)
{
	t_wolf	*wolf;
	int		fd;
	int i =0;

	fd = open (av[1], O_RDONLY);
	wolf = init_wolf();
	if (check_map(fd, wolf) == 0)
	{
		// !!! clean !!!
		return (0);
	}
	if (wolf->valid->map[(int)wolf->raycast->pos_x][(int)wolf->raycast->pos_y] != 0)
		return (0);
	wolf->draw->mlx = mlx_init();
	wolf->draw->win = mlx_new_window(wolf->draw->mlx,
									WIDTH, HEIGHT, "wolf");
	wolf->draw->img_w = mlx_new_image(wolf->draw->mlx, WIDTH,
									 HEIGHT);
	wolf->draw->img = mlx_get_data_addr(wolf->draw->img_w, &wolf->draw->bpp,
									   &wolf->draw->size_l, &wolf->draw->en);
	while (wolf->valid->map[i])
	{
		ft_printf("%s", wolf->valid->map[i]);
		i++;
	}
	image(wolf);
	mlx_put_image_to_window(wolf->draw->mlx, wolf->draw->win,
							wolf->draw->img_w, 0, 0);
//	mlx_mouse_hook(draw->win, mouse_processing, all);
	mlx_hook(wolf->draw->win, 2, 5, key_processing, wolf->draw);
	mlx_loop(wolf->draw->mlx);
	return (0);
}