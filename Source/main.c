/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 19:38:49 by pedro             #+#    #+#             */
/*   Updated: 2023/11/26 22:23:30 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool solo(t_data *database)
{
	database->start = get_time();
	printf("TimeStamp: %llu ms\n", get_time() - database->start);
	if (pthread_create(&database->philosophers[0], NULL, &soloroutine, &database->philo[0]))
		return error(TH_ERR, database);
	pthread_detach(database->philosophers[0]);
	while (database->_is_dead == 0)
		usleep(0);
	return false;
}

bool normal(t_data *database)
{
	int i;

	i = -1;
	database->start = get_time();
	while (++i < database->_number_of_philosophers)
	{
		if (pthread_create(&database->philosophers[i], NULL, &routine, &database->philo[i]))
			return error(TH_ERR, database);
	}
	
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
	{
		printf("This nerror\n");
		return (1);
	}
	if (init(&av[1], &database))
	{
		printf("This error\n");
		return (1);
	}
	if (database._number_of_philosophers == 1)
		solo(&database);
	else if(database._number_of_philosophers > 1)
		normal(&database);
	printf("Executing: main\n");
	ft_exit(&database);
}