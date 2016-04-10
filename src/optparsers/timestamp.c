/*
** timestamp.c for strace in /home/kureuil/Work/strace
** 
** Made by Arch Kureuil
** Login   <kureuil@epitech.net>
** 
** Started on  Sun Apr 10 21:31:05 2016 Arch Kureuil
** Last update Sun Apr 10 21:38:32 2016 Arch Kureuil
*/

#include <errno.h>
#include "optparser.h"
#include "strace.h"

int
strace_option_timestamp(struct s_strace_opts *opts)
{
  if (opts->timestamp_type == TS_NONE)
    opts->timestamp_type = TS_TIME;
  else if (opts->timestamp_type == TS_TIME)
    opts->timestamp_type = TS_MILLISECOND;
  else
    {
      errno = EINVAL;
      return (-1);
    }
  return (0);
}
