#include "philosophers.h"

t_table *table(void)
{
	static t_table table;
	return &table;
}


int	setup(t_table *table, char **av)
{
	table->philo_n = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->n_of_eats = ft_atoi(av[5]);
	if (table->philo_n == 0 || table->time_to_die == 0
		|| table->time_to_eat == 0 || table->time_to_sleep == 0
		|| table->n_of_eats == 0)
		return (1);
	table->philosophers = (pthread_t *)malloc(sizeof(pthread_t)
		* table->philo_n);
	if (!table->philosophers)
		return (1);
    table->forks = (pfork_t *)malloc(sizeof(pfork_t) * table->philo_n);
    if(!table->forks)
        return 1;
    for (int x = 0; x < table->philo_n; x++)
        table->forks[x] = 1;
	return (0);
}

long	ft_atoi(const char *str)
{
	long	i;
	long	total;
	long	sign;

	sign = 1;
	total = 0;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -sign;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		total *= 10;
		total += str[i] - 48;
		i++;
	}
	return (total * sign);
}
