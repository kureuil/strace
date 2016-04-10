/*
** optparser.c for strace in /home/kureuil/Work/strace
** 
** Made by Arch Kureuil
** Login   <kureuil@epitech.net>
** 
** Started on  Mon Apr  4 22:03:36 2016 Arch Kureuil
** Last update Sun Apr 10 21:35:21 2016 Arch Kureuil
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "optparser.h"
#include "strace.h"

static const struct s_option g_opts[] = {
  { .flag = 'p', .callback = &strace_option_pid },
  { .flag = 's', .callback = &strace_option_compliant },
  { .flag = 'a', .callback = &strace_option_align },
  { .flag = 'f', .callback = &strace_option_file },
  { .flag = 't', .callback = &strace_option_timestamp },
  { .flag = '\0', .callback = NULL },
};

static int
optparser_get_option(char flag,
		     struct s_option *opt)
{
  size_t	i;

  i = 0;
  while (g_opts[i].flag)
    {
      if (g_opts[i].flag == flag)
	{
	  *opt = g_opts[i];
	  return (0);
	}
      i++;
    }
  return (-1);
}

int
optparser_get_arguments(char ***argp, int argc, char **argv)
{
  int	i;

  *argp = calloc(argc - optind + 1, sizeof(char *));
  if (*argp == NULL)
    return (-1);
  i = 0;
  while (optind + i < argc)
    {
      (*argp)[i] = argv[optind + i];
      i++;
    }
  (*argp)[i] = NULL;
  return (0);
}

int
optparse(int argc, char **argv, struct s_strace_opts *opts)
{
  char			c;
  struct s_option	opt;

  while ((c = getopt(argc, argv, "sp:a:f:t")) != -1)
    {
      if (optparser_get_option(c, &opt))
	return (-1);
      if (opt.callback(opts))
	return (-1);
    }
  if (opts->pid == 0 && argc - optind == 0)
    return (-1);
  return (optparser_get_arguments(&opts->command, argc, argv));
}
