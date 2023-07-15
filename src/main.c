#include "philosophers.h"

int setup(t_table *table, char **av)
{
	table->philo_n = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->n_of_eats = ft_atoi(av[4]);
	if(table->philo_n == 0 || table->time_to_die == 0 || table->time_to_eat == 0 || table->time_to_sleep == 0 || table->n_of_eats == 0)
		return 1;
	table->philosophers = (pthread_t *)malloc(sizeof(pthread_t) * table->philo_n);
	if(!table->philosophers)
		return 1;
	return 0;
}

void *print_thread(void *id)
{
	printf("Hello World! %d", *(int *)id);
	sleep(1);
	return NULL;
}

int main (int ac, char **av)
{
	t_table table;
    
	if(ac != 6 || setup(&table, av))
        parse_error(&table, "All the values cannot be 0\n");
	for (int x = 0; x < table.philo_n; x++)
		table.philosophers[x] = pthread_create(&table.philosophers[x], NULL, print_thread, NULL);
	for (int x = 0; x < table.philo_n; x++)
		table.philosophers[x] = pthread_detach(table.philosophers[x]);
	free(table.philosophers);
    return 0;
}