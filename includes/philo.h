/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrichard <mrichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 20:22:53 by marcela           #+#    #+#             */
/*   Updated: 2023/03/03 21:06:21 by mrichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdint.h>

# define TAKE_FORKS "has taken a fork 🍴"
# define SLEEPING "is sleeping 😴"
# define EATING "is eating 🍽️"
# define THINKING "is thinking 💭"
# define DIED "died 💀"

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
	pthread_t		t1;
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
int		ft_atoi(char *str);
int		ft_strcmp(char *s1, char *s2);

//---Init---
int		init(t_table *table, char **argv, int argc);

//---Philo---
uint64_t	get_time(void);

//---Threads---

//Routine that every philo/thread will execute.
void    *routine(void *philo_pointer);
int		thread_init(t_table *table);

//---Exit and free---
int		exit_error(t_table *table);
void	ft_exit(t_table *table);

//---Actions---
void	messages(char *str, t_philo *philo);
void    eat(t_philo *philo);

#endif