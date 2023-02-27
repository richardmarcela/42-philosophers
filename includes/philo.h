/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcela <marcela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 20:22:53 by marcela           #+#    #+#             */
/*   Updated: 2023/02/27 20:12:19 by marcela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				times_ate;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;


typedef struct s_table
{
	int 			number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				must_eat;
	int				starting_time;
	t_philo			philos;
	pthread_mutex_t	*forks;
}					t_table;


//---Utils---
int	ft_isdigit(int c);
int	exit_error(void);

#endif