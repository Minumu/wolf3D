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
	valid->wolf_map = 0;
	valid->map_len_y = 0;
	valid->above_line = 0;
	return (valid);
}

t_raycast	*init_raycast(void)
{
	t_raycast *raycast;

	raycast = malloc(sizeof(t_raycast));
	raycast->pos_x = 3;
	raycast->pos_y = 3;
	raycast->dir_x = 1;
	raycast->dir_y = 0;
	raycast->plane_x = 0;
	raycast->plane_y = 0.66;
	raycast->curr_frame = 0;
	raycast->prev_frame = 0;
	raycast->frame_time = 0;
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
	raycast->move_speed = 0;
	raycast->rot_speed = 0;
	return (raycast);
}

t_move		*init_movement(void)
{
	t_move *move;

	move = malloc(sizeof(t_move));
	move->up = 0;
	move->down = 0;
	move->right = 0;
	move->left = 0;
	return (move);
}

t_wolf		*init_wolf(void)
{
	t_wolf *wolf;

	wolf = malloc(sizeof(t_wolf));
	wolf->draw = init_draw();
	wolf->valid = init_validation();
	wolf->raycast = init_raycast();
	wolf->move = init_movement();
	return (wolf);
}