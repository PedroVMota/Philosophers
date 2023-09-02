#include <philosophers.h>

long	ft_atoi(const char *str)
{
	long	i;
	long	total;
	long	sign;

	sign = 1;
	total = 0;
	i = 0;
    if(!str)
        return 0;
	while ((str[i] == 32 || (str[i] >= 9 && str[i] <= 13)) && str[i] != 0)
		i++;
	if (str[i] == '-')
	{
		sign = -sign;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && str[i] != 0)
	{
		total *= 10;
		total += str[i] - 48;
		i++;
	}
	return (total * sign);
}
