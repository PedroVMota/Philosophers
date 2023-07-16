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

void *routine(void *id)
{
	struct timeval last_meal, current_time;
	gettimeofday(&last_meal, NULL);

	int i = 0;
	while (i < 2)
	{
		gettimeofday(&current_time, NULL);
        long milliseconds_since_last_meal = (current_time.tv_sec - last_meal.tv_sec) * 1000 +
                                            (current_time.tv_usec - last_meal.tv_usec) / 1000;
        long milliseconds_since_start = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);

        printf("%ld %d is living!\n", milliseconds_since_start, *(int *)id);

        if (milliseconds_since_last_meal > table()->time_to_die)
        {
            printf("%ld %d died!\n", milliseconds_since_start, *(int *)id);
            break;
        }
	}
}

void philosophers_init(t_table *center)
{
	int i;
	int thread_ids[center->philo_n];

	i = 0;
	while (i != center->philo_n)
	{
		thread_ids[i] = i;
		if (pthread_create(&center->philosophers[i], NULL, routine,
						   (void *)&thread_ids[i]) != 0)
			return;
		i++;
	}
	for (int x = 0; x < center->philo_n; x++)
		pthread_join(center->philosophers[x], NULL);
}

int main(int ac, char **av)
{
	if (ac != 6)
		return 1;
	if (setup(table(), av))
		parse_error(table(), "All the values cannot be 0\n");
	philosophers_init(table());
	free(table()->philosophers);
	return (0);
}