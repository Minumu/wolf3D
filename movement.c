#include "wolf.h"

void	move_up(t_wolf *wolf)
{
	int x;
	int y;

	x = (int)(wolf->raycast->pos_x + wolf->raycast->dir_x * wolf->raycast->move_speed);
	y = (int)(wolf->raycast->pos_y + wolf->raycast->dir_y * wolf->raycast->move_speed);
	if (wolf->valid->wolf_map[x][(int)wolf->raycast->pos_y] == 0)
		wolf->raycast->pos_x += wolf->raycast->dir_x * wolf->raycast->move_speed;
	if (wolf->valid->wolf_map[(int)wolf->raycast->pos_x][y] == 0)
		wolf->raycast->pos_y += wolf->raycast->dir_y * wolf->raycast->move_speed;
}

void	move_down(t_wolf *wolf)
{
	int x;
	int y;

	x = (int)(wolf->raycast->pos_x - wolf->raycast->dir_x * wolf->raycast->move_speed);
	y = (int)(wolf->raycast->pos_y - wolf->raycast->dir_y * wolf->raycast->move_speed);
	if (wolf->valid->wolf_map[x][(int)wolf->raycast->pos_y] == 0)
		wolf->raycast->pos_x -= wolf->raycast->dir_x * wolf->raycast->move_speed;
	if (wolf->valid->wolf_map[(int)wolf->raycast->pos_x][y] == 0)
		wolf->raycast->pos_y -= wolf->raycast->dir_y * wolf->raycast->move_speed;
}

void	move_left(t_wolf *wolf)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = wolf->raycast->dir_x;
	old_plane_x = wolf->raycast->plane_x;
	wolf->raycast->dir_x = wolf->raycast->dir_x * cos(-wolf->raycast->rot_speed) -
						   wolf->raycast->dir_y * sin(-wolf->raycast->rot_speed);
	wolf->raycast->dir_y = old_dir_x * sin(-wolf->raycast->rot_speed) +
						   wolf->raycast->dir_y * cos(-wolf->raycast->rot_speed);
	wolf->raycast->plane_x = wolf->raycast->plane_x * cos(-wolf->raycast->rot_speed) -
							 wolf->raycast->plane_y * sin(-wolf->raycast->rot_speed);
	wolf->raycast->plane_y = old_plane_x * sin(-wolf->raycast->rot_speed) +
							 wolf->raycast->plane_y * cos(-wolf->raycast->rot_speed);
}

void	move_right(t_wolf *wolf)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = wolf->raycast->dir_x;
	old_plane_x = wolf->raycast->plane_x;
	wolf->raycast->dir_x = wolf->raycast->dir_x * cos(wolf->raycast->rot_speed) -
						   wolf->raycast->dir_y * sin(wolf->raycast->rot_speed);
	wolf->raycast->dir_y = old_dir_x * sin(wolf->raycast->rot_speed) +
						   wolf->raycast->dir_y * cos(wolf->raycast->rot_speed);
	wolf->raycast->plane_x = wolf->raycast->plane_x * cos(wolf->raycast->rot_speed) -
							 wolf->raycast->plane_y * sin(wolf->raycast->rot_speed);
	wolf->raycast->plane_y = old_plane_x * sin(wolf->raycast->rot_speed) +
							 wolf->raycast->plane_y * cos(wolf->raycast->rot_speed);
}