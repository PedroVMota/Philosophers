/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 17:24:02 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/10 17:27:32 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	initallocation(t_data *database)
{
	database->philosophers = malloc(sizeof(pthread_t) * database->n_p);
	if (!database->philosophers)
		return (error(ALLOC_THREAD, database));
	database->forks = malloc(sizeof(pthread_mutex_t) * database->n_p);
	if (!database->forks)
		return (error(ALLOC_FORK, database));
	database->philo = malloc(sizeof(t_philo) * database->n_p);
	if (!database->philo)
		return (error(ALLOC_PHILO, database));
	database->edit = malloc(sizeof(t_philo) * database->n_p);
	if (!database->edit)
		return (error(ALLOC_PHILO, database));
	return (false);
}

bool	initdata(t_data *database, char **av)
{
	database->n_p = ft_atoi(av[0]);
	database->t_die = ft_atoi(av[1]);
	database->t_eat = ft_atoi(av[2]);
	database->t_sle = ft_atoi(av[3]);
	if (av[4])
		database->n_eat = ft_atoi(av[4]);
	else
		database->n_eat = INT_MAX;
	if (database->n_p < 1 || database->n_p > 200
		|| database->t_die <= 0 || database->t_eat <= 0
		|| database->t_sle <= 0 || database->n_eat <= 0)
		return (error(ERR_INVALID_VALUES, NULL));
	database->b_dead = 0;
	database->f_ph = 0;
	pthread_mutex_init(&database->write, NULL);
	pthread_mutex_init(&database->lock, NULL);
	return (false);
}

static bool	initmutex(t_data *db)
{
	int	i;

	i = -1;
	while (++i < db->n_p)
		pthread_mutex_init(&db->forks[i], NULL);
	i = -1;
	while (++i < db->n_p)
	{
		db->philo[i]._id = i + 1;
		db->philo[i].left_fork = &db->forks[i];
		db->philo[i].right_fork = &db->forks[(i + 1) % db->n_p];
		db->philo[i]._meals_eaten = 0;
		db->philo[i]._is_eating = false;
		db->philo[i].last_meal = get_time();
		db->philo[i].time_start = get_time();
		db->philo[i].any_died = &db->b_dead;
		db->philo[i].database = db;
	}
	return (false);
}

static void	set_philo_data(t_data *database)
{
	int	i;

	i = -1;
	while (++i < database->n_p)
	{
		database->philo[i]._id = i + 1;
		database->philo[i]._eat_count = 0;
		database->philo[i]._is_eating = false;
		database->philo[i]._time_to_die = database->t_die;
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
