#include "wolf.h"

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
//	map->map_y++;
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
	while (line[i])
	{
		if (is_coord(line, &i) == 0)
			return (0);
		while (line[i] && line[i] == ' ')
			i++;
	}
	return (1);
}

int		is_error(char *line, t_wolf *wolf)
{
	if (!line || !validate_line(line))
	{
		ft_printf("Oh, this map isn't valid\n");
		return (0);
	}
	wolf->valid->line = count_line_length(line, wolf->valid);
	if (wolf->valid->len == 0)
		wolf->valid->len = wolf->valid->line;
	else if (wolf->valid->line != wolf->valid->len)
	{
		ft_printf("Oh, varied lengths of lines in map\n");
		ft_strdel(&line);
		return (0);
	}
	ft_strdel(&line);
	return (1);
}

int		check_map(int fd, t_wolf *wolf)
{
	char *line;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		if (!is_error(line, wolf))
			return (0);
	}
	if (wolf->valid->len == 0)
	{
		ft_printf("Sorry, but this map is empty\n");
		return (0);
	}
	ft_strdel(&line);
	return (1);
}