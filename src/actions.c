/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:37:33 by mrichard          #+#    #+#             */
/*   Updated: 2023/03/04 15:41:04 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	messages(char *str, t_philo *philo)
{
	uint64_t	time;

	pthread_mutex_lock(&philo->table->write);
	time = get_time() - philo->table->starting_time; //current time
	if (ft_strcmp(DIED, str) == 0 && philo->table->dead == 0) //if the philo died and there's no other dead yet
	{
		printf("%lu %d %s\n", time, philo->id, str); //prints the message
		philo->table->dead = 1; //increase the number of dead
	}
	if (!philo->table->dead) //if it's not a message of dying or there's no dead yet
		printf("%lu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->table->write);
}

void    eat(t_philo *philo)
{
	t_table	*table;
	
	table = philo->table;
	pthread_mutex_lock(&table->forks[philo->left_fork]);
	pthread_mutex_lock(&table->forks[philo->right_fork]);
	philo->eating = 1;
	philo->time_to_die = get_time() + philo->table->time_to_die;
	messages(EATING, philo);
	philo->times_ate++;
	usleep(philo->table->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(&table->forks[philo->left_fork]);
	pthread_mutex_unlock(&table->forks[philo->right_fork]);
}