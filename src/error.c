#include "philosophers.h"

void parse_error(t_table *table, char *msg)
{
    if(table->philosophers)
        free(table->philosophers);
    printf("%s", msg);
    exit(EXIT_FAILURE);
}