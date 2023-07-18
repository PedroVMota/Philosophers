/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:59:57 by pedromota         #+#    #+#             */
/*   Updated: 2023/07/18 19:55:33 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void fork_manager(t_table *table, int thread_id)
{
	
	if(table->arr_phi[thread_id].left_fork->is_using == 0)
	{
		pthread_mutex_lock(table->arr_phi[thread_id].left_fork->forks);
		table->arr_phi[thread_id].left_fork->is_using = 1;
		printf("has taken a fork\n");
	}
	if(table->arr_phi[thread_id].right_fork->is_using == 0)
	{
		pthread_mutex_lock(table->arr_phi[thread_id].right_fork->forks);
		table->arr_phi[thread_id].right_fork->is_using = 1;
		printf("has taken a fork\n");
	}
	if (table->arr_phi[thread_id].left_fork->is_using == 1 && table->arr_phi[thread_id].right_fork->is_using == 1)
	{
		printf("is eating\n");
		table->arr_phi[thread_id].n_of_eats++;
		gettimeofday(&table->arr_phi[thread_id].last_meal, NULL);
		usleep(table->time_to_eat_ms * 1000);
		pthread_mutex_unlock(table->arr_phi[thread_id].left_fork->forks);
		pthread_mutex_unlock(table->arr_phi[thread_id].right_fork->forks);
		table->arr_phi[thread_id].left_fork->is_using = 0;
		table->arr_phi[thread_id].right_fork->is_using = 0;
		printf("is sleeping\n");
		usleep(table->time_to_sleep_ms * 1000);
		printf("is thinking\n");
	}
}

void *routine(void *id)
{
	int ThreadID = *(int *)id;
	while(1 && table()->arr_phi[ThreadID].is_life == true && table()->arr_phi[ThreadID].n_of_eats < table()->n_of_eats)
	{
		gettimeofday(&table()->arr_phi[ThreadID].current_time, NULL);
		printf("%d %d \n", table()->arr_phi[ThreadID].start.tv_usec / 1000, ThreadID);
		fork_manager(table(), ThreadID);
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
		if (pthread_create(&center->phi_thread[i], NULL, routine,
						   (void *)&thread_ids[i]) != 0)
			return;
		i++;
	}
	for (int x = 0; x < center->philo_n; x++)
		pthread_join(center->phi_thread[x], NULL);
}

int main(int ac, char **av)
{
	if (ac != 6)
		parse_error(table(), "Wrong number of arguments\n");
	if (setup(table(), av))
		parse_error(table(), "All the values cannot be 0\n");
	philosophers_init(table());
	return (0);
}