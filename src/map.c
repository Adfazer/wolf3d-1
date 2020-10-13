#include "../includes/wolf3d.h"

static void	validate_map(char *map, int map_size, t_map *map_struct)
{
	int		len_first;
	int		curr_start;
	int		i;

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

static char	*get_map(int *was_read, char *b)
{
	char	*s;
	int		fd;
	
	s = ft_strnew(MAP_MAX_SIZE + 1);
	fd = open(b, O_RDONLY);
	fd < 0 ? error("cant open") : 0;
	read(fd, s, 0) < 0 ? error("cant read") : 0;
	*was_read = read(fd, s, MAP_MAX_SIZE + 1);
	if (*was_read > MAP_MAX_SIZE || *was_read < MAP_MIN_SIZE)
		error("too big map");
	return s;
}

static void	check_logic(t_map *map)
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



void		check_start(t_map *map)
{
	int		start_counter;
	int		i;

	start_counter = 0;
	i = -1;
	while (++i < map->w * map->h)
	{
		if (map->map[i] == TEX_START)
		{
			map->player_start = i;
			map->map[i] = TEX_FLOOR;
			start_counter++;
		}
	}
	!start_counter ? error("no player start position") : 0;
	start_counter > 1 ? error("ambiguous player start position") : 0;
}


void		init_mm(t_map *map)
{
	int		map_max_side;

	map_max_side = max(map->w, map->h);
	map->mm_cube = (W / 3) / map_max_side;
	map->mm_start.x = 16;
	map->mm_start.y = 16;
	map->mm_w = map->mm_cube * map->w;
	map->mm_h = map->mm_cube * map->h;
	map->mm_p_size = map->mm_cube / 4;
	map->mm_cube_coef = (float)map->mm_cube / CUBE;
	map->mm_map_coef = (float)map->mm_w / W;
	map->mm_show = 1;
}

void		map_init(t_map *map, char *b)
{
	int		map_size;
	char	*str_map;
	int		i;
	int		j;
	
	
	str_map = get_map(&map_size, b);
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
	map->w_pix = map->w * CUBE;
	map->h_pix = map->h * CUBE;
	free(str_map);
	check_start(map);
	check_logic(map);
	init_mm(map);
}
