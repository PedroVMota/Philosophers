#include "philo.h"

void print_dead(t_philo *philo);

void *soloroutine(void *ph_ptr)
{
	t_philo *philo;

	philo = (t_philo *)ph_ptr;
	(void)philo;
	
	philo->last_meal = get_time();
	pthread_mutex_lock(philo->left_fork);
	print_dead(philo);
	pthread_mutex_unlock(philo->left_fork);
	messages("died\n", philo);
	return 0;
}
void *routine(void *ph_ptr)
{
	t_philo *philo;

	philo = (t_philo *)ph_ptr;
	while ()
		return 0;
}