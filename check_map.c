#include "wolf.h"

void	map_to_int(t_valid *valid)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	valid->wolf_map = (int**)malloc(sizeof(int*) * valid->map_len_y);
	while (i < valid->map_len_y)
	{
		j = 0;
		valid->wolf_map[i] = (int*)malloc(sizeof(int) * valid->len);
		while (j < valid->len)
		{
			valid->wolf_map[i][j] = ft_atoi(valid->map[k]);
			j++;
			k++;
		}
		i++;
	}
}

int		count_line_length(char *line, t_valid *valid)
{
	char	**split;
	char	**temp;
	int		len;

	split = ft_strsplit(line, ' ');
	len = 0;
	while (split[len])
		len++;
	if (valid->map == NULL)
		valid->map = ft_strdup_double_arr(split);
	else
	{
		temp = ft_strdup_double_arr(valid->map);
		free_double_arr(valid->map);
		valid->map = ft_strjoin_double_arr(temp, split);
		free_double_arr(temp);
	}
	valid->map_len_y++;
	free_double_arr(split);
	return (len);
}

int		is_coord(const char *line, int *i)
{
	while (line[(*i)] && line[(*i)] != ' ')
	{
		if (line[(*i)] == '0' || line[(*i)] == '1')
			(*i)++;
		else
			return (0);
	}
	return (1);
}

int		validate_line(char *line)
{
	int i;

	i = 0;
	if (line[0] == '0')
		return (0);
	while (line[i])
	{
		if (is_coord(line, &i) == 0)
			return (0);
		while (line[i] && line[i] == ' ')
			i++;
	}
	if (line[i - 1] == '0')
		return (0);
	return (1);
}

int 	valid_above_line(t_wolf *wolf, char *line)
{
	int i;

	i = 0;
	if (wolf->valid->above_line == 0)
	{
		while (line[i])
		{
			if (line[i] == '0')
			{
				ft_printf("Oh man, this map isn't valid (check walls)\n");
				ft_strdel(&line);
				return (0);
			}
			i++;
		}
		wolf->valid->above_line = 1;
	}
	return (1);
}

int		is_error(char *line, t_wolf *wolf)
{
	if (!line || !validate_line(line))
	{
		ft_printf("Oh man, this map isn't valid\n");
		return (0);
	}
	if (valid_above_line(wolf, line) == 0)
		return (0);
	wolf->valid->line = count_line_length(line, wolf->valid);
	if (wolf->valid->len == 0)
		wolf->valid->len = wolf->valid->line;
	else if (wolf->valid->line != wolf->valid->len)
	{
		ft_printf("Oh man, varied lengths of lines in map\n");
		ft_strdel(&line);
		return (0);
	}
	return (1);
}

int 	valid_below_line(char *last)
{
	int	i;

	i = 0;
	while (last[i])
	{
		if (last[i] == '0')
		{
			ft_printf("Oh man, this map isn't valid (check walls)\n");
			ft_strdel(&last);
			return (0);
		}
		i++;
	}
	return (1);
}

int		check_map(int fd, t_wolf *wolf)
{
	char *line;
	char *last;

	line = NULL;
	last = NULL;
	while (get_next_line(fd, &line))
	{
		if (!is_error(line, wolf))
			return (0);
		if (last != NULL)
			ft_strdel(&last);
		last = ft_strdup(line);
		ft_strdel(&line);
	}
	if (valid_below_line(last) == 0)
		return (0);
	ft_strdel(&last);
	if (wolf->valid->len == 0)
	{
		ft_printf("Oh man, this map is empty\n");
		return (0);
	}
	ft_strdel(&line);
	map_to_int(wolf->valid);
	return (1);
}
