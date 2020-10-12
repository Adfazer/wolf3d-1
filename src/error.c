#include "wolf3d.h"

int		error(char *s)
{
    ft_printf("%s%s%s\n", C_RED, s, C_NRM);
    exit(EXIT_FAILURE);
}
