/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:08:02 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/10 16:11:56 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->database->write);
	printf("%lu %u %s\n", philo->_time_to_die, philo->_id, DIED);
	philo->database->_is_dead = 1;
	pthread_mutex_unlock(&philo->database->write);
}
