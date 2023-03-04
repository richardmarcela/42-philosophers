/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 20:23:06 by marcela           #+#    #+#             */
/*   Updated: 2023/03/04 15:13:45 by mrichard         ###   ########.fr       */
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
	struct timeval	tv; //estrutura que armazena o tempo atual em segundos e microssegundos

	if (gettimeofday(&tv, NULL)) //tempo atual do programa em microssegundos
		return (exit_error(NULL));
	//multiplica o numero de segundos por 1000 para converte-los em milissegundos
	//divide os milissegundos por 100 pra transformar em microssegundos
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

int	case_one(t_table *table)
{
	table->starting_time = get_time();
	if (pthread_create(&table->tid[0], NULL, &routine, &table->philos[0]))
		return (exit_error(table));
	pthread_detach(table->tid[0]);
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