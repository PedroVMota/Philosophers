#include <philosophers.h>

void	clear_data(struct s_table	*data)
{
	if (data->tid)
		free(data->tid);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}


void	ft_exit(struct s_table *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].lock);
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
	clear_data(data);
}

int	error(char *str, struct s_table *data)
{
	printf("%s\n", str);
	if (data)
		ft_exit(data);
	return (1);
}

int64_t	get_time(void)
{
	struct timeval	tv;
	
	if (gettimeofday(&tv, NULL))
		return (error("gettimeofday() FAILURE\n", NULL));
	return ((tv.tv_sec * (int64_t)1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(suseconds_t time)
{
	int64_t	start;
	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return(0);
}