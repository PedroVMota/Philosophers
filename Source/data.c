/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:08:25 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/10 16:17:07 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	initallocation(t_data *database)
{
	database->philosophers = malloc(sizeof(pthread_t) * database->ph_n);
	if (!database->philosophers)
		return (error(ALLOC_THREAD, database));
	database->forks = malloc(sizeof(pthread_mutex_t) * database->ph_n);
	if (!database->forks)
		return (error(ALLOC_FORK, database));
	database->philo = malloc(sizeof(t_philo) * database->ph_n);
	if (!database->philo)
		return (error(ALLOC_PHILO, database));
	database->edit = malloc(sizeof(t_philo) * database->ph_n);
	if (!database->edit)
		return (error(ALLOC_PHILO, database));
	return (false);
}

bool	initdata(t_data *database, char **av)
{
	database->ph_n = ft_atoi(av[0]);
	printf("n_philo: %d\n", database->ph_n);
	database->die_t = ft_atoi(av[1]);
	database->eat_t = ft_atoi(av[2]);
	database->sle_t = ft_atoi(av[3]);
	if (av[4])
		database->eat_n = ft_atoi(av[4]);
	else
		database->eat_n = INT_MAX;
	if (database->ph_n < 1 || database->ph_n > 200
		|| database->die_t <= 0 || database->eat_t <= 0
		|| database->sle_t <= 0 || database->eat_n <= 0)
		return (error(ERR_INVALID_VALUES, NULL));
	database->_is_dead = 0;
	database->f_philo = 0;
	pthread_mutex_init(&database->write, NULL);
	pthread_mutex_init(&database->lock, NULL);
	return (false);
}

static bool	initmutex(t_data *db)
{
	int	i;

	i = -1;
	while (++i < db->ph_n)
		pthread_mutex_init(&db->forks[i], NULL);
	i = -1;
	while (++i < db->ph_n)
	{
		db->philo[i]._id = i + 1;
		db->philo[i].left_fork = &db->forks[i];
		db->philo[i].right_fork = &db->forks[(i + 1) % db->ph_n];
		db->philo[i].meal_n = 0;
		db->philo[i].b_eatg = false;
		db->philo[i].last_meal = get_time();
		db->philo[i].time_start = get_time();
		db->philo[i].dead = &db->_is_dead;
		db->philo[i].database = db;
	}
	return (false);
}

static void	set_philo_data(t_data *database)
{
	int	i;

	i = -1;
	while (++i < database->ph_n)
	{
		database->philo[i]._id = i + 1;
		database->philo[i].eat_c = 0;
		database->philo[i].b_eatg = false;
		database->philo[i]._time_to_die = database->die_t;
		database->philo[i].database = database;
		pthread_mutex_init(&database->philo[i].lock, NULL);
	}
}

bool	init(char **av, t_data *database)
{
	if (initdata(database, av))
		return (true);
	if (initallocation(database))
		return (true);
	if (initmutex(database))
		return (true);
	set_philo_data(database);
	return (false);
}
