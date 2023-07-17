/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:59:57 by pedromota         #+#    #+#             */
/*   Updated: 2023/07/17 15:42:23 by pvital-m         ###   ########.fr       */
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
        long long ms_since_last_meal = (current_time.tv_usec - last_meal.tv_usec) / 1000;
        long long ms_since_start = (current_time.tv_usec + current_time.tv_usec) / 1000;
		printf("Philosopther %d Milliseconds from the last meal: %d\n", * (int *) id,  ms_since_last_meal);
		printf("Philosopther %d from the start: %d\n", * (int *) id,  ms_since_start);
        break;
	}
    return (NULL);
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