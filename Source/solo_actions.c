/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 17:24:28 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/10 17:37:59 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->database->write);
	printf("%lu %u %s\n", philo->_time_to_die, philo->_id, DIED);
	philo->database->b_dead = 1;
	pthread_mutex_unlock(&philo->database->write);
}

void	*soloroutine(void *ph_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ph_ptr;
	(void)philo;
	philo->last_meal = get_time();
	pthread_mutex_lock(philo->left_fork);
	print_dead(philo);
	pthread_mutex_unlock(philo->left_fork);
	messages(DIED, philo);
	return (NULL);
}
