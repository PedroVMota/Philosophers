/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 17:24:32 by pedromota         #+#    #+#             */
/*   Updated: 2023/12/10 17:37:03 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*soloroutine(void *ph_ptr);
void		philo_eat(t_philo *ph);

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
	while (!(philo->database->b_dead)
		&& philo->_meals_eaten < philo->database->n_eat)
	{
		pthread_mutex_unlock(&philo->database->lock);
		philo_eat(philo);
		messages(SLEEPING, philo);
		ft_usleep(philo->database->t_sle);
		messages(THINKING, philo);
		pthread_mutex_lock(&philo->database->lock);
	}
	pthread_mutex_unlock(&philo->database->lock);
	return (NULL);
}

static void	*update_dead(t_data *data, int i)
{
	messages(DIED, &data->philo[i]);
	pthread_mutex_lock(&data->lock);
	data->b_dead = 1;
	pthread_mutex_unlock(&data->lock);
	pthread_mutex_unlock(&data->philo[i].lock);
	return (NULL);
}

void	*monitor(void *db)
{
	t_data	*data;
	int		i;

	data = db;
	i = -1;
	while (data->f_ph < data->n_p)
	{
		i = -1;
		while (++i < data->n_p)
		{
			pthread_mutex_lock(&data->philo[i].lock);
			if (data->philo[i]._meals_eaten == data->n_eat)
				data->f_ph++;
			if (get_time() - data->philo[i].last_meal > (__uint64_t)data->t_die)
				return (update_dead(data, i));
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
	while (++i < db->n_p)
	{
		if (pthread_create(&db->philosophers[i], NULL, &routine, &db->philo[i]))
			return ;
		usleep(150);
	}
	routine_supervisor(db);
	i = -1;
	while (++i < db->n_p)
		if (pthread_join(db->philosophers[i], NULL))
			return ;
	return ;
}
