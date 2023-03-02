/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:31:10 by mrichard          #+#    #+#             */
/*   Updated: 2023/03/02 19:56:21 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	alloc(t_table *table)
{
	table->tid = malloc(sizeof(pthread_t) * table->number_of_philos);
	if (!table->tid)
		return (exit_error());
	table->forks = malloc(sizeof(pthread_mutex_t) * table->number_of_philos);
	if (!table->forks)
		return (exit_error());
	table->philos = malloc(sizeof(t_philo) * table->number_of_philos);
	if (!table->philos)
		return (exit_error());
	return (0);
}

static int	init_forks(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->number_of_philos)
		pthread_mutex_init(&table->forks[i], NULL);
	table->philos[0].left_fork = &table->forks[0];
	table->philos[0].right_fork = &table->forks[table->number_of_philos - 1];
	i = 0;
	while (++i < table->number_of_philos)
	{
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[i - 1];
	}
	return (0);
}

static void	init_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->number_of_philos)
	{
		table->philos[i].table = table;
		table->philos[i].id = i + 1;
		table->philos[i].time_to_die = table->time_to_die;
		table->philos[i].times_ate = 0;
		table->philos[i].status = 0;
		pthread_mutex_init(&table->philos[i].lock, NULL);
	}
}

static int	init_table(t_table *table, char **argv, int argc)
{
	table->number_of_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->must_eat = ft_atoi(argv[5]);
	else
		table->must_eat = -1;
	if (table->number_of_philos <= 0 || table->time_to_die < 0
		|| table->time_to_eat < 0 || table->time_to_sleep < 0)
		return (exit_error());
	table->dead = 0;
	table->finished = 0;
	pthread_mutex_init(&table->write, NULL);
	pthread_mutex_init(&table->lock, NULL);
	return (0);
}

int	init(t_table *table, char **argv, int argc)
{
	if (init_table(table, argv, argc) || alloc(table)
		|| init_forks(table))
		return (1);
	init_philos(table);
	return (0);
}