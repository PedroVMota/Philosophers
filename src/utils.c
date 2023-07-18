#include "philosophers.h"

t_table *table(void)
{
	static t_table table;
	return &table;
}

void set_forks(t_table *table)
{
	int i = 0;
	while(i < table->philo_n)
	{
		if (i == 0)
		{
			
		}
	}
}

int setup_part_2(t_table *table)
{
	table->phi_thread = (pthread_t *)malloc(sizeof(pthread_t) * table->philo_n);
	if (!table->phi_thread)
		return (1);
	table->arr_phi = (t_philo *)malloc(sizeof(t_philo) * table->philo_n);
	if (!table->arr_phi)
		return (1);
	table->forks = (t_forks *)malloc(sizeof(t_forks) * table->philo_n);
	if (!table->forks)
		return (1);
	for (int i = 0; i < table->philo_n; i++)
	{
		table->forks[i].is_using = 0;
		table->forks[i].forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!table->forks[i].forks)
			return (1);
		pthread_mutex_init(table->forks[i].forks, NULL);
		table->arr_phi[i].is_life = true;
		table->arr_phi[i].id = i;
		table->arr_phi[i].n_of_eats = 0;
		gettimeofday(&table->arr_phi[i].start, NULL);
	}
	set_forks(table);
	return (0);
}

int	setup(t_table *table, char **av)
{
	table->philo_n = ft_atoi(av[1]);
	table->time_to_die_ms = ft_atoi(av[2]);
	table->time_to_eat_ms = ft_atoi(av[3]);
	table->time_to_sleep_ms = ft_atoi(av[4]);
	table->n_of_eats = ft_atoi(av[5]);
	if (table->philo_n == 0 || table->time_to_die_ms == 0
		|| table->time_to_eat_ms == 0 || table->time_to_sleep_ms == 0
		|| table->n_of_eats == 0)
		return (1);
	if(setup_part_2(table))
		return 1;
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
