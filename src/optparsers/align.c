/*
** align.c for strace in /home/kureuil/Work/strace
** 
** Made by Arch Kureuil
** Login   <kureuil@epitech.net>
** 
** Started on  Sun Apr 10 20:48:28 2016 Arch Kureuil
** Last update Mon Apr 11 00:04:22 2016 Arch Kureuil
*/

#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "optparser.h"
#include "strace.h"

int
strace_option_align(struct s_strace_opts *opts)
{
  errno = 0;
  opts->align = strtol(optarg, NULL, 10);
  if (errno)
    return (-1);
  if (opts->align < 0)
    {
      errno = EINVAL;
      return (-1);
    }
  return (0);
}
