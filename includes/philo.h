/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 20:22:53 by marcela           #+#    #+#             */
/*   Updated: 2023/03/02 20:04:35 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_philo
{
	int				id;
	int				times_ate;
	int				eating;
	int				status;
	__uint64_t		time_to_die;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	lock;
	struct s_table	*table;
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
	int				dead;
	int				finished;
	t_philo			*philos;
	pthread_t		*tid;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}					t_table;


//---Utils---
int		ft_isdigit(int c);
int		exit_error(void);
int		ft_atoi(char *str);

//---Init---
int		init(t_table *table, char **argv, int argc);

#endif