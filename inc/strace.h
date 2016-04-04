/*
** strace.h for strace in /home/kureuil/Work/strace
** 
** Made by Arch Kureuil
** Login   <kureuil@epitech.net>
** 
** Started on  Mon Apr  4 21:50:50 2016 Arch Kureuil
** Last update Mon Apr  4 22:16:18 2016 Arch Kureuil
*/

#ifndef STRACE_H_
# define STRACE_H_

# include <stdbool.h>
# include <sys/types.h>

struct s_strace_opts
{
  pid_t	pid;
  char	**command;
  bool	compliant;
};

/*
** Trace all system calls made by the given PID.
**
** @param pid the traced program id
** @return 0 in case of success, -1 in case of failure
*/
int strace(pid_t pid);

#endif
