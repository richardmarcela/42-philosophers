/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:37:33 by mrichard          #+#    #+#             */
/*   Updated: 2023/03/07 20:33:05 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	messages(char *str, t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->table->write);
	time = get_time() - philo->table->starting_time; //current time
	if (ft_strcmp(DIED, str) == 0 && philo->table->dead == 0) //if the philo died and there's no other dead yet
	{
		printf("%d %d %s\n", time, philo->id, str); //prints the message
		philo->table->dead = 1; //increase the number of dead
	}
	if (!philo->table->dead) //if it's not a message of dying or there's no dead yet
		printf("%d %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->table->write);
}

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	messages(TAKE_FORKS, philo);
	pthread_mutex_lock(philo->left_fork);
	messages(TAKE_FORKS, philo);
}

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	messages(SLEEPING, philo);
	usleep(philo->table->time_to_sleep);
}

void    eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_to_die = get_time() + philo->table->time_to_die;
	messages(EATING, philo);
	philo->times_ate++;
	usleep(philo->table->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
}