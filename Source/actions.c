/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:06:14 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/10 16:15:27 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	messages(char *str, t_philo *philo)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->database->write);
	pthread_mutex_lock(&philo->database->lock);
	time = get_time() - philo->time_start;
	if (ft_strcmp(DIED, str) == 0 && philo->database->_is_dead == 0)
	{
		printf("%lu %u %s\n", time, philo->_id, str);
		philo->database->_is_dead = 1;
	}
	if (!philo->database->_is_dead)
		printf("%lu %u %s\n", time, philo->_id, str);
	pthread_mutex_unlock(&philo->database->lock);
	pthread_mutex_unlock(&philo->database->write);
}

void	philo_eat(t_philo *ph)
{
	if (ph->_id % 2 == 0)
	{
		pthread_mutex_lock(ph->left_fork);
		messages(TAKE_FORKS, ph);
		pthread_mutex_lock(ph->right_fork);
		messages(TAKE_FORKS, ph);
	}
	else
	{
		pthread_mutex_lock(ph->right_fork);
		messages(TAKE_FORKS, ph);
		pthread_mutex_lock(ph->left_fork);
		messages(TAKE_FORKS, ph);
	}
	pthread_mutex_lock(&ph->lock);
	ph->last_meal = get_time();
	pthread_mutex_unlock(&ph->lock);
	messages(EATING, ph);
	ft_usleep(ph->database->eat_t);
	pthread_mutex_lock(&ph->lock);
	ph->meal_n++;
	pthread_mutex_unlock(&ph->lock);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
}
