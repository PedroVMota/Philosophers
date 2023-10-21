#include "philo.h"

void *routine(void *ph_ptr)
{
	t_philo *philo;

	philo = (t_philo *)ph_ptr;
	(void)philo;
	pthread_mutex_lock(philo->left_fork);
	philo->database->_is_dead = 1;
	pthread_mutex_unlock(philo->left_fork);
	return 0;
}