/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:05:28 by mrichard          #+#    #+#             */
/*   Updated: 2023/03/07 20:15:27 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Checks if the status of all philos are marked as finished to stop the threads*/
static void	*monitor(void *table_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)table_pointer;
	pthread_mutex_lock(&philo->table->write);
	printf("table val: %d", philo->table->dead);
	pthread_mutex_unlock(&philo->table->write);
	while (philo->table->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->table->finished >= philo->table->number_of_philos)
			philo->table->dead = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return (NULL);
}

static void	*supervisor(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	while (philo->table->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->time_to_die && philo->eating == 0) //if he reaches the time to die without eating
			messages(DIED, philo); //he dies
		if (philo->times_ate == philo->table->must_eat) //other way, if he ate the number of times he must eat
		{
			pthread_mutex_lock(&philo->table->lock);
			philo->table->finished++; //mark him as finished so the monitor knows when all of them have eaten
			philo->times_ate++;
			pthread_mutex_unlock(&philo->table->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return (NULL);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo; //new philo

	philo = (t_philo *)philo_pointer;
	philo->time_to_die = philo->table->time_to_die + get_time(); //set the limit to a philo to die adding the local time and the global time of the table
	if (pthread_create(&philo->supervisor, NULL, &supervisor, (void *)philo)) //creates the supervisor who will check if it's time to die for the philo
		return ((void *)1);
	while (philo->table->dead == 0) //while there's no dead philos
	{
		eat(philo); //they eat
		messages(THINKING, philo); //and think after that
	}
	if (pthread_join(philo->supervisor, NULL)) //waits for supervisor to finish
		return ((void *)1); //error case
	return (NULL);
}

int	thread_init(t_table *table)
{
	int			i;
	pthread_t	tmonitor;
	
	i = -1;
	table->starting_time = get_time();
	if (table->must_eat > 0) //only if the optional parameter is defined
	{
		if (pthread_create(&tmonitor, NULL, &monitor, &table->philos[0]))
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