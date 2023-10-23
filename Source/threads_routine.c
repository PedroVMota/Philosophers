#include "philo.h"

void *routine(void *ph_ptr)
{
	t_philo *philo;

	philo = (t_philo *)ph_ptr;
	philo->_time_to_die = philo->database->_time_to_die + get_time();
	while (!philo->database->_is_dead)
	{
		eat(philo);
		messages(THINKING, philo);
	}
	return (NULL);
	return 0;
}

bool create_threads(t_data *db)
{
	int			i;

	i = -1;
	db->start = get_time();
	while (++i < db->_number_of_philosophers)
	{
		if (pthread_create(&db->tid[i], NULL, &routine, &db->philo[i]))
			return (error(TH_ERR, db));
		ft_usleep(1);
	}
	return (0);
	return false;
}