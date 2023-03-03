/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:05:28 by mrichard          #+#    #+#             */
/*   Updated: 2023/03/03 21:06:02 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*monitor(void *table_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)table_pointer;
	pthread_mutex_lock(&philo->table->write);
	printf("data val: %d", philo->table->dead);
	pthread_mutex_unlock(&philo->table->write);
	while (philo->table->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->table->finished >= philo->table->number_of_philos)
			philo->table->dead = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

static void	*supervisor(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	while (philo->table->dead == 0)
	{
		pthread_mutex_lock(&philo->lock); //lock operations made by a single philo and it's data structure
		if (get_time() >= philo->time_to_die && philo->eating == 0)
			messages(DIED, philo);
		if (philo->times_ate == philo->table->must_eat)
		{
			pthread_mutex_lock(&philo->table->lock); //lock data shared by multiple threads
			philo->table->finished++;
			philo->times_ate++;
			pthread_mutex_unlock(&philo->table->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo; //new philo

	philo = (t_philo *)philo_pointer;
	philo->time_to_die = philo->table->time_to_die + get_time(); //set the limit to a philo to die adding the local time and the global time of the table
	if (pthread_create(&philo->t1, NULL, &supervisor, (void *)philo)) //creates the supervisor which is a thread to check if the philo is eating and alive
		return ((void *)1); //error case
	while (philo->table->dead == 0) //while there's no dead philos
	{
		eat(philo); //they eat
		messages(THINKING, philo); //and think after that
	}
	if (pthread_join(philo->t1, NULL)) //waits for t1 to finish
		return ((void *)1); //error case
	return ((void *)0);
}

int	thread_init(t_table *table)
{
	int			i;
	pthread_t	t0;
	
	i = -1;
	table->starting_time = get_time();
	if (table->must_eat > 0)
	{
		if (pthread_create(&t0, NULL, &monitor, &table->philos[0]))
			return (exit_error(table));
	}
	while (++i < table->number_of_philos)
	{
		if (pthread_create(&table->tid[i], NULL, &routine, &table->philos[i]))
			return (exit_error(table));
		usleep(1);
	}
	i = -1;
	while (++i < table->number_of_philos)
	{
		if (pthread_join(table->tid[i], NULL))
			return (exit_error(table));
	}
	return (0);
}