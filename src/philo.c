/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 20:23:06 by marcela           #+#    #+#             */
/*   Updated: 2023/03/07 20:35:01 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	error_in_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	if (argc < 5 || argc > 6)
		return (1);
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
		} 
	}
	return (0);
}

uint64_t	get_time(void)
{
	struct timeval	tv; //struct that stores the current time in seconds and microseconds

	if (gettimeofday(&tv, NULL)) //current program time in microseconds
		return (exit_error(NULL));
	///multiply the number of seconds by 1000 to convert them to milliseconds
	//divide milliseconds by 100 to convert to microseconds
	return ((tv.tv_sec * (int)1000) + (tv.tv_usec / 1000));
}

int	case_one(t_table *table)
{
	table->starting_time = get_time();
	if (pthread_create(&table->tid[0], NULL, &routine, &table->philos[0])) //creates just one thread
		return (exit_error(table));
	pthread_detach(table->tid[0]); //it no longer needs to be explicitly joined with another thread in order to release its resources.
	while (table->dead == 0)
		usleep(0);
	ft_exit(table);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;
	
	if (error_in_args(argc, argv) || init(&table, argv, argc))
		return (exit_error(&table));
	if (table.number_of_philos == 1)
		return (case_one(&table));
	if (thread_init(&table))
		return (1);
	ft_exit(&table);
	return (0);
}