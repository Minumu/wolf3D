#ifndef WOLF_H
# define WOLF_H

# include <math.h>
# include "libft/include/libft.h"
# include "minilibx_macos/mlx.h"
# define HEIGHT 500
# define WIDTH 500

typedef struct	s_valid
{
	int 		len;
	int 		line;
	char		**map;
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
}				t_raycast;

typedef struct	s_wolf
{
	t_draw		*draw;
	t_valid		*valid;
	t_raycast	*raycast;
}				t_wolf;

t_wolf		*init_wolf(void);
int		check_map(int fd, t_wolf *wolf);

char	**ft_strdup_double_arr(char **src);
char	**ft_strjoin_double_arr(char **s1, char **s2);
void	free_double_arr(char **arr);


#endif
