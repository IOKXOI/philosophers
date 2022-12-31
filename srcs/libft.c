#include <stddef.h>

int s_atoi(char *str, int *nb)
{
	int	i;
	int number;

	i = 0;
	number = 0;
	//*nb = number;
	if (!str || str[i] == '\0')
		return(0);
	if (!(str[i] >= '0' && str[i] <= '9'))
		return(0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - 48);
		if (number + 1 < 0)
			return(0);
		i++;
	}
	*nb = number;
	if (str[i] && (!(str[i] >= '0' && str[i] <= '9')))
		return(0);
	return(1);
}
