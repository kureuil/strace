/*
** file.c for strace in /home/kureuil/Work/strace
** 
** Made by Arch Kureuil
** Login   <kureuil@epitech.net>
** 
** Started on  Sun Apr 10 20:54:58 2016 Arch Kureuil
** Last update Mon Apr 11 00:04:43 2016 Arch Kureuil
*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "optparser.h"
#include "strace.h"

static int
strace_option_file_command(struct s_strace_opts *opts,
			   const char *command)
{
  opts->output = popen(command + 1, "w");
  if (opts->output == NULL)
    return (-1);
  opts->output_type = O_COMMAND;
  return (0);
}

static int
strace_option_file_path(struct s_strace_opts *opts,
			const char *filepath)
{
  opts->output = fopen(filepath, "w+");
  if (opts->output == NULL)
    return (-1);
  opts->output_type = O_FILE;
  return (0);
}

int
strace_option_file(struct s_strace_opts *opts)
{
  if (opts->output_type != O_INNATE)
    {
      errno = EINVAL;
      return (-1);
    }
  if (optarg[0] == '!' || optarg[0] == '|')
    return (strace_option_file_command(opts, optarg));
  return (strace_option_file_path(opts, optarg));
}
