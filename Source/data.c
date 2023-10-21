#include "philo.h"

static bool initallocation(t_data *database)
{
	database->philosophers = malloc(sizeof(pthread_t) * database->_number_of_philosophers);
	if (!database->philosophers)
		return error(ALLOC_THREAD, database);
	database->forks = malloc(sizeof(pthread_mutex_t) * database->_number_of_philosophers);
	if (!database->forks)
		return error(ALLOC_FORK, database);
	database->philo = malloc(sizeof(t_philo) * database->_number_of_philosophers);
	if (!database->philo)
		return error(ALLOC_PHILO, database);
	return false;
}

bool initdata(t_data *database, char **av)
{
	database->_number_of_philosophers = ft_atoi(av[0]);
	database->_time_to_die = ft_atoi(av[1]);
	database->_time_to_eat = ft_atoi(av[2]);
	database->_time_to_sleep = ft_atoi(av[3]);
	if (av[4])
		database->_number_of_times_each_philosopher_must_eat = ft_atoi(av[4]);
	else
		database->_number_of_times_each_philosopher_must_eat = -1;
	if (database->_number_of_philosophers < 1 || database->_number_of_philosophers > 200 || database->_time_to_die < 0 || database->_time_to_eat < 0 || database->_time_to_sleep < 0)
		return error(ERR_INVALID_VALUES, database);
	database->_is_dead = 0;
	database->_is_full = 0;
	pthread_mutex_init(&database->write, NULL);
	pthread_mutex_init(&database->lock, NULL);
	return false;
}

static bool initmutex(t_data *database)
{
	int i;

	i = -1;
	while (++i < database->_number_of_philosophers)
	{
		pthread_mutex_init(&database->forks[i], NULL);
	}
	database->philo[0].left_fork = &database->forks[0];
	database->philo[0].right_fork = &database->forks[database->_number_of_philosophers - 1];
	i = 1;
	while (++i < database->_number_of_philosophers)
	{
		database->philo[i].left_fork = &database->forks[i - 1];
		database->philo[i].right_fork = &database->forks[i];
	}
	return false;
}

static void set_philo_data(t_data *database)
{
	int i;

	i = -1;
	while (++i < database->_number_of_philosophers)
	{
		database->philo[i]._id = i + 1;
		database->philo[i]._eat_count = 0;
		database->philo[i]._is_eating = false;
		database->philo[i]._time_to_die = database->_time_to_die;
		database->philo[i]._mode = 0;
		database->philo[i].database = database;
		pthread_mutex_init(&database->philo[i].lock, NULL);
	}
}

bool init(char **av, t_data *database)
{
	if (initdata(database, av))
		return true;
	if (initallocation(database))
		return true;
	if (initmutex(database))
		return true;
	set_philo_data(database);
	return false;
}