/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 20:23:06 by marcela           #+#    #+#             */
/*   Updated: 2023/03/02 20:07:29 by mrichard         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_table	table;
	
	if (error_in_args(argc, argv) || init(&table, argv, argc))
		return (exit_error());
	printf("\nNUMBER OF PHILOS: %d\n", table.number_of_philos);
	printf("TIME TO DIE: %d\n", table.time_to_die);
	printf("TIME TO EAT: %d\n", table.time_to_eat);
	printf("TIME TO SLEEP: %d\n", table.time_to_sleep);
	printf("TIMES TO EAT: %d\n", table.must_eat);
}