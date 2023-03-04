/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:40:02 by mrichard          #+#    #+#             */
/*   Updated: 2023/03/04 15:17:04 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clear_data(t_table *table)
{
	free(table->tid);
	free(table->forks);
	free(table->philos);
}

int	exit_error(t_table *table)
{
	printf("Error in params! Try again.\n");
	if (table)
		ft_exit(table);
	return (1);
}

void	ft_exit(t_table *table)
{
	int	i;
	
	i = -1;
	if (table)
	{
		while (++i < table->number_of_philos)
		{
			pthread_mutex_destroy(&table->forks[i]);
			pthread_mutex_destroy(&table->philos[i].lock);
		}
		pthread_mutex_destroy(&table->write);
		pthread_mutex_destroy(&table->lock);
		clear_data(table);
	}
}