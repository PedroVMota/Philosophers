#include <philo.h>

void *monitor(void *ph_ptr)
{
    t_philo *philo;

    philo = (t_philo *)ph_ptr;
    (void)philo;
    return 0;
}