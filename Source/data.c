/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 12:39:17 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/10 12:43:27 by pedromota        ###   ########.fr       */
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
	printf("n_philo: %d\n", database->n_p);
	database->db_nttd = ft_atoi(av[1]);
	database->db_tte = ft_atoi(av[2]);
	database->db_tts = ft_atoi(av[3]);
	if (av[4])
		database->db_nte = ft_atoi(av[4]);
	else
		database->db_nte = INT_MAX;
	if (database->n_p < 1 || database->n_p > 200
		|| database->db_nttd <= 0 || database->db_tte <= 0
		|| database->db_tts <= 0 || database->db_nte <= 0)
		return (error(ERR_INVALID_VALUES, NULL));
	database->_is_dead = 0;
	database->db_full_philos = 0;
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
		db->philo[i].any_died = &db->_is_dead;
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
		database->philo[i]._time_to_die = database->db_nttd;
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
