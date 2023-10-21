/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 19:38:49 by pedro             #+#    #+#             */
/*   Updated: 2023/09/24 08:50:42 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool solo(t_data *database)
{
	database->start = get_time();
	printf("TimeStamp: %lu ms\n", get_time() - database->start);
	if (pthread_create(&database->philosophers[0], NULL, &routine, &database->philo[0]))
		return error(TH_ERR, database);
	pthread_detach(database->philosophers[0]);
	while (database->_is_dead == 0)
		usleep(0);
	return false;
}

bool error(char *msg, t_data *database)
{
	printf("Error: %s\n", msg);
	if (database)
		ft_exit(database);
	return (true);
}

static void delete_mallocs(t_data *database)
{
	if (database->philosophers)
	{
		free(database->philosophers);
		database->philosophers = NULL;
	}
	if (database->forks)
	{
		free(database->forks);
		database->forks = NULL;
	}
	if (database->philo)
	{
		free(database->philo);
		database->philo = NULL;
	}
}
void ft_exit(t_data *database)
{
	int i;

	i = -1;
	while (++i < database->_number_of_philosophers)
	{
		pthread_mutex_destroy(&database->forks[i]);
		pthread_mutex_destroy(&database->philo[i].lock);
	}
	pthread_mutex_destroy(&database->write);
	pthread_mutex_destroy(&database->lock);
	delete_mallocs(database);
}

int main(int ac, char **av)
{
	t_data database;
	if (ac < 5 || ac > 6)
		return (1);
	if (input(&av[1]))
		return (1);
	if (init(&av[1], &database))
		return (1);
	if (database._number_of_philosophers == 1)
		solo(&database);
	ft_exit(&database);
}