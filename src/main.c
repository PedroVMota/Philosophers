#include "philosophers.h"

static void	update_forks(t_table *table, int index)
{
}
static int	init_table(t_table *table)
{
	int	i;

	i = 0;
	table->threads = malloc(sizeof(pthread_t) * table->philo_num);
	if (!table->threads)
		return (0);
	while (i < table->philo_num)
	{
		addlast_philo(&table, i++);
		update_forks(table, i);
	}
	return (1);
}
int	set_paramters(t_table *table, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (0);
	}
	table->philo_num = ft_atoi(argv[1]);
	table->head = NULL;
	table->tail = NULL;
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->must_eat = ft_atoi(argv[5]);
	else
		table->must_eat = -1;
	if (table->philo_num < 1 || table->time_to_die < 1 || table->time_to_eat < 1
		|| table->time_to_sleep < 1 || (argc == 6 && table->must_eat < 1))
	{
		printf("Error: Wrong arguments\n");
		return (0);
	}
	if (!init_table(table))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_table *table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	if (!set_paramters(table, argc, argv))
		return (1);
	print_philo(table);
}