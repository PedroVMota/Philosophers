#include "philo.h"

void *soloroutine(void *ph_ptr)
{
	t_philo *philo;

	philo = (t_philo *)ph_ptr;
	(void)philo;
	philo->last_meal = get_time();
	pthread_mutex_lock(philo->left_fork);
	print_dead(philo);
	pthread_mutex_unlock(philo->left_fork);
	messages(DIED, philo);
	return (NULL);
}

void philo_eat(t_philo *ph)
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
	messages(EATING, ph);
	ft_usleep(ph->database->db_time_to_eat);
	ph->_meals_eaten++;
	pthread_mutex_unlock(&ph->lock);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
}

void *routine(void *ph_ptr)
{
	t_philo *philo;

	philo = (t_philo *)ph_ptr;
	if (philo->database->db_n_philo == 1)
	{
		soloroutine((void *)philo);
		return (NULL);
	}
	pthread_mutex_lock(&philo->database->lock);
	while (!(philo->database->_is_dead) && philo->_meals_eaten < philo->database->db_n_time_eat)
	{
		pthread_mutex_unlock(&philo->database->lock);
		philo_eat(philo);
		messages(SLEEPING, philo);
		ft_usleep(philo->database->db_time_to_sleep);
		messages(THINKING, philo);
		// usleep(2000);
		pthread_mutex_lock(&philo->database->lock);
	}
	pthread_mutex_unlock(&philo->database->lock);
	return (NULL);
}

void *monitor(void *db)
{
	t_data *data;
	int i;

	data = db;
	i = -1;
	while (data->db_full_philos < data->db_n_philo)
	{
		i = -1;
		while (++i < data->db_n_philo)
		{
			pthread_mutex_lock(&data->philo[i].lock);
			if (data->philo[i]._meals_eaten == data->db_n_time_eat)
				data->db_full_philos++;
			if (get_time() - data->philo[i].last_meal > (__uint64_t)data->db_time_to_die)
			{
				messages(DIED, &data->philo[i]);
				pthread_mutex_lock(&data->lock);
				data->_is_dead = 1;
				pthread_mutex_unlock(&data->lock);
				pthread_mutex_unlock(&data->philo[i].lock);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philo[i].lock);
		}
	}
	return (NULL);
}

void routine_supervisor(t_data *db)
{
	pthread_t th_monitor;

	if (pthread_create(&th_monitor, NULL, &monitor, (void *)db))
		return;
	if (pthread_join(th_monitor, NULL))
		return;
}

void routine_setup(t_data *db)
{
	int i;

	i = -1;
	while (++i < db->db_n_philo)
	{
		if (pthread_create(&db->philosophers[i], NULL, &routine, &db->philo[i]))
			return;
		usleep(150);
	}
	routine_supervisor(db);
	i = -1;
	while (++i < db->db_n_philo)
		if (pthread_join(db->philosophers[i], NULL))
			return;
	return;
}
