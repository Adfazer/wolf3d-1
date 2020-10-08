#include "../includes/wolf3d.h"

static void	validate_map(char *map, int map_size, t_map *map_struct)
{
	int len_first;
	int	curr_start;
	int	i;

	i = 0;
	len_first = -1;
	map_struct->h = 0;
	while (i < map_size)
	{
		curr_start = i;
		while (map[i] && map[i] != '\n')
		{
			if (!ft_strchr(CHARSET, map[i]))
				error("invalid char");
			i++;
		}
		i - curr_start < MAP_MIN_COL_NUM ? error("MIN COL") : 0;
		len_first = len_first == -1 ? i - curr_start : len_first;
		len_first != i - curr_start ? error("Diff row") : 0;
		i++;
		map_struct->h++;
	}
	map_struct->h < MAP_MIN_ROW_NUM ? error("min row") : 0;
	map_struct->w = len_first;
}

static char		*get_map(int *was_read)
{
	char	*s;
	int		fd;
	
	s = ft_strnew(MAP_MAX_SIZE + 1);
	fd = open(MAP_FILEPATH, O_RDONLY);
	fd < 0 ? error("cant open") : 0;
	read(fd, s, 0) < 0 ? error("cant read") : 0;
	*was_read = read(fd, s, MAP_MAX_SIZE + 1);
	if (*was_read > MAP_MAX_SIZE || *was_read < MAP_MIN_SIZE)
		error("too big map");
	return s;
}

static void		check_logic(t_map *map)
{
	int		i;
	char	*s;

	i = -1;
	s = NULL;
	while (++i < map->w)
	{
		if (!ft_strchr(WALLSET, map->map[i])
		|| !ft_strchr(WALLSET, map->map[map->w * (map->h - 1) + i]))
		{
			ft_asprintf(&s,
				"There must be a border texture at column %d", i);
			error(s);
		}
	}
	i = -1;
	while (++i < map->h)
	{
		if (!ft_strchr(WALLSET, map->map[i * map->w])
		|| !ft_strchr(WALLSET, map->map[i * map->w + (map->w - 1)]))
		{
			ft_asprintf(&s,
				"There must be a border texture at row %d", i);
			error(s);
		}
	}
}

void		init_map(t_map *map)
{
	int		map_size;
	char	*str_map;
	int		i;
	int		j;
	
	
	str_map = get_map(&map_size);
	validate_map(str_map, map_size, map);
	map->map =ft_strnew(map->h * map->w);
	!map->map ? error("malloc") : 1;

	map->mm_start.x = 16;
	map->mm_start.y = 16;

	map->mm.x = 4;
	map->mm.y = 4;
	map->mm_cube.x = CUBE / map->mm.x;
	map->mm_cube.y = CUBE / map->mm.y;
	i = -1;
	j = 0;
	while (++i < map_size)
	{
		if (str_map[i] != '\n')
			map->map[j++] = str_map[i];
	}
	//map_rect_w(map);
	free(str_map);
	check_logic(map);
}
