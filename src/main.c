/*
** main.c for zappy in /home/kureuil/Work/zappy/server/src
**
** Made by Arch Kureuil
** Login   <kureuil@epitech.net>
**
** Started on  Fri Mar 18 08:53:07 2016 Arch Kureuil
** Last update Sun Apr 10 21:20:18 2016 Arch Kureuil
*/

#include <sys/ptrace.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include "optparser.h"
#include "strace.h"

static void
usage(FILE *stream, const char *prgm)
{
  fprintf(stream, "\nUSAGE: %s [OPTIONS...] COMMAND [ARGS]\n\n", prgm);
  fprintf(stream, "OPTIONS:\n");
  fprintf(stream, "\t-s       Make output more compliant with the system's"
	  " strace\n");
  fprintf(stream, "\t-p PID   Trace program with id = PID instead of launching"
	  " COMMAND\n");
  fprintf(stream, "\t-a ALIGN Align output on column ALIGN (default=40)\n");
  fprintf(stream, "\t-f FILE  Write strace output to FILE (default=stderr)\n");
  fprintf(stream, "\tCOMMAND  Program to execute & trace\n");
  fprintf(stream, "\tARGS     Arguments given to the executed program\n");
}

static int
exec(char **command, pid_t *pidptr)
{
  pid_t	child;

  child = fork();
  if (child == -1)
    return (-1);
  else if (child == 0)
    {
      if (ptrace(PTRACE_TRACEME, 0, 0, 0) == -1)
	return (-1);
      execvp(command[0], command);
      return (-1);
    }
  else
    *pidptr = child;
  return (0);
}

static void
opts_init(struct s_strace_opts *opts)
{
  memset(opts, 0, sizeof(struct s_strace_opts));
  opts->align = 40;
  opts->output = stderr;
  opts->output_type = O_INNATE;
}

static void
opts_destroy(struct s_strace_opts *opts)
{
  free(opts->command);
  if (opts->output_type == O_FILE)
    fclose(opts->output);
  else if (opts->output_type == O_COMMAND)
    pclose(opts->output);
}

int
main(int argc, char *argv[])
{
  MANAGED(opts_destroy) struct s_strace_opts	opts;

  opts_init(&opts);
  if (optparse(argc, argv, &opts))
    {
      usage(stderr, argv[0]);
      return (EXIT_FAILURE);
    }
  if (opts.pid == 0 && opts.command == NULL)
    {
      usage(stderr, argv[0]);
      return (EXIT_FAILURE);
    }
  if (opts.command != NULL && opts.command[0] != NULL)
    {
      if (exec(opts.command, &opts.pid))
	return (perror(argv[0]), EXIT_FAILURE);
    }
  if (strace(opts.pid, &opts))
    {
      if (errno != 0)
	perror(argv[0]);
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
