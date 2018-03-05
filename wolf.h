#ifndef WOLF_H
# define WOLF_H

# include <math.h>
# include <time.h>

# include <stdio.h> // DELETE

# include "libft/include/libft.h"
# include "minilibx_macos/mlx.h"
# define HEIGHT 1000
# define WIDTH 1000

typedef struct	s_valid
{
	int 		len;
	int 		line;
	char		**map;
	int 		**wolf_map;
	int			map_len_y;
	int 		above_line;
}				t_valid;

typedef struct	s_draw
{
	void		*mlx;
	void		*win;
	void		*img_w;
	char		*img;
	int			bpp;
	int			size_l;
	int			en;
}				t_draw;

typedef struct	s_raycast
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		curr_frame;
	double		prev_frame;
	double		frame_time;
	double		camera_x;
	double		ray_x;
	double		ray_y;
	int 		map_x;
	int 		map_y;
	double		side_x;
	double		side_y;
	double		del_dist_x;
	double		del_dist_y;
	double		perp_dist;
	int 		step_x;
	int 		step_y;
	int 		wall_side;
	double		move_speed;
	double		rot_speed;
}				t_raycast;

typedef struct	s_move
{
	int			up;
	int 		down;
	int 		right;
	int 		left;
}				t_move;

typedef struct	s_wolf
{
	t_draw		*draw;
	t_valid		*valid;
	t_raycast	*raycast;
	t_move		*move;
}				t_wolf;

t_wolf		*init_wolf(void);
int		check_map(int fd, t_wolf *wolf);
void	move_up(t_wolf *wolf);
void	move_down(t_wolf *wolf);
void	move_right(t_wolf *wolf);
void	move_left(t_wolf *wolf);
int 	image(t_wolf *wolf);

char	**ft_strdup_double_arr(char **src);
char	**ft_strjoin_double_arr(char **s1, char **s2);
void	free_double_arr(char **arr);
void	clean_all(t_wolf *wolf);

#endif
