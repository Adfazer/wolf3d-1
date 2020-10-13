#include "wolf3d.h"

int		error(char *s)
{
    ft_printf("%s%s%s\n", C_RED, s, C_NRM);
    exit(EXIT_FAILURE);
}

int		error_free_s(char *s)
{
	ft_printf("%s%s%s\n", C_RED, s, C_NRM);
	free(s);
    exit(EXIT_FAILURE);
}