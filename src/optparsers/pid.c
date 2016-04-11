/*
** pid.c for strace in /home/kureuil/Work/strace
** 
** Made by Arch Kureuil
** Login   <kureuil@epitech.net>
** 
** Started on  Sun Apr 10 20:39:16 2016 Arch Kureuil
** Last update Mon Apr 11 00:00:17 2016 Arch Kureuil
*/

#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "optparser.h"
#include "strace.h"

int
strace_option_pid(struct s_strace_opts *opts)
{
  errno = 0;
  opts->pid = (pid_t) strtol(optarg, NULL, 10);
  if (errno == -1)
    return (-1);
  return (0);
}
