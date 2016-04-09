/*
** optparser.c for strace in /home/kureuil/Work/strace
** 
** Made by Arch Kureuil
** Login   <kureuil@epitech.net>
** 
** Started on  Mon Apr  4 22:03:36 2016 Arch Kureuil
** Last update Sat Apr  9 19:12:56 2016 Arch Kureuil
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "optparser.h"
#include "strace.h"

int
optparse(int argc, char **argv, struct s_strace_opts *opts)
{
  char	c;
  int	i;

  while ((c = getopt(argc, argv, "sp:")) != -1)
    {
      if (c == 's')
	opts->compliant = true;
      else if (c == 'p')
	opts->pid = (pid_t) strtol(optarg, NULL, 10);
      else
	return (1);
    }
  if (opts->pid == 0 && argc - optind == 0)
    return (-1);
  opts->command = calloc(argc - optind + 1, sizeof(char *));
  if (opts->command == NULL)
    return (-1);
  i = 0;
  while (optind + i < argc)
    {
      opts->command[i] = argv[optind + i];
      i++;
    }
  opts->command[i] = NULL;
  return (0);
}
