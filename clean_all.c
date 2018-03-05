#include "wolf.h"

void	free_int_array(t_valid *valid)
{
	int i;

	i = 0;
	if (valid->wolf_map)
	{
		while (i < valid->map_len_y)
		{
			free(valid->wolf_map[i]);
			i++;
		}
		free(valid->wolf_map);
	}
}

void	free_double_arr(char **arr)
{
	int i;

	i = 0;
	if (arr == NULL)
		return ;
	else
	{
		while (arr[i])
		{
			ft_strdel(&arr[i]);
			i++;
		}
		free(arr);
	}
}

void	clean_all(t_wolf *wolf)
{
	free_double_arr(wolf->valid->map);
	free_int_array(wolf->valid);
	free(wolf->valid);
	free(wolf->draw);
	free(wolf->move);
	free(wolf->raycast);
	free(wolf);
}