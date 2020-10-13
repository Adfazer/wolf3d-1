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

int		error_inv_c(char *s, char inv_char)
{
	ft_printf("%s%s%c%s\n", C_RED, s, inv_char, C_NRM);
    exit(EXIT_FAILURE);
}

int		error_inv_n(char *s, int inv_num)
{
	ft_printf("%s%s%d%s\n", C_RED, s, inv_num, C_NRM);
    exit(EXIT_FAILURE);
}