#include "wolf.h"

t_draw		*init_draw(void)
{
	t_draw *draw;

	draw = malloc(sizeof(t_draw));
	draw->mlx = NULL;
	draw->win = NULL;
	draw->img_w = NULL;
	draw->img = NULL;
	return (draw);
}

t_valid		*init_validation(void)
{
	t_valid *valid;

	valid = malloc(sizeof(t_valid));
	valid->len = 0;
	valid->line = 0;
	valid->map = NULL;
	return (valid);
}

t_raycast	*init_raycast(void)
{
	t_raycast *raycast;

	raycast = malloc(sizeof(t_raycast));
	raycast->pos_x = 1;
	raycast->pos_y = 2;
	raycast->dir_x = -1;
	raycast->dir_y = 0;
	raycast->plane_x = 0;
	raycast->plane_y = 0.66;
	raycast->curr_frame = 0;
	raycast->prev_frame = 0;
	raycast->camera_x = 0;
	raycast->ray_x = 0;
	raycast->ray_y = 0;
	raycast->map_x = 0;
	raycast->map_y = 0;
	raycast->side_x = 0;
	raycast->side_y = 0;
	raycast->del_dist_x = 0;
	raycast->del_dist_y = 0;
	raycast->perp_dist = 0;
	raycast->step_x = 0;
	raycast->step_y = 0;
	raycast->wall_side = -1;
	return (raycast);
}

t_wolf		*init_wolf(void)
{
	t_wolf *wolf;

	wolf = malloc(sizeof(t_wolf));
	wolf->draw = init_draw();
	wolf->valid = init_validation();
	wolf->raycast = init_raycast();
	return (wolf);
}