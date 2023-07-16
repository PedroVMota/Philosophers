/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:59:57 by pedromota         #+#    #+#             */
/*   Updated: 2023/07/15 21:08:38 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	setup(t_table *table, char **av)
{
	table->philo_n = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->n_of_eats = ft_atoi(av[4]);
	if (table->philo_n == 0 || table->time_to_die == 0
		|| table->time_to_eat == 0 || table->time_to_sleep == 0
		|| table->n_of_eats == 0)
		return (1);
	table->philosophers = (pthread_t *)malloc(sizeof(pthread_t)
		* table->philo_n);
	if (!table->philosophers)
		return (1);
	return (0);
}

void	*routine(void *id)
{
	int	thread_id;

	thread_id = *(int *)id;
	//printf("Thread %i > %d\n", thread_id, thread_id);
    (void) thread_id;
	return (NULL);
}

void	philosophers_init(t_table *center)
{
	int	i;
	int	thread_ids[center->philo_n];

	i = 0;
	while (i != center->philo_n)
	{
		thread_ids[i] = i;
		if (pthread_create(&center->philosophers[i], NULL, routine,
				(void *)&thread_ids[i]) != 0)
			return ;
		i++;
	}
	for (int wait = 0; wait < center->philo_n; wait++)
		pthread_join(center->philosophers[wait], NULL);
}

int	main(int ac, char **av)
{
	t_table table;

	if (ac != 6 || setup(&table, av))
		parse_error(&table, "All the values cannot be 0\n");
	philosophers_init(&table);
	//free(table.philosophers);
	return (0);
}