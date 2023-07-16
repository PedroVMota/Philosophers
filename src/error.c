/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:59:51 by pedromota         #+#    #+#             */
/*   Updated: 2023/07/15 20:59:55 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	parse_error(t_table *table, char *msg)
{
	printf("%s", msg);
	if (table->philosophers != NULL)
		free(table->philosophers);
	exit(EXIT_FAILURE);
}
