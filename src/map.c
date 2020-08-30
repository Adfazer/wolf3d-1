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

/*
void		prebuild_map(t_map *map)
{
	int		y;
	int		x;

	map->w = 8;
	map->h = 8;
	map->map = (int *)malloc(sizeof(int) * (map->w * map->h));
	y = -1;
	while (++y < map->h)
	{
		x = -1;
		while (++x < map->w)
			if (x == 0 || y == 0 || x == map->w - 1 || y == map->h - 1)
				map->map[y * map->w + x] = 11;
			else
				map->map[y * map->w + x] = 10;
	}
	map->map[1 * map->w + 3] = 15;
	map->map[2 * map->w + 3] = 12;
	map->map[5 * map->w + 5] = 12;
}
*/

/*
void	map_rect_w(t_map *map)
{
	int rect_w;
	int rect_h;

	rect_w = W_W / map->w / 3;
	rect_h = W_H / map->h / 3;
	if (rect_h < rect_w)
		map->rect_w = rect_h;
	else
		map->rect_w = rect_w;
}
*/

static void		check_logic(t_map *map)
{
	int		i;
	char	*s;

	i = -1;
	s = NULL;
	while (++i < map->w)
	{
		if (map->map[i] != TEX_BORDER
		|| map->map[map->w * (map->h - 1) + i] != TEX_BORDER)
		{
			ft_asprintf(&s,
				"There must be a border texture at column %d", i);
			error(s);
		}
	}
	i = -1;
	while (++i < map->h)
	{
		if (map->map[i * map->w] != TEX_BORDER
		|| map->map[i * map->w + (map->w - 1)] != TEX_BORDER)
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
