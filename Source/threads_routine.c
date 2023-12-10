/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 12:41:31 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/10 15:07:03 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *ph);

void	*soloroutine(void *ph_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ph_ptr;
	(void)philo;
	pthread_mutex_lock(&philo->lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_lock(philo->left_fork);
	print_dead(philo);
	pthread_mutex_unlock(philo->left_fork);
	messages(DIED, philo);
	ft_usleep(100);
	return (NULL);
}

void	*routine(void *ph_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ph_ptr;
	if (philo->database->n_p == 1)
	{
		soloroutine((void *)philo);
		return (NULL);
	}
	pthread_mutex_lock(&philo->database->lock);
	while (!(philo->database->_is_dead)
		&& philo->_meals_eaten < philo->database->db_nte)
	{
		pthread_mutex_unlock(&philo->database->lock);
		philo_eat(philo);
		messages(SLEEPING, philo);
		ft_usleep(philo->database->db_tts);
		messages(THINKING, philo);
		pthread_mutex_lock(&philo->database->lock);
	}
	pthread_mutex_unlock(&philo->database->lock);
	return (NULL);
}

void	*monitor(void *db)
{
	t_data	*data;
	int		i;

	data = db;
	i = -1;
	while (data->db_full_philos < data->n_p)
	{
		i = -1;
		while (++i < data->n_p)
		{
			pthread_mutex_lock(&data->philo[i].lock);
			if (get_time() - data->philo[i].last_meal > (__uint64_t)data->db_nttd)
			{
				messages(DIED, &data->philo[i]);
				pthread_mutex_lock(&data->lock);
				data->_is_dead = 1;
				pthread_mutex_unlock(&data->lock);
				pthread_mutex_unlock(&data->philo[i].lock);
				return (NULL);
			}
			if (data->philo[i]._meals_eaten == data->db_nte)
				data->db_full_philos++;
			pthread_mutex_unlock(&data->philo[i].lock);
		}
	}
	return (NULL);
}

void	routine_supervisor(t_data *db)
{
	pthread_t	th_monitor;

	if (pthread_create(&th_monitor, NULL, &monitor, (void *)db))
		return ;
	if (pthread_join(th_monitor, NULL))
		return ;
}

void	routine_setup(t_data *db)
{
	int	i;

	i = -1;
	routine_supervisor(db);
	while (++i < db->n_p)
	{
		if (pthread_create(&db->philosophers[i], NULL, &routine, &db->philo[i]))
			return ;
		usleep(20);
	}
	i = -1;
	while (++i < db->n_p)
		if (pthread_join(db->philosophers[i], NULL))
			return ;
	return ;
}
