/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:05:28 by mrichard          #+#    #+#             */
/*   Updated: 2023/03/04 20:50:33 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	supervisor(t_philo *philo)
{
	if (get_time() >= philo->time_to_die && philo->eating == 0)
		messages(DIED, philo);
	if (philo->times_ate == philo->table->must_eat)
	{
		pthread_mutex_lock(&philo->table->lock);
		philo->table->finished++;
		philo->times_ate++;
		pthread_mutex_unlock(&philo->table->lock);
	}
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo; //new philo
	t_table	*table;

	philo = (t_philo *)philo_pointer;
	table = philo->table;
	philo->time_to_die = philo->table->time_to_die + get_time(); //set the limit to a philo to die adding the local time and the global time of the table
	while (philo->table->dead == 0) //while there's no dead philos
	{
		eat(philo); //they eat
		messages(THINKING, philo); //and think after that
		supervisor(philo);
	}
	if (pthread_join(philo->t1, NULL)) //waits for t1 to finish
		return ((void *)1); //error case
	return ((void *)0);
}

int	thread_init(t_table *table)
{
	int			i;
	
	i = -1;
	table->starting_time = get_time();
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