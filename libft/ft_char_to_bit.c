#include "libft.h"

char    *ft_char_to_bit(int dec)
{
    char *bits;
	int		i;

    bits = malloc(sizeof(char) * 9);
	ft_bzero(bits, 9);
	i = 7;
	while (i >= 0)
	{
		if (dec % 2 == 0)
			bits[i] = '0';
		else
			bits[i] = '1';
		i--;
		dec = dec / 2;
	}
    return (bits);
}